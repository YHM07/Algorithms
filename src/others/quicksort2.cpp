/*
 * =====================================================================================
 *
 *       Filename:  quicksort.c
 *
 *    Description:  quick sort
 *
 *        Version:  1.0
 *        Created:  04/19/2015 02:20:47 PM
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

void QuickSort(int *A,int p,int r);
int partition(int *A,int p,int r);
void swap(int *p,int *q);
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
//	int num[BUFFSIZE];
	int num[8] = {3,5,7,2,8,4,1,6};
	int i;
	int n = 8;
//	while (scanf("%d",&num[n]) != EOF){
//		n ++;
//	}
	
	QuickSort(num,0,n);
	for (i = 0;i < n;i ++){
		printf ( "num[%d] = %d\n",i,num[i] );
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void QuickSort(int *A,int p,int r) 
{
	int q;
	if (p < r){
		q = partition(A,p,r);
		QuickSort(A,p,q);
		QuickSort(A,q+1,r);
	}
	return;
}

int partition(int *A,int p,int r) 
{
	int x = A[r-1];
	int i = p-1;
	int j = 0;
	static int sn = 1;
	printf ( "partition(A,%d,%d)\n",p,r );
	printf ( "sn = %d\n",sn );
	for (j = 0;j < 8;j ++){
		printf ( "A[%d] = %d\t",j,A[j] );
	}
	printf ( "\n" );

	for (j = p;j < r-1;j ++) {
		if (A[j] <= x) {
			i = i+1;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[i+1],&A[r-1]);

	for (j = 0;j < 8;j ++){
		printf ( "A[%d] = %d\t",j,A[j] );
	}
	printf ( "\n" );
	sn ++;
	printf ( "sn = %d return i = %d\n",sn,i+1 );
	return i+1;
}

void swap(int *p,int *q)
{
	int tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}
