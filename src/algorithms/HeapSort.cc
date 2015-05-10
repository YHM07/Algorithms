/**
 * @file HeapSort.cc
 * @brief 堆排序，进行降序排序，建立小顶堆
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/08/2015
 */

#include <stdio.h>
#include <istream>
#include "lib/comm.h"

#include <stdlib.h>
void HeapAdjust(int *heap,int i);
void HeapSort(int *heap,int n);
void HeapFixDown(int *heap,int i,int n);

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
	int cnt = 0;
	printf ( "input the number of heap:" );
	scanf("%d",&cnt);
	int *heap;
	heap = (int *)malloc(sizeof(int)*cnt);
	printf ( "input heap\n" );
	for (int i = 0; i < cnt; ++i) {
		scanf("%d",&heap[i]);
		HeapAdjust(heap,i);
	}
	print(heap,cnt);
	HeapSort(heap,cnt);
	print(heap,cnt); 
	free(heap);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/**
 * @brief	HeapAdjust 
 *
 * @param	heap 建立小顶堆
 * @param	i 从i开始建立小顶堆,如果i=0,那么father=0;此时会进入死循环
 */
void HeapAdjust(int *heap,int i)
{
	// 新加入i节点，其父节点为(i-1)/2
	int father = (i - 1) / 2;
	int tmp = heap[i];
	while (father >= 0 && i != 0) {
		if (heap[father] <= tmp ) {
			break;
		}
		
//		swap(heap[father],tmp);
		heap[i] = heap[father];             /* 将较大的子节点往下移动，替换它的子节点 */
		i = father;                                  /* 节点上移 */
		father = (i - 1) / 2;
	}
	heap[i] = tmp;
}

void HeapFixDown(int *heap,int i,int n)
{
	int child = 2 * i + 1;
	int tmp   = heap[i];
	
	while (child < n) {
		if (child + 1 < n && 
				heap[child] > heap[child + 1]) {
			child = child + 1;
		}
		if (heap[child] > tmp)
			break;
		heap[i] = heap[child];
		i = child;
		child = 2 * i + 1;
//		swap(heap[i],heap[child]);
	}
	heap[i] = tmp;
}

/**
 * @brief	HeapSort 
 *
 * @param	heap
 * @param	n
 */
void HeapSort(int *heap,int n)
{
	for (int i = n - 1; i > 0; --i) {
		swap(heap[0],heap[i]);
//		HeapAdjust(heap,i-1);
		HeapFixDown(heap,0,i);
	}
}

