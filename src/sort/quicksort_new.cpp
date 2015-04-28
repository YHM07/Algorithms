/*
 * =====================================================================================
 *
 *       Filename:  quicksort_new.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年04月21日 23时13分30秒
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
int partition(int *R,int low,int high);
void quicksort(int *R,int low,int high);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int R[BUFFSIZE];
	int cnt = 0;
	int i = 0;
	int low,high;
	while (scanf("%d",&R[cnt]) != EOF ){
		cnt ++;
	}
	low = 0;
	high = cnt;
	quicksort(R,low,high-1);
	for (i = 0;i < cnt; ++i){
		printf ( "R[%d] = %d\n",i,R[i] );
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

int partition(int *R,int low,int high)
{
	int pivot = R[low];
	while (low < high) {
		while (low < high && R[high] >= pivot){
			high --;
		}
		if (low < high){
			R[low++] = R[high];
		}
		while (low < high && R[low] <= pivot){
			low ++;
		}
		if (low < high) {
			R[high--] = R[low];
		}
	}
	R[low] = pivot;
	return low;
}
void quicksort(int *R,int low,int high)
{
	int q;
	if (low < high){
		q = partition(R,low,high);
		quicksort(R,low,q-1);
		quicksort(R,q+1,high);
	}
}
