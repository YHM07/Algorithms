/**
 * @file KMP.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/10/2015
 */
#include <cstdio>
#include <cassert>
#include <cstring>

#include <stdlib.h>
//int strlen(const char *str);
int ViolentMatch(const char *s, const char *p, int pos);
void GetNextVal(const char *p, int next[]);
int kmp(const char *s, const char *p, int pos);

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
	const char *pch = "BBC ASBCAB ABCDABCDABDE!";
   	const char *p = "ABCDABD";
	int len = strlen(pch);
	printf ( "ch: %s %d\n", pch, len );
	int pos;
	if ( (pos = ViolentMatch(pch,p,3)) == -1 ) {
		fprintf ( stderr, "match failure\n" );
	} else {
		printf ( "%d\n", pos );
	}
	if ((pos = kmp(pch,p,0)) == -1) {
		fprintf ( stderr, "match failure\n" );
	} else {
		printf ( "%d\n", pos );
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


/**
 * @brief	ViolentMatch 字符串暴力匹配
 *
 * @param	s 主字符串,从字符串的pos位置开始匹配
 * @param	p 模式字符串
 *
 * @return	如果匹配成功，返回第一次字符串匹配的位置，失败返回-1
 */
int ViolentMatch(const char *s, const char *p, int pos) 
{
	assert(s != NULL);
	assert(p != NULL);
	int sl = strlen(s);
	int pl = strlen(p);

	int i = pos, j = 0;
	while (i < sl && j < pl) {
		if (s[i] == p[j]) {
			++i;
			++j;
		} else {
			i = i -j + 1;
			j = 0;
		}
	}
	if (j >= pl) 
		return i - j;
	else
		return -1;
}

//int strlen(const char *str)
//{
//	assert(str != NULL);
//	if (*str == '\0') {
//		return 0;
//	} else {
//		return strlen(str+1) + 1;
//	}
//
//}
//

/**
 * @brief	kmp 
 *
 * @param	s
 * @param	p
 * @param	pos
 *
 * @return	
 */
int kmp(const char *s, const char *p, int pos)
{
	assert(s != NULL);
	assert(p != NULL);

	int sl = strlen(s);
	int pl = strlen(p);
	int i  = pos, j = 0;
	int *next = (int *)malloc(sizeof(int) * pl);
	if (next == NULL) {
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	GetNextVal(p,next);
	while (i < sl && j < pl) {
		/**
		 * @name 
		 * j == -1 表示数据从头重新开始检索
		 * @{ */
		/**  @} */

		if (j == -1 || s[i] == p[j]) {
			i ++;
			j ++;
		} else {
			j = next[j];
		}
	}
	free(next);
	if (j >= pl) 
		return i - j;
	else 
		return -1; 

}

/**
 * @brief	GetNextVal 
 *
 * @param	p
 * @param	next[]
 */
void GetNextVal(const char *p, int next[])
{
	int pl = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;

	while (j < pl - 1) {
		if (k == -1 || p[j] == p[k]) {
			j ++;
			k ++;
			if (p[j] == p[k]) {
				next[j] = next[k];
			} else {
				next[j] = k;
			}	

		} else {
			k = next[k];
		}
	}

}
