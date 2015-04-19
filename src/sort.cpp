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
void descend_sort(int *num,int n);
void del(int *num,int n);

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
//	while ((num[cnt] = getchar()) != '\n') {
//		cnt ++;
//	}
	while (scanf("%d",&num[cnt]) != EOF) {
		++ cnt;
	}
	descend_sort(num,cnt);
	for (i = 0;i < cnt; ++i) {
		printf ( "num[%d] = %d\n",i,num[i] );
	}
	del(num,cnt);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void descend_sort(int *num,int n) 
{
	int i = 0;
	int j = 0;
	int tmp;
	for (i = 0;i < n; ++i) {
		for (j = i + 1;j < n; ++j) {
			if ( num[i] < num[j] ) {
				tmp = num[i];
				num[i] = num[j];
				num[j] = tmp;
			}
		}
	}
}

void del(int *num,int n)
{
	int i = 0,j = 0;
	int max,min;
	int diff = 0;
	int first;

	for (i = 0;i < n-1; ) {
		max = num[i];
		printf( "%d ",max );
		first = num[i];
		for (j = i+1;j < n-1; ++j) {
			min = num[j];
			diff = first - min;
			if ( diff == 1 ) {
				first = min;
//				if ( i == n-1 ){
//					printf ( "%d %d",max,min);					
//					i = i + 1;
//				}
			}
			else {
				if (j - i == 1){
					printf ( "%d ",min);
					j = j + 1;
				}
				else {
					printf ( "%d ",num[j-1]);
//					j = j;
				}
//				printf ( " " );
				break;
			}
		}
		i = j;
	}
	if (i == n - 1)
		printf ( "%d",num[n-1]);
	printf ( "\n" );
}
