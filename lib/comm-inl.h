/**
 * @file comm-inl.h
 * @brief 
 * @author H.M.Yang, hmyang07@gmail.com
 * @version v1.0
 * @date 05/02/2015
 */

#ifndef COMM_INL_H_
#define COMM_INL_H_

#include <stdio.h>
#include <iostream>
//using namespace std;

/**
 * @brief	print 
 *
 * @tparam T
 * @param	A[]
 * @param	n
 */
template <class T>
void print(const T A[],int n)
{
	for (int i=0;i < n; ++i){
		std::cout << A[i] << "\t";
	}
	std::cout << std::endl;
}

/**
 * @brief	swap 
 *
 * @tparam T
 * @param	p
 * @param	q
 */
template <class T>
void swap(T *p,T *q)
{
	T tmp;
	tmp = *p;
	*p  = *q;
	*q  = tmp;
}
#endif  /* ---- not COMM-INL_H_*/
