/*
 * =====================================================================================
 *
 *       Filename:  bubblesort.c
 *
 *    Description:  improve bubble sort
 *
 *        Version:  1.0
 *        Created:  2015年04月20日 23时03分41秒
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

#define	BUFFSIZE 4096			/* Buffer size */
void sort(int *seq,int n);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int data[BUFFSIZE];
	int i;
	int cnt = 0;
	printf ( "input data(<= 4096):\n" );
	while (scanf("%d",&data[cnt]) != EOF){
		cnt ++;
	}
	sort(data,cnt);
	for (i = 0;i < cnt;++i){
		printf ( "data[%d] = %d\n",i,data[i] );
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void sort(int *seq,int n)
{
	int i = 0,j = 0;
	int tmp;
	int exchange = 0;
	for (i = 0;i < n; ++i){
		printf ( "%dth loop\n",i+1 );
		for (j = n-1;j > i;j--){
			if (seq[j] < seq[j-1]){
				tmp = seq[j];
				seq[j] = seq[j-1];
				seq[j-1] = tmp;
				exchange = 1;
			}
		}
		if (!exchange){
			return;
		}
	}

}
	
