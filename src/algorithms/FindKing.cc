/**
 * @file FindKing.cc
 * @brief 编程之美 寻找发帖“水王”
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/07/2015
 */

#include <stdio.h>

#include <stdlib.h>
int FindKing(int *ID,int n);

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
	int cnt = 0;
	int ID[100];
	while (scanf("%d",&ID[cnt++]) != EOF) {

	}
	printf ( "FindKing: %d\n",FindKing(ID,cnt) );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

// 以下实现来自编程之美
/**
 * @brief  FindKing 寻找发帖"水王"
 *
 * @param  ID ID
 * @param  n
 *
 * @return  
 */
int FindKing(int *ID,int n)
{
	int candidate = 0;
	int ntimes = 0;
	for (int i = 0; i < n; ++i) {
		if (ntimes == 0) {
			candidate = ID[i];
			ntimes = 1;
		} else {
			if (candidate == ID[i] ) {
				ntimes ++;
			} else {
				ntimes --;
			}
		}
	}
	return candidate;
}
