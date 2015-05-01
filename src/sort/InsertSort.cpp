/**
 * @file InsertSort.c
 * @brief Insert sort
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/01/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>

#define	BUFFSIZE	4096		/*  */
void InsertSort(int A[],int n);

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
	int data[BUFFSIZE];
	int cnt = 0;
	int i;
//	FILE *pfile = fopen("file.txt","r");
//	char *pdata;
//	fseek(pfile,0,SEEK_END);
//	cnt = ftell(pfile);
//	pdata = (char *)malloc(sizeof(char)*cnt);
//	rewind(pfile);
//	fread(pdata,1,cnt,pfile);
//	pdata[cnt] = '\0';
//	MessageBox(pdata);
//	for (i = 0;i < cnt; ++i){
//		printf ( "pdata[%d] = %d\n",i,pdata[i] );;
//	}
//	fclose(pfile);
	int fd;
	FILE *fp;
	off_t currpos;
	if ((fd = open("file.txt",O_RDONLY)) == -1){
		perror("open error");
	}
	currpos = lseek(fd,0,SEEK_END);
	cnt = currpos;
	printf ( "cnt = %d\n",cnt );
	cnt = 0;
//	while(scanf("%d",&data[cnt]) != EOF){
//		cnt ++;
//	}
	close(fd);
	if ((fp = fopen("file.txt","r")) == NULL){
		perror("fopen error");
	}
	while(fscanf(fp,"%d",&data[cnt]) != EOF){
		cnt ++;
	}
	for (i = 0;i < cnt; ++i){
		printf ( "data[%d] = %d\n",i,data[i] );
	}
	fclose(fp);
	InsertSort(data,cnt);
	for (i = 0;i < cnt; ++i){
		printf ( "data[%d] = %d\n",i,data[i] );
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief	InsertSort 
 *
 * @param	A[] 
 * @param	n the number of array A
 */
void InsertSort(int A[],int n)
{
	int i = 0;
	int j = 0;
	int sentry;
	for (i = 1; i < n; ++i){
		if (A[i-1] > A[i]){
			sentry = A[i];
			j = i - 1;
//			A[i] = A[i-1];
			while (A[j] > sentry && j >= 0){
				A[j+1] = A[j];
				j --;
			}
			A[j+1] = sentry;
		}
	}
	
}
