/**
 * @file test.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 09/22/2016
 */
#include <stdio.h>

#include <stdlib.h>
void sort(int *seq, int *wi, int n);
/**
 * @brief  main 
 *
 * @param  argc
 * @param  argv[]
 *
 * @return  
 */
int main ( int argc, char *argv[] ) { 
	int n,m;
	int vi[100],wi[100];
	int i,j;
	int cnt = 0, sum = 0, max = cnt;
	scanf("%d",&n);
	scanf("%d",&m);
	for ( i = 0; i < n; i ++ ) {
		scanf( "%d %d", &vi[i], &wi[i] );
	}
//	for ( i = 0; i < n; i++ ) {
//		printf ( "%d %d", vi[i],wi[i] );
//	}
//	sort(vi,wi,n);
	for ( i = 0; i < n; i++ ) {
		sum = m;
		cnt = 0;
		for ( j = i; j < n; j++ ) {
			if ( sum >= wi[j] ) { 
				cnt += vi[j];
				sum = sum - wi[j];
			}
		}
		if ( max < cnt ) {
			max = cnt;
		}
	}
	printf ( "%d\n", max );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void sort(int *seq, int *wi, int n)
{
        int i = 0,j = 0;
        int tmp1, tmp2;
        int exchange = 0;
        for (i = 0;i < n; ++i){
                for (j = n-1;j > i;j--){
                        if (seq[j] > seq[j-1]){
                                tmp1 = seq[j]; tmp2 = wi[j];
                                seq[j] = seq[j-1]; wi[j] = wi[j-1];
                                seq[j-1] = tmp1; wi[j-1] = tmp2;
                                exchange = 1;
                        }
                }
                if (!exchange){
                                return;
                }
        }

}
