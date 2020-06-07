#pragma once
#ifndef HOG_H
#define HOG_H
#include "MNDTLibrary.h"
class HOG
{

public:
	HOG();
	~HOG();

	void GetHOGVector(const UCHAE* src, UCHAE* pubinr
		, const UINT32 width, const UINT32 height
		, const UINT32 cellSplitW, const UINT32 cellSplitH
		, const UINT32 blockSplitW, const UINT32 blockSplitH
		, const double drawBase);


	void Gamma(const UCHAE* src, UCHAE* pur
		, const UINT32 width, const UINT32 height
		, const double gamma);

	void Gradient(const UCHAE* src, UCHAE* pur
		, int** directions, int** amplitudes
		, const UINT32 width, const UINT32 height);

	void Gradient(const UCHAE* src, UCHAE* pur
		, const UINT32 width, const UINT32 height);

	void CellSplit(double*** bins
		, const int** directions, const int** amplitudes
		, const UINT32 width, const UINT32 height
		, const UINT32 splitW, const UINT32 splitH);

	/*
	CellHistogram Parameter:
	bin		= spilt's space (default 9 size)
	directions	= image's all direction // 梯度方向
	amplitudes = Image's all amplitude // 梯度幅度
	minWidth	= min width's index
	minHeight	= min height's index
	maxWidth	= max width's index
	maxHeight	= max height's index
	*/
	void CellHistogram(double* bin
		, const int** directions, const int** amplitudes
		, const UINT32 minWIndex, const UINT32 minHIndex
		, const UINT32 maxWIndex, const UINT32 maxHIndex);

	void BlockSplit(double*** blockBin, const double*** cellBin
		, const UINT32 cellWidth, const UINT32 cellHeight
		, const UINT32 splitW, const UINT32 splitH);


	void NormL2(double* bin, const double*** cellBin
		, const UINT32 minWidth, const UINT32 minHeight
		, const UINT32 maxWidth, const UINT32 maxHeight);

	void ViewHOGHistogram(UCHAE* pur
		, const double*** blockBin
		, const UINT32 cellSplitW, const UINT32 cellSplitH
		, const UINT32 blockSplitW, const UINT32 blockSplitH
		, const UINT32 cellWidth, const UINT32 cellHeight
		, const UINT32 blockWidth, const UINT32 blockHeight
		, const double drawBase);

	int AnglePosition(const int angle);

private:
	UINT32 _binSize;
	const char* LOG_FILE;
	std::fstream _fwLog;
};
#endif // !HOG_H
