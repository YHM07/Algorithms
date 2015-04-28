/*
 * =====================================================================================
 *
 *       Filename:  bcd.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年04月18日 22时33分56秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  H.M.Yang, hmyang07@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define	MAX_BUFFER 4096			/*  */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{	
	char ptr[MAX_BUFFER] = {'\0'};
//	int  num;
	int  n = 0;
//	int  dec[MAX_BUFFER];
	int  i;
	n =	scanf("%s",ptr);
	printf("n = %d\n",n);
//	num = atoi(ptr);
//	printf("num = %d\n",num);
//	while ( *(ptr+n) != '\0' ){
//		++ n;	
//	}
	n = strlen(ptr);
//	printf("n = %d\n",n);
		
	for ( i = 0;i < n; i++ ) {
		if (i == 0 && n % 2 == 1){
			printf ( "%d",*ptr - '0' );
		}
		else {
			printf ( "%d",(*(ptr+i) - '0')*16 + *(ptr+i+1) - '0' );
			i++;
		}
	}
	printf ( "\n" );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
