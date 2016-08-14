/**
 * @file chess.cc
 * @brief 五子棋
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/13/2016
 */

#include <stdio.h>

#include <stdlib.h>

#define	N	19			/* 棋盘大小 19*19 */
#define	HUMAN 0			/* 游戏玩家 */
#define	PC	1			/* 电脑玩家*/

typedef int status ;
status	WIN  = 1;                               /* 胜利者 */
status	QUIT = 2;                               /* 游戏结束 */
status	RES	 = 3;                               /* 悔棋，rescinded */

int Player = PC;                                 /* 0: 游戏玩家；1：电脑玩家 */

int CreateBoard ( char (*board)[N] );
int PrintBoard ( char (*board)[N] );
//int PrintBoard ( char (*board)[N], int row, int col );
int PrintInfo ( status flag, int player  );
status PlayChess( char (*board)[N], int player, int *x, int *y );
status CheckBoard( char (*board)[N], int player, int *x, int *y );

/**
 * @brief  main 
 *
 * @param  argc
 * @param  argv[]
 *
 * @return  
 */
int main ( int argc, char *argv[] ) { 
	char board[N][N] = { {0,0} };
//	int *player = &Player;
	int x = 0, y =0;
	int flag = 2;
	status s = -1;
	CreateBoard(board);
	while ( true ) {
		PrintBoard(board);
		PrintInfo(flag, Player);
		if ( s == WIN ) {
			printf ( "\033[33mSome one win!\n\033[0m" );
			break;
		}
		s = PlayChess(board, Player, &x, &y);
		if ( s == -1 ) continue;
		if ( s == RES ) {
			printf ( "Someone rescinded!\n" );
		}
		if ( s == QUIT ) {
			printf ( "Gave Over\n" );
			break;
		}
		s =  CheckBoard(board, Player, &x,&y);
		Player = ( Player + 1 ) % 2;

	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

int  CreateBoard ( char (*board)[N] ) {
	int i = 0, j = 0;                            /* 定义棋盘行列	 */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			board[i][j] = '-';
		}
	}
	return 0;
}		/* -----  end of function CreateBoard  ----- */

//int PrintBoard ( char (*board)[N], int row, int col ) {
int PrintBoard ( char (*board)[N] ) {
	int i,j;                                    /* 定义棋盘行列	 */
	printf ( "\033[2J" );
	printf ( "\033[32m--------------------------Welcome to My Chess!-------------------------------\033[0m\n" );
	printf ( " * " );
	for (i = 0; i < N; i++) {
		printf ( "%-2d  ", i );                    /* 显示列号 */
	}
	printf ( "\n" );
	for ( i = 0; i < N; i++ ) {
		printf ( "%2d", i);
		for (j = 0; j < N; j++) {
			printf ( "%2c  ", board[i][j] );
//			printf ( "\033[%d*2;%dH\033[5m%2c\033[0m", i, j, board[i][j] );
		}	
		printf ( "\n" );
	}
//	printf ( "\033[5m%2c\033[0m",  board[3][3] );
	printf ( "\033[32m-----------------------------------------------------------------------------\033[0m\n" );

	return 0;
}		/* -----  end of function PrintBoard  ----- */


int PrintInfo ( status flag, int player  ) {
	if ( flag == WIN ) {
		if ( player == HUMAN) {
			printf ( "\033[32m People Win! Good Job!\n\033[3m" );
		 } else {
			printf ( "\033[32m PC Win! Come on!\n\033[3m" );
		 }
	} else {
		if ( flag == -1 ) {
			printf ( "Something wrong\n" );
		}
		if ( player == HUMAN ) {
			printf ( "White play!(q to quit)\n" );
		} else {
			printf ( "Black play!(q to quit)\n" );
		}
	}
	return 0;
}		/* -----  end of function PrintInfo  ----- */
/**
 * @brief  PlayChess 
 *
 * @param  board
 * @param  player
 * @param  x
 * @param  y
 *
 * @return QUIT or 2 表示退出，-1 表示输入错误。
 */
status PlayChess( char (*board)[N], int player, int *x, int *y ) {
	int option;
	printf ( "\033[34mInput you choice,(x,y).e.g. 4,5\n\033[0m" );
	while ( scanf("%d,%d",x,y) != 2 || *x < 0 || *x >= N || *y < 0 || *y >= N ) {
//		printf ( "Something is wrong,So...\n" );
		option = getchar();
		if ( option == 'q' && getchar() == '\n' ) {
			return QUIT;
		} else {
			if ( option == 'r' && getchar() == '\n' ) {
				if ( board[*x][*y] == '-' ) {
					printf ( "You have already rescinded!\n" );
					return -1;					
				} else {
					board[*x][*y] = '-';
//					Player = ( player + 1 ) % 2;
					printf ( "\033[33mRescinded\n\033[0m" );
					return RES;	
				}
			}
		}
//		if ( *x == 'q' ) return QUIT;
//		printf ( "\033[34mInput you choice,(x,y).e.g. 4,5\n\033[0m" );
//		continue;
	}
	if ( board[*x][*y] != '-' ) {
		printf ( "The position has something, So change you mind!\n" );
		return -1;
	}
	if (Player == PC) {
		board[*x][*y] = 'O';
	} else {
		board[*x][*y] = 'X';
	}
//	Player = ( player + 1 ) % 2;
	return 0;
}		/* -----  end of function PlayChess  ----- */


/**
 * @brief  CheckBoard 
 *
 * @param  board
 * @param  player
 * @param  x
 * @param  y
 *
 * @return WIN or 1: 表示获胜, 0 表示比赛继续
 */
status CheckBoard( char (*board)[N], int player, int *x, int *y ) {
	int dir[8][2] = { {0,1}, {0,-1}, {-1,0}, {1,0}, {-1,1}, {-1,-1}, {1,-1}, {1,1} };
	int xpos = *x, ypos = *y;
	int i = 0;
	int cnt = 1;
	for ( i = 0; i < 8; i++ ) {
		while ( true ) {
			xpos += dir[i][0];
			ypos += dir[i][1];
//			if ( xpos >= 0 && xpos <= N-1 && ypos >=0 && ypos <= N-1 && board[xpos][ypos] == board[x][y] ) {
//				cnt ++;
//			}
			if ( xpos < 0 || xpos >= N || ypos < 0 || ypos >= N ) {
				cnt = 1;
				xpos = *x;
				ypos = *y;
				break;
			} else {
				if ( board[xpos][ypos] == board[*x][*y] && board[*x][*y] != '-') {
					cnt ++;
				} else {
					cnt = 1;
					xpos = *x;
					ypos = *y;
					break;
				}
			}
			if ( cnt == 5 ) {
				return WIN;
			}

		}
	}
//	Player = ( player + 1 ) % 2;
	return 0;
}
