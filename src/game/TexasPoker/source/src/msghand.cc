/**
 * @file msghand.cc
 * @brief deal with the msg from socket
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */
#include "protocol.h"
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

struct player_msg;

extern player;

extern int blind_msg(struct player_msg	player[], const char *msgbuf);
/*
 * @brief	msghand deal with the msg from socket 
 *
 * @param	msg
 *
 * @return	
 */
int msghand(const char *msg ) 
{
	char header[64];
	int i = 0, j = 0;
	while (msg[i] != '\n' && msg[i] != '\0') {
		header[j++] = msg[i++];
	}
	i ++;                                       /* ignore the \n */
	int msgno = 0;
	for (int i = 0; i < 11; ++i) {
		if (strcmp(header, infomsg[i])) {
			msgno = i;
			break;
		}
	}
	switch (msgno) {
		case SEAT:								    /* seat/      */
			seat_msg(player, msg);
			break;
		case BLIND:                                 /* blind/     */
			blind_msg(player, msg);
			break;
		case HOLD:                                  /* hold/      */
			break;
		case INQUIRE:                               /* inquire/   */
			break;
		case FLOP:                                  /* flop/      */
			break; 
		case TURN:                                  /* turn/      */
			break;
		case RIVER:                                 /* river/     */
			break;
		case SHOWDOWN:                              /* showdown/  */
			break;
		case POTWIN:                                /* pot-win/   */
			break;
		case NOTIFY:                                /* notify/    */
			break;
		case GAMEOVER:                              /* game-over/ */
			break;
		default:
			break;
	}
	return msgno;
}

