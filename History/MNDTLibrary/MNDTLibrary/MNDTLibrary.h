#pragma once
#ifndef MNDT_LIBRARY_H
#define MNDT_LIBRARY_H

#include <vector>
#include <fstream>
#include <assert.h>
#include "general.h"

//指標方式傳入展開, 需要多一層指標指向原本指標
//namespace MNDT {
//	template <class T>
//	inline void Delete(T** ptr) 
//	{
//		delete[] *ptr; 
//		*ptr = nullptr;
//	}
//
//	template <class T>
//	inline void DeletePtrs(T*** ptrs, UINT32 size) 
//	{
//		for(UINT32 index = 0; index < size; index++) 
//		{
//			Delete(&(*ptrs)[index]);
//		}
//		Delete((*ptrs));
//	}
//}

enum ColerType
{
	BGR2GRAY_8BIT
};

class MNDTLibrary
{
public:

	MNDTLibrary();

	~MNDTLibrary();

	/*
	ChangeColor Parameter:
	src		= source of image
	pur		= purpose of image
	width		= Image's width
	height		= Image's height
	type		= change type
	*/
	void ChangeColor(const UCHAE* src, UCHAE* pur
		, const UINT32 width, const UINT32 height
		, const UINT32 type);

	void BGR2Gray8Bit(const UCHAE* src, UCHAE* pur
		, const UINT32 width, const UINT32 height);

private:
	const char* LOG_FILE;
	std::fstream _fwLog;
};

#endif // !MNDT_LIBRARY_H
