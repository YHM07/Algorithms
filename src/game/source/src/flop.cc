/**
 * @file flop.cc
 * @brief flop msg
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */

#include "protocol.h"
#include <stdio.h>
#include <string.h>
struct cards;

/**
 * @brief  flop_msg flop msg
 *
 * @param  flop[] 
 * @param  msgbuf
 *
 * @return  
 */
int flop_msg(struct cards flop[], const char *msgbuf)
{
	int i = 0;
	int m = 0, n = 0;
	char flopmsg[5][16];
	memset(flopmsg, 0, sizeof(flopmsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			flopmsg[m][n++] = msgbuf[i++];
		}
		flopmsg[m][n] = '\0';
		m ++;
		i ++;                                   /* ignore the \n */
	}
	m = m - 2;                                  /* the number of valid msg*/
	for (int i = 0; i < 3; ++i) {
		sscanf(flopmsg[i+1], "%s %d", 
				flop[i].color, &flop[i].point);
	}
	return 0;
}
