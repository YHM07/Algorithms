/**
 * @file msghand.cc
 * @brief deal with the msg from socket
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */
//#include "protocol.h"
#include "msghandle.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>


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
	char pid[10];
	for (int i = 0; i < 2; ++i) {
		sscanf(blindmsg[i+1], "%[0-9]: %d", 
				pid, &bet);
		player[i].pid = atoi(pid);
	}

	return 0;
}

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
