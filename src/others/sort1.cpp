/*
 * =====================================================================================
 *
 *       Filename:  sort1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/20/2015 08:35:53 PM
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
#define	BUFFSIZE 4096			/* Buffer size */
void sort(int *num,int n);
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
	int data[BUFFSIZE];
//	int i = 0,j = 0;
	int cnt = 0;
	while (scanf("%d",&data[cnt]) != EOF) {
		++cnt;
	}
	sort(data,cnt);
	del(data,cnt);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void sort(int *num,int n) 
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
	int max = 0;
	int diff = 0;
	for (i = 0;i < n; ){
		max = num[i];
		printf ( "%d ",max );
		j = 1;
		while ( i != n-1 ){
			diff = max - num[i+j];
			if (diff == j){
				j ++;
				if (j == n) {
					printf ( "%d ",num[i+j-1] );
					break;
				}
			}
			else {
				printf ( "%d ",num[i+j-1] );
				break;
			}
		}
		i = i + j;
	}
	printf ( "\n" );
}

