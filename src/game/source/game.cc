/**
 * @file game.cc
 * @brief HUAWEI game
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/21/2015
 */
//#include "protocol.h"
#include "msghandle.h"
#include "gamelogic.h"
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

#define	BUFFSIZE	4096 /*  */

//struct player_msg;
//struct cards;
struct player_msg gplayer[8];
//int					ghold[2];
//int					gflop[3];
//int					gturn[1];
//int					griver[1];
int					gcards[7];



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
	while (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))
		   	== -1) {
		perror("connect error");
//		exit(EXIT_FAILURE);
		usleep(100*1000);
	}
	printf ( "connect succeed\n" );

	/* registration  */
	char msgbuf[BUFFSIZE] = {'\0'};
	char pname[] = "hellokity";
//	sprintf(msgbuf, "reg: %d %s need_notify \n", pid, pname);
	sprintf(msgbuf, "reg: %d %s \n", pid, pname);
	printf ( "msgbuf: %s\n", msgbuf );
//	if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
	int n = 0;
	if ((n = send(sockfd, msgbuf, strlen(msgbuf), 0)) == -1) {
		perror("send message error! regist failed");
//		exit(EXIT_FAILURE); 
	}
//	printf ( "send reg msg number %d %d\n",n, __LINE__ );

#ifndef CALL 
#define	CALL	2			/* call  */
#endif
	/* GAME START */
	while ( true ) {
		memset(msgbuf, 0, sizeof(msgbuf));
		while ((n = recv(sockfd, msgbuf, BUFFSIZE, 0) <= 0 )) {
			if (n < 0) 
				perror("info msg recv error");
			else 
				continue;
		}

		/* msg handle */
		int msgno;
		static int iflag = 0;                   /* my cards */
//		static int oflag = 0;                   /* others cards */
		int oflag = 0;                   /* others cards */
		msgno = msghandle(msgbuf, &iflag, &oflag);
		printf ( "flag = %d %d\n", iflag, __LINE__ );
//		printf ( "msgno = %d %d\n", msgno, __LINE__ );

		memset(msgbuf, 0, sizeof(msgbuf));
		switch (iflag) {
			case STRAIGHT_FLUSH:
				sprintf(msgbuf, "all_in \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case FOUR_OF_A_KIND:
				sprintf(msgbuf, "raise \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case FULL_HOUSE:
				sprintf(msgbuf, "call \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case FLUSH:
				sprintf(msgbuf, "call \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case STRAIGHT:
				sprintf(msgbuf, "call \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case THREE_OF_A_KIND:
				sprintf(msgbuf, "call \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case TWO_PAIR:
				if (oflag > CALL) {
					sprintf(msgbuf, "fold \n");
				} else {
					sprintf(msgbuf, "call \n");
				}
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case ONE_PAIR:
				if (oflag > CALL) {
					sprintf(msgbuf, "fold \n");
				} else {
					sprintf(msgbuf, "call \n");
				}
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			case HIGH_CARD:
				sprintf(msgbuf, "fold \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
			default:
				sprintf(msgbuf, "fold \n");
//				printf ( "msgbuf: %s %d \n", msgbuf, __LINE__ );
				break;
		}

#ifndef INQUIRE
#define INQUIRE 3
#endif
		if (msgno == INQUIRE) {
			if ((n = send(sockfd, msgbuf, strlen(msgbuf), 0)) == -1) {
				perror("send msg error");
				printf ( "send msg number %d %d\n",n, __LINE__ );
			}
		}


#ifndef GAMEOVER 
#define GAMEOVER 10
#endif
		if (msgno == GAMEOVER) {
			close(sockfd);
			break;
		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
