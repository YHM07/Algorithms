/**
 * @file quicksort.cc
 * @brief quick sort
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/09/2016
 */

#include <stdio.h>

#include <stdlib.h>

int partition ( int *arv, int l, int r );
void quicksort(int *array, int l, int r );
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
	int array[1024];
	int cnt = 0;
	int i = 0;
	while ( scanf("%d", &array[cnt]) != EOF) {
		cnt ++;
	}
	quicksort(array, 0, cnt-1);
	for (i = 0; i < cnt; i++) {
		printf("%d\t", array[i]);
	}
	printf ( "\n" );
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief  partition 
 *
 * @param  arv
 * @param  l
 * @param  r
 *
 * @return  
 */

	int
partition ( int *arv, int l, int r )
{
	int pivot = arv[l];
	while ( l < r && arv[r] >= pivot ) {
		r --;
	}
	if ( l < r ) {
		arv[l++] = arv[r];
	}
	while (l < r && arv[l] <= pivot) {
		l ++;
	}
	if ( l < r ) {
		arv[r--] = arv[l];
	}
	arv[l] = pivot;
	return l;
}		/* -----  end of function partition  ----- */

void quicksort(int *array, int l, int r) {
	int q;
	if ( l < r ) {
		q = partition(array, l, r);
		quicksort(array,l,q-1);
		quicksort(array,q+1,r);
	}
}
