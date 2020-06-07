#pragma once
#ifndef LBPFEATURE_H
#define LBPFEATURE_H
#include "general.h"
#include "LBP.h"
#include "Library.h"

class LBPFeature
{
public:
	LBPFeature(C_UINT32 gridX, C_UINT32 gridY, C_UINT32 bin) : _gridX(gridX), _gridY(gridY), _bin(bin) {};
	~LBPFeature();

	void OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);

	void LBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);
private:

	void L1NormalizedHistogram8bit(std::vector<double>& histogram
		, C_UINT32 start, C_UINT32 end);

	C_UINT32 _gridX;
	C_UINT32 _gridY;
	C_UINT32 _bin;

};

#endif // !Feature

