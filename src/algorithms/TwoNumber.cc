/**
 * @file TwoNumber.cc
 * @brief Two Number
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/06/2015
 */

// Single Number I
// Given an array of integers,every element appears twice time  except  
// for one. Find that single one.
// Note:
// You algorithm should have a linear runtime complexity.Could you 
// implement whithout using extra memory?
int SingleNumberI(int *A,int n);

// Single Number II
// Given an array of integers,every element appears two times except
// for two. Fine that single two.
void SingleNumberII(int *A,int n,int &px,int &py);

#define	BUFFSIZE 5			/*  */
#include <stdio.h>

#include <stdlib.h>
#include "lib/comm.h"

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
//	int A[BUFFSIZE] = {1,2,2,1,3};
	int cnt = 0;
	int px,py;
	int A[BUFFSIZE];
	while (scanf("%d",&A[cnt]) != EOF) {
		cnt ++;
	}
//	printf ( "SingleNumberI:%d\n",SingleNumberI(A,cnt) );
//	printf ( "SingleNumberII:%d\n",SingleNumberII(A,cnt,px,py) );
	SingleNumberII(A,cnt,px,py);
	printf ( "SingleNumberII:%d\t%d\n",px,py );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

// 以下算法参考:http://www.cnblogs.com/wei-li/p/SingleNumberII.html
/**
 * @brief  SingleNumberI 数组A中除去一个数字x，其他数字均出现两次，而x出现一次，找到x。
 *
 * @param  A 
 * @param  n 数组A的大小
 *
 * @return 出现一次的数据x
 */
int SingleNumberI(int *A,int n)
{
	int x = 0;
	for  (int i = 0; i < n; ++i) {
		x ^= A[i];
	}
	return x;

}

// 以下算法参考:http://blog.csdn.net/morewindows/article/details/12684497

/**
 * @brief	SingleNumberII 数组A中除去一个数字x,y，其他数字均出现两次，而x,y出现一次，找到x,y。
 *
 * @param	A
 * @param	n
 * @param	px
 * @param	py
 */
void SingleNumberII(int *A,int n,int &px,int &py)
{
	int x = SingleNumberI(A,n);
	int pos = 0;;
	for (int i = 0; i < 32; ++i) {
		if ((x >> i) & 0x01) {
			pos = i;
			break;
		}
	}
	// 
	for (int j = 0; j < n; ++j) {
		if (A[j] & (1 << pos)) {
			px ^= A[j];
		} else {
			py ^= A[j];
		}
	}
}
