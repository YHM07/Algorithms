/**
 * @file CircShift.cc
 * @brief 字符串循环左移
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/10/2015
 */
/**
 * @name 字符串循环左移
 * 给定长度为n的字符串，例如n=6 abcdef，左移一位变为bcdefa，左移两位变为
 * cdefab，问左移m位后的结果。
 * @{ */
/**  @} */


void LeftShiftOne(char *pc, int n);
void CircShiftI(char *pc, int n, int m);
void reverse(char *pc, int l, int r);
void CircShiftII(char *pc, int n, int m);
#include <cstdio>
#include <cstring>
#include <cassert>

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
	char pc[] = {"Hello World"};
	printf ( "%s\n", pc );
	char *tmp = pc;
	int m = 4;
	CircShiftI(tmp, strlen(tmp), m);
	printf ( "%s\n", tmp );
	CircShiftII(tmp, strlen(tmp), m);
	printf ( "%s\n", tmp );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


/**
 * @brief  LeftShiftOne 将字符串左移一位
 *
 * @param  pc 字符串数组
 * @param  n
 */
void LeftShiftOne(char *pc, int n)
{
	assert(pc != NULL);
	char ch = pc[0];
	for (int i = 1; i < n; ++i) {
		pc[i - 1] = pc[i];
	}
	pc[n-1] = ch;
}

/**
 * @brief  CircShiftI 循环左移，每次左移一位，一共移动m位
 *
 * @param  pc
 * @param  m
 * @param  n
 */
void CircShiftI(char *pc, int n, int m)
{
	assert(pc != NULL);
	for (int i = 1; i <= m; ++i){
		LeftShiftOne(pc,n);
	}
}

/**
 * @brief  reverse 反转字符串中l~r部分
 *
 * @param  pc
 * @param  l
 * @param  r
 */
void reverse(char *pc, int l, int r)
{
	assert(pc != NULL);
	while (l < r) {
		*(pc + l) ^= *(pc + r);
		*(pc + r) ^= *(pc + l);
		*(pc + l) ^= *(pc + r);
		++ l;
		-- r;
	}
}

/**
 * @brief  CircShiftII 
 * abcdef循环左移 2位，变为cdefab，我们可以理解为对左2位翻转变为ba,
 * 右边4位翻转变为fedc，现在整个变为了bafedc，再翻转一次变为cdefab，
 * 可见，只要实现翻转这一基本操作，就可以实现循环左移。
 * @param  pc
 * @param  n 字符串的数据长度
 * @param  m 循环左移m位
 */
void CircShiftII(char *pc, int n, int m)
{
	assert(pc != NULL);
	m %= n;
	reverse(pc,0,m-1);
	reverse(pc,m,n-1);
	reverse(pc,0,n-1);
}
