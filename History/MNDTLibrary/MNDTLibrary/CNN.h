#pragma once
#ifndef CNN_H
#define CNN_H
#include "MNDTLibrary.h"
#include "CNNFilter.h"

class CNN {
public:
	void Convolution(const UCHAE* src, UCHAE* pur
					, const UINT32 width, const UINT32 height);
private:
};

#endif // !CNN_H
