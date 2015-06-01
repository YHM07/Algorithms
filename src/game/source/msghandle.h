/**
 * @file msghandle.h
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/24/2015
 */

#ifndef _MSGHANDLE_H
#define _MSGHANDLE_H

//struct cards;
//struct player_msg;
struct cards {
	char  color[9];                            /* SPADES HEARTS CLUBS DIAMONDS */
	char  point;                                /*  */
};
struct player_msg {
	int		pid;
	int		jetton;
	int		money;
//	char   *status;                             /* player,button ,big blind and small blind */
//	struct cards holdcards[2];
};

int msghandle(const char *msg, int *flag);
int seat_msg(struct player_msg	player[], const char *msgbuf);
int blind_msg(struct player_msg	*player, const char *msgbuf);
int hold_msg(struct cards hold[], const char *msgbuf);
int turn_msg(struct cards turn[], const char *msgbuf);
int river_msg(struct cards river[], const char *msgbuf);
int flop_msg(struct cards flop[], const char *msgbuf);
int inquire_msg(const char *msgbuf);
int showdown_msg(const char *msg);
int potwin_msg(const char *msg);

#endif                                          /*_MSGHANDLE_H  */
