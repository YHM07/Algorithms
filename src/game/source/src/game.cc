/**
 * @file game.cc
 * @brief HUAWEI game
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/21/2015
 */
//#include "protocol.h"
#include "msghandle.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

#include <stdlib.h>

#define	BUFFSIZE	128			/*  */

//struct player_msg;
//struct cards;

const char *infomsg[] = {"seat/ ",
	"blind/ ",
	"hold/ ",
	"inquire/ ",
	"flop/ ",
	"turn/ ",
	"river/ ",
	"showdown/ ",
	"pot-win/ ",
	"notify/ ",
	"game-over/ "
};

/* msg number */
#define	SEAT		0			/* seat/      */
#define	BLIND		1			/* blind/     */
#define	HOLD		2			/* hold/	  */
#define	INQUIRE		3			/* inquire/	  */
#define	FLOP		4    		/* flop/	  */
#define	TURN		5    		/* turn/	  */
#define	RIVER		6    		/* river/	  */
#define	SHOWDOWN	7    		/* showdown/  */
#define	POTWIN		8    		/* pot-win/   */
#define	NOTIFY		9    		/* notify/    */
#define	GAMEOVER	10			/* game-over/ */


/**
 * @brief	main 
 *
 * @param	argc
 * @param	argv[]
 *
 * @return	
 */
	int
main ( int argc, char *argv[] )
{
	int	sockfd;

	if (argc != 6) {
		fprintf(stderr,"usage: %s serviceIP serviceport clientIP clientport clientID", 
				argv[0]);
		printf ( "\n" );
		exit(EXIT_FAILURE);
	}

	/* get the param  */
	in_addr_t server_IP   = inet_addr(argv[1]);
	in_port_t server_Port = htons(atoi(argv[2]));
	in_addr_t client_IP   = inet_addr(argv[3]);
	in_port_t client_Port = htons(atoi(argv[4]));
	/* my id */
	int  pid			  = atoi(argv[5]);

	/* set server param */
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family		  = AF_INET;
	server_addr.sin_addr.s_addr   = server_IP;
	server_addr.sin_port	      = server_Port;

	/* set client param */
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family		  = AF_INET;
	client_addr.sin_addr.s_addr   = client_IP;
	client_addr.sin_port		  = client_Port;

	/* create socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("create socket failed");
		exit(EXIT_FAILURE); 
	}
	/* set socket opt */
	int reuse = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1){
		perror("setsockopt error");
		exit(EXIT_FAILURE); 
	}

	/* bind ip and port */
	if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		perror("bind error");
		exit(EXIT_FAILURE);  
	}

	/* connect to server */
	while (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect error");
//		exit(EXIT_FAILURE);
		usleep(100*1000);
	}
	printf ( "connect succeed\n" );

	/* registration  */
	char msgbuf[BUFFSIZE] = {'\0'};
	char pname[] = "hellokity";
	sprintf(msgbuf, "reg: %d %s need_notify \n", pid, pname);
	printf ( "msgbuf: %s\n", msgbuf );
	if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
		perror("send message error! regist failed");
		exit(EXIT_FAILURE); 
	}
	/* GAME START */
	int n = 0;
	struct player_msg player[8];
	while ( true ) {
		//		write(STDOUT_FILENO, msgbuf, n);
		/* seat-info-msg */
		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
			perror("seat info msg recv error");
		}

		/* msg handle */
		char header[64];
		int i = 0, j = 0;
		while (msgbuf[i] != '\n' && msgbuf[i] != '\0') {
			header[j++] = msgbuf[i++];
		}
		i ++;                                       /* ignore the \n */
		int msgno = 0;
		for (int i = 0; i < 11; ++i) {
			if (strcmp(header, infomsg[i])) {
				msgno = i;
				break;
			}
		}
		switch (msgno) {
			case SEAT:								    /* seat/      */
				seat_msg(player, msgbuf);
				break;
			case BLIND:                                 /* blind/     */
				blind_msg(player, msgbuf);
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case HOLD:                                  /* hold/      */
				struct cards hold[2];
				hold_msg(hold, msgbuf);
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case INQUIRE:                               /* inquire/   */
				memset(msgbuf, 0, sizeof(msgbuf));
				sprintf(msgbuf, "call \n");
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
					perror("send message error! action failed");
					exit(EXIT_FAILURE); 
				}
				break;
			case FLOP:                                  /* flop/      */
				struct cards flop[3];
				flop_msg(flop, msgbuf);
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break; 
			case TURN:                                  /* turn/      */
				struct cards turn[1];
				turn_msg(turn, msgbuf);
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case RIVER:                                 /* river/     */
				struct cards river[1];
				river_msg(river, msgbuf);
				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case SHOWDOWN:                              /* showdown/  */
				break;
			case POTWIN:                                /* pot-win/   */
				break;
			case NOTIFY:                                /* notify/    */
				break;
			case GAMEOVER:                              /* game-over/ */
				break;
			default:
				break;
		}

//		/* blind-msg  */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("blind msg recv error");
//		}
//
//		/* hold-cards-msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("hold cards msg recv error");
//		}
//
//		/* inquire-msg and action msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("inquire msg recv error");
//		}
//
//		memset(msgbuf, 0, sizeof(msgbuf));
//		sprintf(msgbuf, "call \n");
//		printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
//		if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
//			perror("send message error! regist failed");
//			exit(EXIT_FAILURE); 
//		}
//		/* flop-msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("flop msg recv error");
//		}
//
//		/* inquire-msg and action msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("inquire msg recv error");
//		}
//
//		memset(msgbuf, 0, sizeof(msgbuf));
//		sprintf(msgbuf, "call \n");
//		printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
//		if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
//			perror("send message error! action failed");
//			exit(EXIT_FAILURE); 
//		}
//		/* turn msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("turn msg recv error");
//		}
//
//		/* inquire-msg and action msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("inquire msg recv error");
//		}
//
//		memset(msgbuf, 0, sizeof(msgbuf));
//		sprintf(msgbuf, "call \n");
//		printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
//		if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
//			perror("send message error! action failed");
//			exit(EXIT_FAILURE); 
//		}
//		/* river msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("river msg recv error");
//		}
//
//		/* inquire-msg and action msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("inquire msg recv error");
//		}
//
//		memset(msgbuf, 0, sizeof(msgbuf));
//		sprintf(msgbuf, "call \n");
//		printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
//		if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
//			perror("send message error! action failed");
//			exit(EXIT_FAILURE); 
//		}
//		/* showdown msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("showdown msg recv error");
//		}
//
//		/* pot win msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("pot win msg recv error");
//		}
//
//		/* game over msg */
//		if ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) < 0 )) {
//			perror("seat info msg recv error");
//		}
//
	}

	close(sockfd);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
