/**
 * @file SelectSort.c
 * @brief 二元选择排序
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/01/2015
 */
#include <stdio.h>

#include <stdlib.h>
void SelectSort(int A[],int n);
void swap(int *p,int *q);

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
	int i;
	int data[BUFFSIZE];
	int cnt = 0;
	FILE *fp;
	if ((fp = fopen("file.txt","r")) == NULL){
			perror("fopen error");
	}
//	while (fscanf(fp,"%d",&data[cnt]) != EOF){
//		cnt ++;
//	}
	while (scanf("%d",&data[cnt]) != EOF){
		cnt ++;
	}
	fclose(fp);
	SelectSort(data,cnt);
	for (i = 0;i < cnt; ++i){
		printf ( "data[%d] = %d\n",i,data[i] );
	}


	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
/**
 * @brief	SelectSort 
 *
 * @param	A[]
 * @param	n
 */
void SelectSort(int A[],int n)
{
	int i,j;
	int min,max;
	for (i = 0;i < n/2; ++i){
		min = i;max = i;
		for (j = i+1;j < n-i; ++j){
			if (A[j] < A[min]){
				min = j;
				continue;
			}
			if (A[j] > A[max]){
				max = j;
			}
		}
		/* 如果max与i值相等，那么min与i交换后，max改变，因此要保留max */
		if (min != i ){
			swap(&A[i],&A[min]);
			if (max == i){
				max = min;
			}
		}
		if (max != n-i-1 ){
			swap(&A[n-i-1],&A[max]);
		}
		
	}
}
/**
 * @brief	swap 
 *
 * @param	p
 * @param	q
 */
void swap(int *p,int *q)
{
	int tmp;
	tmp = *p;
	*p  = *q;
	*q  = tmp;
}

