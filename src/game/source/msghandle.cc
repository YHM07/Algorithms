/**
 * @file msghand.cc
 * @brief deal with the msg from socket
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/23/2015
 */
//#include "protocol.h"
#include "msghandle.h"
#include "gamelogic.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

extern int action_msg(int card[], int m);
extern int judgement(int m);

int color_msg(char color[]);
int point_msg(char ch);
int card_combination(int card[], int m);

extern const char *colordata[];
extern int gcards[];
struct cards;
//struct player_msg;
extern struct player_msg gplayer[];
const char *infomsg[] = {"seat/ ",
	"blind/ ",
	"hold/ ",
	"inquire/ ",
	"flop/ ",
	"turn/ ",
	"river/ ",
	"showdown/ ",
	"pot-win/ ",
	"notify/ ",
	"game-over "
};

/* msg number */
#define	SEAT		0			/* seat/      */
#define	BLIND		1			/* blind/     */
#define	HOLD		2			/* hold/	  */
#define	INQUIRE		3			/* inquire/	  */
#define	FLOP		4    		/* flop/	  */
#define	TURN		5    		/* turn/	  */
#define	RIVER		6    		/* river/	  */
#define	SHOWDOWN	7    		/* showdown/  */
#define	POTWIN		8    		/* pot-win/   */
#define	NOTIFY		9    		/* notify/    */
#define	GAMEOVER	10			/* game-over  */


/**
 * @brief	msghandle 
 *
 * @param	msg
 *
 * @return	
 */
int msghandle(const char *msg, int *flag)
{
	int start = 0;
	int end   = 0;
	int msgno = 12;
//	static int i = 1;
	printf ( "the received msg is (%s) length = %lu\n", 
			msg, strlen(msg) );
	while (msg[start] != '\0') {
//		printf ( "i = %d \n", i++ );
		char header[128];
		memset(header, 0, sizeof(header));
		sscanf(&msg[start], "%[^\n]", header);
		start += strlen(header);
		header[start] = '\0';
		start ++;                                   /* ignore the \n */ 
		for (int i = 0; i < 11; ++i) {
			if (strcmp(header, infomsg[i]) == 0) {
				msgno = i;
//				printf ( "msgno = %d\n",msgno );
				break;
			}
		}
		const char *pmsgbuf = &msg[start];
		switch (msgno) {
			case SEAT:								    /* seat/      */
				end = seat_msg(gplayer, pmsgbuf);
				break;
			case BLIND:                                 /* blind/     */
				end = blind_msg(gplayer, pmsgbuf);
				break;
			case HOLD:                                  /* hold/      */
				struct cards hold[2];
				end = hold_msg(hold, pmsgbuf);
				int ihold[2];
				for (int i = 0; i < 2; ++i) {
					ihold[i] = color_msg(hold[i].color) +
						point_msg(hold[i].point);
					printf ( "ihold = %d\n",ihold[i] );
				}
				int tmp;
				tmp = ihold[0] ^ ihold[1];
				if ((tmp & 0xF0) == 0x00) {       /* FLUSH */

				}
				if ((tmp & 0x0F) == 0x00) {         /* ONE_PAIR */
					*flag = ONE_PAIR;
				} 
				card_combination(ihold, 2);
//				*flag = judgement(2);
				break;
			case INQUIRE:                               /* inquire/   */
				end = inquire_msg(pmsgbuf);
				break;
			case FLOP:                                  /* flop/      */
				struct cards flop[3];
				end = flop_msg(flop, pmsgbuf);
				int iflop[3];
				for (int i = 0; i < 3; ++i) {
					iflop[i] = color_msg(flop[i].color) +
						point_msg(flop[i].point);
					printf ( "iflop = %d\n",iflop[i] );
				}
				card_combination(iflop, 3);
//				*flag = judgement(5);
				break; 
			case TURN:                                  /* turn/      */
				struct cards turn[1];
				end = turn_msg(turn, pmsgbuf);
				int iturn[1];
				iturn[0] = color_msg(turn[0].color) + 
					point_msg(turn[0].point);
				card_combination(iturn, 1);
				//				*flag = judgement(6);
				break;
			case RIVER:                                 /* river/     */
				struct cards river[1];
				end = river_msg(river, pmsgbuf);
				int iriver[1];
				iriver[0] = color_msg(river[0].color) + 
					point_msg(river[0].point);
				card_combination(iriver, 1);
				//				*flag = judgement(7);
				break;
			case SHOWDOWN:                              /* showdown/  */
				end = showdown_msg(pmsgbuf);
				break;
			case POTWIN:                                /* pot-win/   */
				end = potwin_msg(pmsgbuf);
				break;
			case NOTIFY:                                /* notify/    */
				break;
			case GAMEOVER:                              /* game-over/ */
				return GAMEOVER;
				break;
			default:
				break;
		}
		start += end;

	}
	return msgno;
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
	int length  = 0;
	int m = 0;
	int newline = 0;
	char seatmsg[128];
	while (true) {
		memset(seatmsg, 0, sizeof(seatmsg));
		sscanf(&msgbuf[length], "%[^\n]", seatmsg);
		int end = strlen(seatmsg);
		length += end;
		seatmsg[end] = '\0';
		length ++;                                   /* ignore the \n */ 
//		printf ( "seatmsg = %s \n", seatmsg );
		if (strcmp(seatmsg, "/seat ") == 0) {
			printf ( "seat return\n" );
			break;
		}
		newline ++;
		if (newline > 0 && newline < 4) {
			sscanf(seatmsg, "%*[a-z: ] %d %d %d",
					&player[m].pid, &player[m].jetton, &player[m].money);
			m ++;
		} else {
			if (newline >= 4) {
				sscanf(seatmsg, "%d %d %d",
						&player[m].pid, &player[m].jetton, &player[m].money);
				m ++;
			}
		}

		//		printf ( "player : %d %d %d\n", 
		//				player[m-1].pid, player[m-1].jetton, player[m-1].money);

	}
	printf ( "length = %d %d\n", length, __LINE__ );
	return length;
}

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
	int length = 0;
	int m = 0;
	char blindmsg[64];
	while (true) {
		memset(blindmsg, 0, sizeof(blindmsg));
		sscanf(&msgbuf[length], "%[^\n]", blindmsg);
		int end = strlen(blindmsg);
		length += end;
		blindmsg[end] = '\0';
		m ++;
		length ++;                                   /* ignore the \n */
//		printf ( "blindmsg = %s\n", blindmsg );
		if (strcmp(blindmsg, "/blind ") == 0) {
			break;
		}
	}


	return length;
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
	int length = 0;
	int m = 0;
	char flopmsg[16];
	while (true) {
		memset(flopmsg, 0, sizeof(flopmsg));
		sscanf(&msgbuf[length], "%[^\n]", flopmsg);
		int end = strlen(flopmsg);
		length += end;
		flopmsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "flopmsg = %s\n", flopmsg );
		if (strcmp(flopmsg, "/flop ") == 0) {
			break;
		}
		sscanf(flopmsg, "%s %c", flop[m].color, &flop[m].point);
		m ++;
	}
	return length;
}

/**
 * @brief  holdcards_msg hold card msg
 *
 * @param  holdcards[] hold cards
 * @param  msgbuf the msg from server
 *
 * @return  
 */
int hold_msg(struct cards hold[], const char *msgbuf)
{
	int length = 0;
	int m = 0;
	char holdmsg[16];
	while (true) {
		memset(holdmsg, 0, sizeof(holdmsg));
		sscanf(&msgbuf[length], "%[^\n]", holdmsg); 
		int end = strlen(holdmsg);
		length += end;
		holdmsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "holdmsg = %s\n", holdmsg );
		if (strcmp(holdmsg, "/hold ") == 0) {
			break;
		}
		sscanf(holdmsg, "%s %c", hold[m].color, &hold[m].point);
		m ++;
	}
	return length ;
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
	int length = 0; 
	int m = 0;
	char rivermsg[16];
	while (true) {
		memset(rivermsg, 0, sizeof(rivermsg));
		sscanf(&msgbuf[length], "%[^\n]", rivermsg); 
		int end = strlen(rivermsg);
		length += end;
		rivermsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "rivermsg = %s\n", rivermsg);
		if (strcmp(rivermsg, "/river ") == 0) {
			break;
		}
		sscanf(rivermsg, "%s %c", river[m].color, &river[m].point);
		m ++;
	}
	return length ;
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
	int length = 0;
	int m = 0;
	char turnmsg[16];
	while (true) {
		memset(turnmsg, 0, sizeof(turnmsg));
		sscanf(&msgbuf[length], "%[^\n]", turnmsg); 
		int end = strlen(turnmsg);
		length += end;
		turnmsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "turnmsg = %s\n", turnmsg );
		if (strcmp(turnmsg, "/turn ") == 0) {
			break;
		}
		sscanf(turnmsg, "%s %c", turn[m].color, &turn[m].point);
		m ++;
	}
	return length;
}

/**
 * @brief  inquire_msg 
 *
 * @param  msgbuf
 *
 * @return  
 */
int inquire_msg(const char *msgbuf)
{
	int length = 0;
	int m = 0;
	char inquiremsg[128];
//	printf ( "msgbuf = %s\n", msgbuf );
	while (true) {
		memset(inquiremsg, 0, sizeof(inquiremsg));
		sscanf(&msgbuf[length], "%[^\n]", inquiremsg);
		int end = strlen(inquiremsg);
		length += end;
		inquiremsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "inquiremsg = %s\n", inquiremsg );
		if (strcmp(inquiremsg, "/inquire ") == 0) {
			break;
		}
		m ++;
	}
	return length;
}

/**
 * @brief  showdown_msg 
 *
 * @param  msg
 *
 * @return  
 */
int showdown_msg(const char *msgbuf)
{
	int length = 0;
	int m = 0;
	char showdownmsg[128];
	while (true) {
		memset(showdownmsg, 0, sizeof(showdownmsg));
		sscanf(&msgbuf[length], "%[^\n]", showdownmsg);
		int end = strlen(showdownmsg);
		length += end;
		showdownmsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "showdownmsg = %s\n", showdownmsg );
		if (strcmp(showdownmsg, "/showdown ") == 0) {
			break;
		}
		m ++;
	}
	return length;
}

/**
 * @brief  potwin_msg 
 *
 * @param  msg
 *
 * @return  
 */
int potwin_msg(const char *msgbuf)
{
	int length = 0;
	int m = 0;
	char potwinmsg[128];
	while (true) {
		memset(potwinmsg, 0, sizeof(potwinmsg));
		sscanf(&msgbuf[length], "%[^\n]", potwinmsg);
		int end = strlen(potwinmsg);
		length += end;
		potwinmsg[end] = '\0';
		length ++;                                   /* ignore the \n */
//		printf ( "potwinmsg = %s\n", potwinmsg );
		if (strcmp(potwinmsg, "/pot-win ") == 0) {
			break;
		}
		m ++;
	}
	return length;
}

/**
 * @brief  color_msg 
 *
 * @param  color[]
 *
 * @return  
 */
int color_msg(char color[])
{
	int i = 0;
	for (i = 0; i < 4; ++i) {
		if (strcmp(color, colordata[i]) == 0) {
			break;
		}
	}
	switch (i) {
		case DIAMONDS:
			return (DIAMONDS << 4) & LOGIC_MASK_COLOR;
		case CLUBS:
			return (CLUBS    << 4) & LOGIC_MASK_COLOR;
		case HEARTS:
			return (HEARTS   << 4) & LOGIC_MASK_COLOR;
		case SPADES:
			return (SPADES   << 4) & LOGIC_MASK_COLOR;
		default:
			break;
	}
	return -1;
}

/**
 * @brief  point_msg 
 *
 * @param  ch
 *
 * @return  
 */
int point_msg(char ch)
{
	switch (ch) {
		case 'J':
			return 0x0B;
		case 'Q':
			return 0x0C;
		case 'K':
			return 0x0D;
		case 'A':
			return 0x0E;
		default:
			if (ch == '1') {
				return 10;
			}
			return ch - '0';
	}
	return 0;
}

/**
 * @brief  card_combination 
 *
 * @param  card[]
 * @param  m
 *
 * @return  
 */
int card_combination(int cards[], int m)
{
	static int cardsnum = 0;
	for (int i = 0; i < m; ++i) {
		printf ( "cardsnum = %d\n", cardsnum );
		gcards[cardsnum++] = cards[i];
	}
	if (cardsnum >= 5) {
		sort(gcards, cardsnum);
		if (cardsnum >= 7)
			cardsnum = 0;
	}
//	for (int i = 0; i < cardsnum; ++i) {
//		printf ( "gcards = %d\n", gcards[i] );
//	}
	return 0;
}
