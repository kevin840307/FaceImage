#include "stdafx.h"
#include "Feature.h"

Feature::~Feature()
{
}

void Feature::OriginalLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	// 1. padding
	C_UINT32 padWidth = width + 2;
	C_UINT32 padHeight = height + 2;
	UCHAR* padData = new UCHAR[padWidth * padHeight]{ 0 };

	MNDT::ImagePadding8bit(src, padData, width, height, 1);


	// 2. calculate original lbp
	Image padImage(padData, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = 1; row < padHeight - 1; row++)
	{
		for (UINT32 col = 1; col < padWidth - 1; col++)
		{
			UCHAR sum = 0;

			sum |= static_cast<UCHAR>(padImage.image[row - 1][col - 1] > padImage.image[row][col]) << 7;
			sum |= static_cast<UCHAR>(padImage.image[row - 1][col] > padImage.image[row][col]) << 6;
			sum |= static_cast<UCHAR>(padImage.image[row - 1][col + 1] > padImage.image[row][col]) << 5;
			sum |= static_cast<UCHAR>(padImage.image[row][col + 1] > padImage.image[row][col]) << 4;
			sum |= static_cast<UCHAR>(padImage.image[row + 1][col + 1] > padImage.image[row][col]) << 3;
			sum |= static_cast<UCHAR>(padImage.image[row + 1][col] > padImage.image[row][col]) << 2;
			sum |= static_cast<UCHAR>(padImage.image[row + 1][col - 1] > padImage.image[row][col]) << 1;
			sum |= static_cast<UCHAR>(padImage.image[row][col - 1] > padImage.image[row][col]);

			*pur = sum;
			pur++;
		}

	}

	delete[] padData;
	padData = nullptr;
}

void Feature::OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
	, C_UINT32 width, C_UINT32 height)
{
	UCHAR* purData = new UCHAR[width * height]{ 0 };

	OriginalLBP(src, purData
		, width, height);

	LBPHistogram(purData, histogram
		, width, height);

	delete[] purData;
	purData = nullptr;
}

void Feature::LBPHistogram(C_UCHAR* src, std::vector<double>& histogram
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

void Feature::L1NormalizedHistogram8bit(std::vector<double>& histogram
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