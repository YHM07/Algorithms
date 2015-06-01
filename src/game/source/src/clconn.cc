/**
 * @file clconn.cc
 * @brief 支持重试的连接
 * @author W.Richard Stevens,APUE2,P450
 * @version v1.0
 * @date 2015-05-09
 */

//#include "apue.h"
#include <sys/socket.h>
#include <unistd.h>

#define MAXSLEEP 128

int
connect_retry(int sockfd, const struct sockaddr *addr, socklen_t alen)
{
	int nsec;

	/*
	 * Try to connect with exponential backoff.
	 */
	for (nsec = 1; nsec <= MAXSLEEP; nsec <<= 1) {
		if (connect(sockfd, addr, alen) == 0) {
			/*
			 * Connection accepted.
			 */
			return(0);
		}

		/*
		 * Delay before trying again.
		 */
		if (nsec <= MAXSLEEP/2)
			sleep(nsec);
	}
	return(-1);
}

