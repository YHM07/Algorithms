/*
 * =====================================================================================
 *
 *       Filename:  ps.c
 *
 *    Description: http://blog.csdn.net/newnewman80/article/details/5989449 
 *
 *        Version:  1.0
 *        Created:  04/19/2015 09:05:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  H.M.Yang,yangheming55@126.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct info
{
	int no;
	int code;
	struct info *next;
};
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int n;                                      /* n people */
	int m;                                      /* password */
	int i,j;
	struct info *head,*p,*cur;
	printf ( "input number of people : " );
	scanf ("%d",&n);
	printf ( "initial m(m > 1) : " );
	scanf ("%d",&m);
	
	for (i = 1;i <= n; ++i){
		if (i == 1){
			head = (struct info *)(malloc(sizeof(struct info)));
			if (head == NULL){
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			cur = head;
		}
		else {
			p = (struct info *)(malloc(sizeof(struct info)));
			if (p == NULL){
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			cur->next = p;
			cur = p;
		}
		cur->no = i;
		printf ( "input %d code: ",i );
		scanf("%d",&cur->code);
//		cur->code = m;
		cur->next = NULL;
	}
	cur->next = head;
	cur = head;
	
	for (i = 1;i <= n; ++i){
//		for (j = 1;j < m-1;j++){
//			cur = cur->next;
//		}
		
		for (j=1;j<m;j++,cur=cur->next){
//			printf ( "cur->no = %d\n",cur->no );
		}
		m = cur->code;
		printf ( "%dth no: %d\n",i,cur->no );
		cur->code = cur->next->code;
		cur->no   = cur->next->no;
		p = cur->next;
		cur->next = cur->next->next;
		free(p);
//		p = cur;
//		for (j = 1;j<=n;j++){
//			printf ( "p-no:%d;p-code:%d\n",p->no,p->code );
//			p = p->next;
//		}

//		for (j=1;j<m-1;j++,cur=cur->next){
//			printf ( "cur->no = %d\n",cur->no );
//		}
//		m = cur->next->code;
//		printf ( "m = %d\n",m );
//		printf ( "%dth no: %d\n",i,cur->next->no );
//		p = cur->next;
//		cur->next = cur->next->next;
//		free(p);
//		cur = cur->next;
	}
	printf ( "\n" );	
	return EXIT_SUCCESS;
	
}				/* ----------  end of function main  ---------- */

