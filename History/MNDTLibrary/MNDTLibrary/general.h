#pragma once
#ifndef GENERAL_H
#define GENERAL_H
#define UINT32 unsigned __int32
#define UCHAE unsigned char
#define Image unsigned char
#include "Point.h"
namespace MNDT {
	template <class T>
	inline void DeleteArray(T& ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}

	template <class T>
	inline void DeleteArray(T*& ptrs, const UINT32 size)
	{
		for (UINT32 index = 0; index < size; index++) 
		{
			DeleteArray(ptrs[index]);
		}

		DeleteArray(ptrs);
	}

	template <class T>
	inline void DeleteArray(T**& ptrs, const UINT32 size1, const UINT32 size2)
	{
		for (UINT32 index1 = 0; index1 < size1; index1++)
		{
			DeleteArray(ptrs[index1], size2);
		}
		DeleteArray(ptrs);
	}


	template <class T>
	inline T** CreateArray(T** ptrs, const UINT32 size1, const UINT32 size2)
	{
		ptrs = new T*[size1];
		for (UINT32 index = 0; index < size1; index++)
		{
			ptrs[index] = new T[size2]();
		}
		return ptrs;
	}

	template <class T>
	inline T*** CreateArray(T*** ptrs, const UINT32 size1, const UINT32 size2, const UINT32 size3)
	{
		ptrs = new T**[size1];
		for (UINT32 index = 0; index < size1; index++)
		{
			ptrs[index] = CreateArray(ptrs[index], size2, size3);
		}
		return ptrs;
	}

	/*
	DrawLine Parameter:
	pur		= purpose of image
	width	= pur's width
	p1		= Point start
	p2		= Point end
	*/

	extern void DrawLine(UCHAE* pur, const int width, Point& p1, Point& p2);
	extern double PI;
}
#endif // !GENERAL_H
