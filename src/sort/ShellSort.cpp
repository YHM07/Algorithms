/**
 * @file ShellSort.c
 * @brief shell sort
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/01/2015
 */
#include <stdio.h>

#include <stdlib.h>
void InsertSort(int A[],int n,int dt);
void ShellSort(int A[],int n);
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
	FILE *fp;
	int data[BUFFSIZE];
	int cnt = 0;;
	int i;
	if ((fp = fopen("file.txt","r")) == NULL){
		perror("fopen error");
		exit(EXIT_FAILURE);
	}
	while (fscanf(fp,"%d",&data[cnt]) != EOF){
		cnt ++;
	}
	fclose(fp);
//	for(i = 0;i < cnt; ++i){
//		printf ( "data[%d] = %d\n",i,data[i] );
//	}
	ShellSort(data,cnt);
	for(i = 0;i < cnt; ++i){
		printf ( "data[%d] = %d\n",i,data[i] );
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


/**
 * @brief	ShellSort shell sort
 *
 * @param	A[] 
 * @param	n
 */
void ShellSort(int A[],int n)
{
//	int dt;
	int i;
	for (i = n/2;i > 0; i /= 2){
		InsertSort(A,n,i);
	}
}

/**
 * @brief	InsertSort insert sort
 *
 * @param	A[]
 * @param	n
 * @param	dt
 */
void InsertSort(int A[],int n,int dt)
{
	int i = 0;
	int j = 0;
	int sentry = 0;
	for(i = dt;i < n; i ++){
		if (A[i] < A[i-dt]){
			sentry = A[i];
			j = i - dt;
			while (sentry < A[j] && j >= 0){
				A[j+dt] = A[j];
				j -= dt;
			}
			A[j+dt] = sentry; 
		}
	}
}
