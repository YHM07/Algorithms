/**
 * @file client.cc
 * @brief 练习getaddrinfo
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/09/2015
 */

#include "inc/clconn.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdlib.h>

#define	BUFFSIZE	128 /*  */

//int connect_retry(int , const struct sockaddr *, socklen_t );
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
	struct addrinfo		*ailist,*aip;
	struct addrinfo		hint;
	struct sockaddr_in *sinp;
	const char	       *addr;
	int					sockfd;

	if (argc != 6) {
		fprintf(stderr,"usage: %s serviceIP serviceport clientIP clientport clientID", 
				argv[0]);
		printf ( "\n" );
		exit(EXIT_FAILURE);
	}
	memset(&hint,0,sizeof(hint));
	hint.ai_flags  = AI_CANONNAME;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_addrlen  = 0;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	
	int err;
	if ((err = getaddrinfo(argv[1],argv[2],&hint,&ailist)) != 0) {
		fprintf ( stderr, "getaddrinfo error %s\n", gai_strerror(err) );
		exit(EXIT_FAILURE);
	}
	for (aip = ailist; aip != NULL; aip = aip->ai_next) {
		sinp = (struct sockaddr_in *)aip->ai_addr;
		char buf[INET_ADDRSTRLEN];
		addr = inet_ntop(AF_INET, &sinp->sin_addr, buf, INET_ADDRSTRLEN);
		printf ( "address：%s\n", addr?addr:"unknown" );
		printf ( "port:%d\n", ntohs(sinp->sin_port) );

		sockfd = socket(aip->ai_family, aip->ai_socktype, 
				aip->ai_protocol);
		if (sockfd == -1) {
			err = errno;
			continue;
		}
//		if (connect(sockfd, aip->ai_addr, aip->ai_addrlen) != -1) {
//			break;
//		}
		if (connect_retry(sockfd, aip->ai_addr, aip->ai_addrlen) == -1) {
			err = errno;
		} else {
			printf ( "connect succeeded\n" );
			break;
		}
	}
	if (aip == NULL) {			/* No address succeeded */
		fprintf (stderr, "cannot connect to %s: %s\n", argv[1], 
			  strerror(err));
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(ailist);
	ailist = NULL;

	/* registration  */
	char msgbuf[BUFFSIZE] = {'\0'};
	int  pid = atoi(argv[5]);
	char pname[] = "all_in";
	sprintf(msgbuf, "reg: %d %s need_notify \n", pid, pname);
	printf ( "msgbuf: %s\n", msgbuf );
	if (send(sockfd, msgbuf, BUFFSIZE, 0) == -1) {
		perror("send message error! regist failed");
		exit(EXIT_FAILURE); 
	}
	/* receiver */
	int n = 0;
	while ((n = recv(sockfd, msgbuf, BUFFSIZE, 0)) > 0) {
		write(STDOUT_FILENO, msgbuf, n);
	}
	if (n < 0) {
		perror("recv error");
	}


	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

