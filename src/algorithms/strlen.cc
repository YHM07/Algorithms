/**
 * @file strlen.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/10/2015
 */
#include <cstdio>
#include <cassert>
//#include <cstring>


int strlen(const char *str);
#include <stdlib.h>

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
	const char *pch = "HelloWorld!";
	int len = strlen(pch);
	printf ( "ch: %s %d\n", pch, len );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief  strlen 求解字符串的长度，不使用中间变量
 *
 * @param  str
 *
 * @return  
 */
int strlen(const char *str)
{
	assert(str != NULL);
	if (*str == '\0') {
		return 0;
	} else {
		return strlen(str+1) + 1;
	}

}
