/**
 * @file hold.cc
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */

#include "protocol.h"
#include <stdio.h>
#include <string.h>

struct player_msg;
struct cards;

/**
 * @brief  holdcards_msg hold card msg
 *
 * @param  holdcards[] hold cards
 * @param  msgbuf the msg from server
 *
 * @return  
 */
int hold_msg(struct cards holdcards[], const char *msgbuf)
{
	int i = 0;
	int m = 0, n = 0;
	char holdmsg[4][16];
	memset(holdmsg, 0, sizeof(holdmsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			holdmsg[m][n++] = msgbuf[i++];
		}
		holdmsg[m][n] = '\0';
		m ++;
		i ++;                                   /* ignore the \n */
	}
	m = m - 2;                                  /* the number of valid msg*/
	for (int i = 0; i < 2; ++i) {
		sscanf(holdmsg[i+1], "%[^:]: %d", 
				holdcards[i].color, &holdcards[i].point);
	}
	return 0;
}
