/**
 * @file river.cc
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */

#include "protocol.h"
#include <stdio.h>
#include <string.h>
struct cards;

/**
 * @brief  river_msg 
 *
 * @param  river[]
 * @param  msgbuf
 *
 * @reriver  
 */
int river_msg(struct cards river[], const char *msgbuf)
{
	int i = 0;
	int m = 0, n = 0;
	char rivermsg[3][16];
	memset(rivermsg, 0, sizeof(rivermsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			rivermsg[m][n++] = msgbuf[i++];
		}
		rivermsg[m][n] = '\0';
		m ++;
		i ++;                                   /* ignore the \n */
	}
	m = m - 2;                                  /* the number of valid msg*/
	for (int i = 0; i < 1; ++i) {
		sscanf(rivermsg[i+1], "%s %d", 
				river[i].color, &river[i].point);
	}
	return 0;
}
