/*
 * =====================================================================================
 *
 *       Filename:  josephus.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2015 05:15:48 PM
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

struct node
{
	int no;                                     /* 编号 */
	int flag;                                   /* true or false */
	struct node *next;                          /* next node */
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
	int n;                                      /* n 个人 */
	int m;                                      /* 报数 */
	int i;
	struct node *first;
	struct node *ptr;
	struct node *cur;
	printf ( "input n: " );
	scanf("%d",&n);
//	printf ( "\n" );
	printf ( "input m: " );
	scanf("%d",&m);
	
	first = (struct node *)malloc(sizeof(struct node));
	if (first == NULL){
		printf ( "malloc error\n" );
		exit(EXIT_FAILURE);
	}
	first->no = 0;
	first->flag = 0;
	first->next = NULL;
	cur = first;
	for (i = 1;i < n; ++i) {
		ptr = (struct node *)malloc(sizeof(struct node));
		if (ptr == NULL){
//			printf ( "malloc error\n" );
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		cur->next = ptr;
		ptr->no = i;
		ptr->flag = 0;
		ptr->next = NULL;
		cur = ptr;
	}
	cur->next = first;
	cur = first;

	for (i = 0;i < n;i ++,cur = cur->next){
		printf ( "no: %d\n",cur->no );
	}
	
	int pos = 1;
	for (i = 0;i < n; ){
//		cur->no = pos;
//		cur = cur->next;
		if (pos == m){
			printf ( "cur : %d\n",cur->no );
			cur->flag = 1;
			pos = 0;
			i ++;
		}
//		while (cur->next->flag == 1){
//			cur = cur->next;
//			break;
//		}
		do
		{
			cur = cur->next;
			if (i == n){
				break;
			}	
		}while (cur->flag == 1);
		pos ++;
	}
	
	return EXIT_SUCCESS;
}
				/* ----------  end of function main  ---------- */
