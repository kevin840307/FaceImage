#pragma once
#ifndef LBPFEATURE_H
#define LBPFEATURE_H
#include "general.h"
#include "Library.h"
#include <bitset>

class LBPFeature
{
public:
	LBPFeature(C_UINT32 gridX, C_UINT32 gridY, C_UINT32 bin) : _gridX(gridX), _gridY(gridY), _bin(bin) {};
	~LBPFeature();

	void OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);

	void EquivalentLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);

	void OriginalLBP(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height);

	void CircularLBP(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 radius = 1, C_UINT32 bin = 8);

	void EquivalentLBP(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 radius = 1, C_UINT32 bin = 8);
private:

	void EquivalentTable(UCHAR* table);

	void L1NormalizedHistogram8bit(std::vector<double>& histogram
		, C_UINT32 start, C_UINT32 end);

	void LBPHistogram(C_UCHAR* src, std::vector<double>& histogram
		, C_UINT32 width, C_UINT32 height);

	C_UINT32 _gridX;
	C_UINT32 _gridY;
	C_UINT32 _bin;

};

#endif // !Feature

