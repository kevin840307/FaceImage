#include "LBPFeature.h"

LBPFeature::~LBPFeature()
{
}


void LBPFeature::OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;
	UCHAR* purData = new UCHAR[width * height]{ 0 };
	lbp.OriginalLBP(src, purData
		, width, height);

	LBPHistogram(purData, histogram
		, width, height);

	delete[] purData;
	purData = nullptr;
}

void LBPFeature::LBPHistogram(C_UCHAR* src, std::vector<double>& histogram
	, C_UINT32 width, C_UINT32 height)
{
	// 1. init params
	Image srcImage(const_cast<UCHAR*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	C_UINT32 cellWidth = static_cast<UINT32>(ceil(static_cast<float>(width) / _gridX));
	C_UINT32 cellHeight = static_cast<UINT32>(ceil(static_cast<float>(height) / _gridY));

	// 2. calculate histogram
	for (UINT32 row = 0; row < height; row++)
	{
		UINT32 hisRowIndex = row / cellHeight * _gridX;

		for (UINT32 col = 0; col < width; col++)
		{
			UINT32 hisColIndex = col / cellWidth;
			UINT32 hisIndex = (hisColIndex + hisRowIndex) * _bin;

			histogram[hisIndex + (srcImage.image[row][col] % _bin)]++;
		}
	}

	// 3. normalized histogram
	C_UINT32 histogramSize = _gridX * _gridY;

	for (UINT32 index = 0; index < histogramSize; index++)
	{
		L1NormalizedHistogram8bit(histogram, index * _bin, index * _bin + _bin);
	}
}

void LBPFeature::L1NormalizedHistogram8bit(std::vector<double>& histogram
	, C_UINT32 start, C_UINT32 end)
{
	double L1 = 0;
	C_UINT32 size = histogram.size();

	for (UINT32 index = start; index < end; index++)
	{
		L1 += histogram[index];
	}


	for (UINT32 index = start; index < end; index++)
	{
		histogram[index] /= L1;
	}
}