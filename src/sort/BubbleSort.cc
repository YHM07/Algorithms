/**
 * @file BubbleSort.c
 * @brief bubble sort
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/02/2015
 */
#include <stdio.h>

#include <stdlib.h>
#include "lib/comm.h"
void BubbleSort(int A[],int n);
//void swap(int *p,int *q);
#define	BUFFSIZE 4096			/*  */

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
	int cnt = 0;
	int data[BUFFSIZE];
	FILE *fp;
//	int i;
	fp = fopen("file.txt","r");
//	while (fscanf(fp,"%d",&data[cnt]) != EOF){
//		cnt ++;
//	}
	while (scanf("%d",&data[cnt]) != EOF){
		cnt ++;
	}
	fclose(fp);
	BubbleSort(data,cnt);
//	for (i = 0;i < cnt; ++i){
//		printf ( "data[%d] = %d\n",i,data[i] );
//	}
	print(data,cnt);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief	BubbleSort 
 *
 * @param	A[]
 * @param	n
 */
void BubbleSort(int A[],int n)
{
	int i,j;
	int exchange = 0;
	static int loop = 1;
	for (i = 0;i < n; ++i){
		exchange = 0;
		printf ( "loop = %d\n",loop++ );
		for (j = 0;j < n-i-1; ++j ){
			if (A[j] > A[j+1]){
				swap(&A[j],&A[j+1]);
				exchange = 1;
			}
		}
		if ( exchange == 0 ){
			return;
		}
	}
}

/**
 * @brief	swap 
 *
 * @param	p
 * @param	q
 */
//void swap(int *p,int *q)
//{
//	int tmp;
//	tmp = *p;
//	*p  = *q;
//	*q  = tmp;
//}
