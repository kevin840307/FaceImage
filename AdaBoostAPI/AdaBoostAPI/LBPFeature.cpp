#include "stdafx.h"
#include "LBPFeature.h"

LBPFeature::~LBPFeature()
{
}

void LBPFeature::OriginalLBP(C_UCHAR* src, UCHAR* pur
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

void LBPFeature::CircularLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 radius, C_UINT32 bin)
{
	// 1. padding
	C_UINT32 padWidth = width + (radius << 1);
	C_UINT32 padHeight = height + (radius << 1);
	UCHAR* padData = new UCHAR[padWidth * padHeight]{ 0 };

	MNDT::ImagePadding8bit(src, padData, width, height, radius);


	// 2. calculate offset
	Image padImage(padData, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	UINT32 offsetBase = bin - 1;

	for (UINT32 index = 0; index < bin; index++)
	{
		C_FLOAT centerX = MNDT::FixValue(static_cast<float>(radius * cos(2.0 * MNDT::PI * index / bin)));
		C_FLOAT centerY = MNDT::FixValue(static_cast<float>(radius * sin(2.0 * MNDT::PI * index / bin)));

		C_INT32 x1 = static_cast<int32_t>(floor(centerX));
		C_INT32 y1 = static_cast<int32_t>(floor(centerX));
		C_INT32 x2 = static_cast<int32_t>(ceil(centerX));
		C_INT32 y2 = static_cast<int32_t>(ceil(centerX));

		C_FLOAT xOffset = centerX - x1;
		C_FLOAT yOffset = centerY - y1;

		//(y, x) -> (0, 0), (0, 1), (1, 0), (1, 1)
		C_FLOAT w1 = (1.0f - xOffset) * (1.0f - yOffset);
		C_FLOAT w2 = xOffset * (1.0f - yOffset);
		C_FLOAT w3 = (1.0f - xOffset) * yOffset;
		C_FLOAT w4 = xOffset * yOffset;

		// 3. calcuulate pixel
		for (UINT32 row = radius; row < padHeight - radius; row++)
		{
			for (UINT32 col = radius; col < padWidth - radius; col++)
			{
				UCHAR pix = 0;
				//pix = static_cast<UCHAR>(padImage.image[row + y1][col + x1] * w1
				//	+ padImage.image[row + y1][col + x2] * w2
				//	+ padImage.image[row + y2][col + x1] * w3
				//	+ padImage.image[row + y2][col + x2] * w4);
				pix = static_cast<UCHAR>(padImage.image[row + x1][col + y1] * w1
					+ padImage.image[row + x2][col + y1] * w2
					+ padImage.image[row + x1][col + y2] * w3
					+ padImage.image[row + x2][col + y2] * w4);
				purImage.image[row - radius][col - radius] |= (static_cast<UCHAR>(pix > padImage.image[row][col]) << offsetBase);
			}
		}
		offsetBase--;
	}

	delete[] padData;
	padData = nullptr;
}

void LBPFeature::EquivalentLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 radius, C_UINT32 bin)
{
	// 1. get circular lbp 
	CircularLBP(src, pur
		, width, height
		, radius, bin);


	// 2. set everyone equivalent of the pixels
	UCHAR table[256] = { 0 };

	EquivalentTable(table);



	// 3. change to equivalent lbp
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			purImage.image[row][col] = table[purImage.image[row][col]];
		}
	}
}

void LBPFeature::EquivalentTable(UCHAR* table)
{
	UCHAR pix = 1;

	for (UINT32 index = 0; index < 256; index++)
	{
		UINT32 count = 0;
		std::bitset<8> binary = index;

		for (UINT32 bitIndex = 0; bitIndex < 8; bitIndex++)
		{
			if (binary[bitIndex] != binary[(bitIndex + 1) % 8])
			{
				count++;
			}
		}

		if (count < 3)
		{
			table[index] = pix;
			pix++;
		}
	}
}

void LBPFeature::OriginalLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
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

void LBPFeature::EquivalentLBPHistogram(C_UCHAR* src, std::vector<double>& histogram
	, C_UINT32 width, C_UINT32 height)
{
	UCHAR* purData = new UCHAR[width * height]{ 0 };

	EquivalentLBP(src, purData
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