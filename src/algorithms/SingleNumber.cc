/**
 * @file SingleNumber.cc
 * @brief Single Number
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/04/2015
 */

// Single Number I
// Given an array of integers,every element appears twice time  except  
// for one. Find that single one.
// Note:
// You algorithm should have a linear runtime complexity.Could you 
// implement whithout using extra memory?
int SingleNumberI(int *A,int n);

// Single Number II
// Given an array of integers,every element appears three times except
// for one. Fine that single one.
int SingleNumberII(int *A,int n);

#define	BUFFSIZE 5			/*  */
#include <stdio.h>

#include <stdlib.h>

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
	int A[BUFFSIZE];
	while (scanf("%d",&A[cnt]) != EOF) {
		cnt ++;
	}
//	printf ( "SingleNumberI:%d\n",SingleNumberI(A,cnt) );
	printf ( "SingleNumberII:%d\n",SingleNumberII(A,cnt) );
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

/**
 * @brief  SingleNumberI 数组A中除去一个数字x，其他数字均出现三次，而x出现一次，找到x。
 *
 * @param  A 
 * @param  n 数组A的大小
 *
 * @return 出现一次的数据x
 */
int SingleNumberII(int *A,int n)
{
	int ones = 0;
	int twos = 0;
	int threes = 0;
	
	for (int i = 0; i < n; ++i) {
		int t = A[i];
		ones ^= t;
		twos |= (~ones) & t;
		threes = ones & twos;
		ones &= ~threes;
		twos &= ~threes;
	}
	return ones;
}

// 以下算法参考:http://blog.csdn.net/morewindows/article/details/12684497
/**
 * @brief  SingleNumberI 数组A中除去一个数字x，其他数字均出现三次，而x出现一次，找到x。
 *
 * @param  A 
 * @param  n 数组A的大小
 *
 * @return 出现一次的数据x
 */
int SingleNumberII_1(int *A,int n)
{
	
}
