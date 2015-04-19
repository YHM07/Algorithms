/*
 * =====================================================================================
 *
 *       Filename:  josephus.c
 *
 *    Description:  递归约瑟夫环问题 
 *
 *        Version:  1.0
 *        Created:  04/19/2015 07:52:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  H.M.Yang,yangheming55@126.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#include <stdlib.h>
int josephus(int n,int m,int i);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int n;                                      /* n个人 */
	int m;                                      /* 报数m */
	
	int i;
	printf ( "输入n个人:\n" );
	scanf("%d",&n);
	printf ( "报数m\n" );
	scanf("%d",&m);
	for (i = 1;i <= n; ++i){
		printf ( "%2d: %d\n",i,josephus(n,m,i) );
	}
	return EXIT_SUCCESS;

}				/* ----------  end of function main  ---------- */

int josephus(int n,int m,int i)
{
	if (i == 1){
		return (n+m-1)%n;
	}
	else {
		return (josephus(n-1,m,i-1)+m)%n;
	}
}
