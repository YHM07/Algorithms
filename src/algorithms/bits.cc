/**
 * @file bits.cc
 * @brief 位操作
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/04/2015
 */
#include <stdio.h>
#include <iostream>

#include <stdlib.h>

int NumOfBits(int x);
int NumOfBits_1(int x);
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
	printf ( "NumOfBits:%d\n",NumOfBits(27) );
	printf ( "NumOfBits_1:%d\n",NumOfBits_1(27) );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief  NumOfBits 计算二进制中1的个数，<<编程之美>>中有介绍
 *
 * @param  x 要计算的数字，十进制
 *
 * @return 输入数据中二进制数的1 的个数 
 */
int NumOfBits(int x)
{
	int n = 0;                                  /* 二进制中1的个数 */
	for (int i = 0;i < 32; ++i) {
		n += (x >> i) & 0x01;	
//		n += (x & (1 << i)) ? 1 : 0;
	}
	return n;
}

/**
 * @brief  NumOfBits_1 计算二进制中1的个数，<<编程之美>>中有介绍
 *
 * @param  x 要计算的数字，十进制
 *
 * @return 输入数据中二进制数的1 的个数 
 */
int NumOfBits_1(int x)
{
	// 复杂度与二进制数当中1的个数成正比例
	int n = 0;                                  /* 二进制中1的个数 */
	while (x) {
		x &= x - 1;
		n ++;
	}
	return n;
}
