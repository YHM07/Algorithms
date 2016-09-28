/**
 * @file words.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 09/01/2016
 */
#include<stdio.h>
#include<string.h>


//#include <stdlib.h>

///**
// * @brief  main 
// *
// * @param  argc
// * @param  argv[]
// *
// * @return  
// */
//int main ( int argc, char *argv[] ) { 
//    char s1[120];
//	char s2[120];
//	int i,length;
//	int count=0;
//	gets(s1);
//	gets(s2);
////处理第一个字符串
//	length=strlen(s1);
//	if(length!=0)
//	{
//		int n=0;
//		int flag=0;
//		if(length%8!=0)
//		{
//			n=(8-length%8);
//			flag=1;
//		}
//		for(i=0;i<length;i++)
//		{
//			count++;
//			printf("%c",s1[i]);
//			if(count==8)
//			{
//				count=0;
//				printf("\n");
//			}
//		}
//
//		if(flag)
//		{
//			for(i=0;i<n;i++)
//			printf("0");
//			
//		}
//		printf("\n");
//	}
////处理第二个字符串
//	count=0;
//	length=strlen(s2);
//	if(length!=0)
//	{
//		int n=0;
//		int flag=0;
//		if(length%8!=0)
//		{
//			n=(8-length%8);
//			flag=1;
//		}
//		for(i=0;i<length;i++)
//		{
//			count++;
//			printf("%c",s2[i]);
//			if(count==8)
//			{
//				count=0;
//				printf("\n");
//			}
//		}
//		if(flag)
//		{
//			for(i=0;i<n;i++)
//			printf("0");
//		}
//		printf("\n");
//	}
//	return EXIT_SUCCESS;
//}				/* ----------  end of function main  ---------- */
//


#include <stdlib.h>

/**
 * @brief  main 
 *
 * @param  argc
 * @param  argv[]
 *
 * @return  
 */
int main ( int argc, char *argv[] ) { 
	char s[2][120] = { {'\0'} };
	int i,j,line = 0,n = 0;
	int flag = 0;
	char out[30][8];
	for ( i = 0; i < 2; i++ ) {
		scanf( "%s", s[i] );
	}
//	for ( i = 0; i < 2; i++ ) {
//		printf( "%s", s[i] );
//		printf ( "\n" );
//	}
	for ( i = 0; i < 2; i++ ) {
		j = 0;
		n = 0;
		flag = 0;
		while ( s[i][j] != '\0' ) {
			out[line][n++] = s[i][j++];
			if ( n == 8 ) {
				line ++;
				n = 0;
			}
//			j++;
		}
		flag = strlen(s[i]) % 8;
		for ( j = flag ; j < 8; j++ )  {
			out[line][n++] = '0';
		}
		if ( flag ) {
			line++;
		}

	}
	for ( i = 0; i < line; i ++ ) {
		for ( j = 0; j < 8; j ++ ) {
			printf ( "%c",out[i][j] );
		}
		printf ( "\n" );
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
