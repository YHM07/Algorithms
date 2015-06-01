/**
 * @file blind.cc
 * @brief blind msg
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */

#include "protocol.h"
#include <stdio.h>
#include <string.h>

struct player_msg;

/**
 * @brief	blind_msg blind info msg
 *
 * @param	player[] valid player
 * @param	msgbuf the msg from server
 *
 * @return	
 */
int blind_msg(struct player_msg	*player, const char *msgbuf)
{
	int i = 0;
	int m = 0, n = 0;
	char blindmsg[4][64];
	memset(blindmsg, 0, sizeof(blindmsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			blindmsg[m][n++] = msgbuf[i++];
		}
		blindmsg[m][n] = '\0';
		m ++;
		i ++;                                   /* ignore the \n */
	}
	m = m - 2;                                  /* the number of valid player */
	int bet;
	for (int i = 0; i < 2; ++i) {
		sscanf(blindmsg[i+1], "%[0-9]: %d", 
				&player[i].pid, &bet);
	}

	return 0;
}
