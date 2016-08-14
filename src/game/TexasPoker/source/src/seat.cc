/**
 * @file seat.cc
 * @brief seat info msg
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/22/2015
 */

#include "protocol.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

struct player_msg;

/**
 * @brief  seat_msg seat info msg 
 *
 * @param  player[] player info msg
 * @param  msgbuf the seat info msg
 *
 * @return the number of valid player 
 */
int seat_msg(struct player_msg	player[], const char *msgbuf)
{

	int i = 0;
	int m = 0, n = 0;
	char seatmsg[10][128];
	memset(seatmsg, 0, sizeof(seatmsg));
	while ( msgbuf[i] != '\0') {
		n = 0;
		while (msgbuf[i] != '\n' ) {
			seatmsg[m][n++] = msgbuf[i++];
		}
		seatmsg[m][n] = '\0';
		m ++;
		i ++;
	}
	m = m - 2;                                  /* the number of valid player */
//	memset(player, 0, sizeof(player)*m);
	if (m >= 3) {
		for (int i = 0; i < 3; ++i) {
			sscanf(seatmsg[i+1], "%*[a-z: ] %d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
		for (int i = 3; i < m; ++i) {
			sscanf(seatmsg[i+1], "%d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
	} else {
		for (int i = 0; i < 2; ++i) {
			sscanf(seatmsg[i+1], "%*[a-z: ] %d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
	}

	return m;


}
