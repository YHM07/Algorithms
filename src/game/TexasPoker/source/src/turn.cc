/**
 * @file turn.cc
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
 * @brief  turn_msg 
 *
 * @param  turn[]
 * @param  msgbuf
 *
 * @return  
 */
int turn_msg(struct cards turn[], const char *msgbuf)
{
	int i = 0;
	int m = 0, n = 0;
	char turnmsg[3][16];
	memset(turnmsg, 0, sizeof(turnmsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			turnmsg[m][n++] = msgbuf[i++];
		}
		turnmsg[m][n] = '\0';
		m ++;
		i ++;                                   /* ignore the \n */
	}
	m = m - 2;                                  /* the number of valid msg*/
	for (int i = 0; i < 1; ++i) {
		sscanf(turnmsg[i+1], "%s %d", 
				turn[i].color, &turn[i].point);
	}
	return 0;
}
