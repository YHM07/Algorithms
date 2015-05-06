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
		std::cout << A[i] << "  ";
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
//template <class T>
template <class T>
void swap(T &p, T &q)
{
	if (p != q) {
		p ^= q;
		q ^= p;
		p ^= q; 
	}
}
#endif  /* ---- not COMM-INL_H_*/
