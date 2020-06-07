#pragma once
#ifndef FEATURE_H
#define FEATURE_H
#include "general.h"
#include "Library.h"

class Feature
{
public:
	Feature(C_UINT32 gridX, C_UINT32 gridY, C_UINT32 bin) : _gridX(gridX), _gridY(gridY), _bin(bin) {};
	~Feature();

	void OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);
private:
	void OriginalLBP(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height);

	void L1NormalizedHistogram8bit(std::vector<double>& histogram
		, C_UINT32 start, C_UINT32 end);

	void LBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);

	C_UINT32 _gridX;
	C_UINT32 _gridY;
	C_UINT32 _bin;

};

#endif // !Feature

