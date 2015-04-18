/*
 * =====================================================================================
 *
 *       Filename:  sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年04月18日 23时44分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  H.M.Yang, hmyang07@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#include <stdlib.h>
#define	BUFFSIZE 4096			/*  */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int num[BUFFSIZE];
	int cnt = 0;
	int i = 0;
	while ((num[cnt] = getchar()) != '\n') {
		cnt ++;
	}
	
	for (i = 0;i < cnt; ++i) {
		printf ( "%d\n" ,num[i]);
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
