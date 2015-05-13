/**
 * @file RadixSort.cc
 * @brief radix sort 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 05/12/2015
 */
#include<iostream>
#include<malloc.h>
#include <stdlib.h>
using namespace std;


void  PrintArr(int ar[],int n)
{
	for(int i = 0; i < n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;
}

int MapToIndex(int x,int max)  
{  
	return (10 * x) / max;  
} 

void insertion_sort(int arr[],int begin,int end)
{
	for(int i = begin+1; i <= end; ++i)
	{
		int v = arr[i];
		int j = i;
		while(j-1 >= begin && v<arr[j-1])
		{
			arr[j] = arr[j-1];  
			j --;
		}
		arr[j] = v;
	}
} 

void bucket_sort(int ar[], int begin, int end)  
{  

	const int radix = 11 ;  //注意：为什么是11？
	int count[radix], i, j;    
	int size = end-begin+1;

	//计数值置空
	for(i = 0; i < radix; ++i)  
	{
		count[i] = 0;    //置空
	}

	//end-begin+1 = 9 - 0 + 1 = 10
	int *Temp = (int *) malloc((size) * sizeof(int));     //分配临时空间

	//取得当前待排序数据中的最大数据
	int max = 0;  
	for(i = begin; i < size; ++i)  
	{  
		if(ar[i] > max)  
			max = ar[i];  
	}  

	//统计各桶需要装的元素的个数  
	for(i = begin; i < size; ++i)   
	{
		count[MapToIndex(ar[i], max)]++;   
	}

	//输出计数结果：
	PrintArr(count, radix);

	//求出桶的边界索引，count[i]为第i个桶的右边界索引+1   
	for(i = 1; i < radix; ++i)   
	{
		count[i] = count[i] + count[i-1];  
	}

	//输出桶边界索引        
	PrintArr(count, radix);

	//从右向左扫描，保证排序稳定性   
	for(i = end; i >= begin; --i)             
	{    
		j = MapToIndex(ar[i], max);        
		Temp[count[j]-1] = ar[i];  //放入对应的空间中，count[j]-1是第j个桶的右边界索引   
		--count[j];       //准备放置下一个元素的位置索引   
	}     

	for(int i = 0; i < size; ++i)
	{
		cout<<Temp[i]<<"  ";
	}
	cout<<endl;

	PrintArr(count, radix);

	//从各个桶中收集数据   
	for(i = begin, j = 0; i < size; i++, j++)  
	{
		ar[i] = Temp[j];        
	}

	PrintArr(ar, end+1);

	//释放空间  
	free(Temp);                          

	for(i = 0; i < size; i++)  
	{   
		int index1 = begin + count[i];             //得到第i个桶的左边界   
		int index2 = begin + count[i+1] - 1;       //得到第i个桶的右边界   
		if(index1 < index2)  
			insertion_sort(ar, index1, index2);          
	}  
	PrintArr(ar, end+1);
}  

int main()
{
	int  ar[] = {12, 14, 54, 5, 6, 3, 9, 8, 47, 89};
	int len = sizeof(ar)/sizeof(int);
	bucket_sort(ar, 0, len-1);
	PrintArr(ar, len);
	return EXIT_SUCCESS;
}
/*
   4 3 0 0 0 1 1 0 0 0 1
   4 7 7 7 7 8 9 9 9 9 10
   5  6  3  8  12  14  9  47  54  89
   0 4 7 7 7 7 8 9 9 9 9
   5 6 3 8 12 14 9 47 54 89
   3 5 6 8 9 12 14 47 54 89
   */
