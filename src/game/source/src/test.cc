/**
 * @file test.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/22/2015
 */


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include <stdlib.h>
int seat_msg(struct player_msg player[], const char *msgbuf);
int msghand(const char *msg, char *info );
struct player_msg {
	int		pid;
	int		jetton;
	int		money;
//	char   *status;                             /* player,button ,big blind and small blind */
};
const char *msg[] = {"seat/ ",
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

/**
 * @brief	main 
 *
 * @param	argc
 * @param	argv[]
 *
 * @return	
 */
	int
main ( int argc, char *argv[] )
{	
//	char *seatmsg[10] = {"seat/ \n",
//						"button: 1111 1000 8000 \n",
//						"small button: 2222 1000 8000 \n",
//						"big blind: 3333 1000 8000 \n",
//						"4444 1000 8000 \n",
//						"5555 1000 8000 \n",
//						"6666 1000 8000 \n",
//						"7777 1000 8000 \n",
//						"8888 1000 8000 \n",
//						"/seat \n"
//	};
	char seatmsg[] = "seat/ \nbutton: 1111 1000 8000 \nsmall button: 2222 1000 8000 \nbig blind: 3333 1000 8000 \n4444 1000 8000 \n5555 1000 8000 \n6666 1000 8000 \n7777 1000 8000 \n8888 1000 8000 \n/seat \n";
//	seat_msg(seatmsg);
	char info[10];
	struct player_msg player[8];
	memset(player, 0, sizeof(player));
	msghand(seatmsg, info);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief  seat_msg seat info msg 
 *
 * @param  sockfd socket id 
 * @param  player[] player info msg
 *
 * @return  
 */
int seat_msg(struct player_msg player[], const char *msgbuf)
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
	for (int i = 0; i < 10; ++i) {
		printf ( "%s\n",seatmsg[i] );
	}
	m = m - 2;                                  /* the number of valid player */
	/* test info */
	int o,p,q;
	int pid;
	char pch[20];
	sscanf(seatmsg[1], "%[^:]: %d %d %d", pch, &o, &p, &q);
	printf ( "%s %d %d %d\n",pch, o, p, q );

	printf ( "m = %d \n", m );
	if (m >= 3) {
		for (int i = 0; i < 3; ++i) {
			printf ( "seatmsg[%d] = %s\n", i+1,  seatmsg[i+1] );
			sscanf(seatmsg[i+1], "%*[a-z: ] %d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
		for (int i = 3; i < m; ++i) {
			printf ( "seatmsg[%d] = %s\n", i+1,  seatmsg[i+1] );
			sscanf(seatmsg[i+1], "%d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
	} else {
		for (int i = 0; i < 2; ++i) {
			sscanf(seatmsg[i+1], "%*[a-z: ] %d %d %d", 
					&player[i].pid, &player[i].jetton, &player[i].money);
		}
	}

	for (int i = 0; i < m; ++i) {
		printf ( "player[%d] = %d %d %d\n",
				i, player[i].pid, player[i].jetton, player[i].money);
	}

}

/**
 * @brief	msghand 
 *
 * @param	msg
 * @param	info 
 *
 * @return	
 */
int msghand(const char *msgbuf, char info[] ) 
{
	char header[64];
	int i = 0, j = 0;
	while (msgbuf[i] != '\n' && msgbuf[i] != '\0') {
		header[j++] = msgbuf[i++];
	}
	i ++;                                       /* ignore the \n */
	int msgno;
	for (int i = 0; i < 11; ++i ) {
		if (strcmp(header, msg[i]) == 0) {
			msgno = i;
			printf ( "msgno = %d\n", msgno );
			break;
		} else {
			msgno = 12;
		}
	}
	switch (msgno) {
		case 0:
			struct player_msg player[8];
			seat_msg(player, msgbuf);
//			info = "seat";
			break;
		default :
			break;
	}
	return msgno;
}

