/**
 * @file QuickSort.cc
 * @brief quick sort,Divide-and-Conquer Method
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/06/2015
 */

#include <stdio.h>
#include <malloc.h>
#include "lib/comm.h"

#include <stdlib.h>

void QuickSort(int *A,int l,int r);
/**
 * @brief  main 
 *
 * @param  argc
 * @param  argv[]
 *
 * @return  
 */
	int
main ( int argc, char *argv[] )
{
	int num;
	printf ( "num :  " );
	scanf("%d",&num);
	int *pdata;
	pdata = (int *)malloc(sizeof(int)*num);
	if (pdata == NULL) {
		perror("malloc error");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < num; ++i) {
		scanf("%d",&pdata[i]);
	}
	QuickSort(pdata,0,num-1);
	print(pdata,num);
	free(pdata);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief  QuickSort 
 *
 * @param  A 要排序的数组
 * @param  l 数组的第一个值，一般为0
 * @param  r c语言中初始值为数组长度减1
 */
void QuickSort(int *A,int l,int r)
{
	if (l > r)
		return;
	int pivot = A[l];
	int i = l,j = r;
	while (i < j) {
		while (i < j && A[j] >= pivot) {
			j --;
		}
		if (i < j) {
			A[i++] = A[j];
		}
		while (i < j && A[i] <= pivot) {
			i ++;
		}
		if (i < j) {
			A[j--] = A[i];
		}

	}
	A[i] = pivot;
	QuickSort(A,l,i-1);
	QuickSort(A,i+1,r);
}
