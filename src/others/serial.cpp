/**
 * @file serial.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/29/2016
 */
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
int main ( int argc, char *argv[] ) { 
	int i,j;
	int n, sum = 0;
	scanf( "%d",&n );
	for ( i = 1; i <= n; i++) {
		sum += i;
		if ( i % 2 != 0 ) {
			for ( j = sum - i + 1; j < sum; j++ ) {
				printf ( "%d * ", j );
			}
			printf ( "%d\n", j );
		} else {
			for ( j = sum; j > sum - i + 1; j-- ) {
				printf ( "%d * ", j );
			}
			printf ( "%d\n", j );
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
