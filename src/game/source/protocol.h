/**
 * @file protocol.h
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/22/2015
 */

#ifndef	_PROTOCOL_H_
#define _PROTOCOL_H_

struct cards {
	char  color[9];                            /* SPADES HEARTS CLUBS DIAMONDS */
	int   point;
};
struct player_msg {
	int		pid;
	int		jetton;
	int		money;
//	char   *status;                             /* player,button ,big blind and small blind */
	struct cards holdcards[2];
};

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
	"game-over/ "
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
#define	GAMEOVER	10			/* game-over/ */



#endif                                          /* _PROTOCOL_H_ */
