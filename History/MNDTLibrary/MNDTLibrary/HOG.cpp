#include "HOG.h"

HOG::HOG()
{
	LOG_FILE = "D:\\Log.txt";
	_fwLog.open(LOG_FILE, std::ios::app);
	_binSize = 9;
}

HOG::~HOG()
{
	_fwLog.close();
}


void HOG::GetHOGVector(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height
	, const UINT32 cellSplitW, const UINT32 cellSplitH
	, const UINT32 blockSplitW, const UINT32 blockSplitH
	, const double drawBase)
{
	// 計算梯度方向和梯度大小
	UCHAE* purHead = pur;
	int** directions = nullptr;
	int** amplitudes = nullptr;
	directions = MNDT::CreateArray(directions, height, width);
	amplitudes = MNDT::CreateArray(amplitudes, height, width);

	Gradient(src, pur, directions, amplitudes, width, height);

	// 計算每個Cell
	double*** cellBin = nullptr;
	UINT32 cellWidth = width / cellSplitW;
	UINT32 cellHeight = height / cellSplitH;
	cellBin = MNDT::CreateArray(cellBin, cellHeight, cellWidth, _binSize);
	CellSplit(cellBin
		, const_cast<const int**>(directions), const_cast<const int**>(amplitudes)
		, width, height
		, cellSplitW, cellSplitH);

	// 計算每個Block
	double*** blockBin = nullptr;
	UINT32 blockWidth = cellWidth - blockSplitW + 1;
	UINT32 blockHeight = cellHeight - 2 + 1;
	blockBin = MNDT::CreateArray(blockBin, blockHeight, blockWidth, (_binSize * 4));
	BlockSplit(blockBin, const_cast<const double***>(cellBin)
		, cellWidth, cellHeight
		, blockSplitW, blockSplitH);

	ViewHOGHistogram(purHead
		, const_cast<const double***>(blockBin)
		, cellSplitW, cellSplitH
		, blockSplitW, blockSplitH
		, cellWidth, cellHeight
		, blockWidth, blockHeight
		, drawBase);

	MNDT::DeleteArray(blockBin, blockHeight, blockWidth);
	MNDT::DeleteArray(cellBin, cellHeight, cellWidth);
	MNDT::DeleteArray(directions, height);
	MNDT::DeleteArray(amplitudes, height);
}


void HOG::Gamma(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height
	, const double gamma)
{
	UINT32 gammaLUT[256];
	double pix = 0;

	for (UINT32 index = 0; index < 256; index++)
	{
		pix = (index + 0.5) / 256.0; //歸一化
		pix = pow(pix, gamma);
		gammaLUT[index] = static_cast<UINT32>((pix * 256 - 0.5)); //反歸一化
	}

	const int maxLen = width * height;

	for (int index = 0; index < maxLen; index++)
	{
		*pur = gammaLUT[*src];
		pur++;
		src++;
	}
}

void HOG::Gradient(const UCHAE* src, UCHAE* pur
	, int** directions, int** amplitudes
	, const UINT32 width, const UINT32 height)
{
	const double Angle = 180.0 / MNDT::PI;
	src += width + 1;
	pur += width + 1;

	for (UINT32 col = 1; col < height - 1; col++)
	{
		for (UINT32 row = 1; row < width - 1; row++)
		{
			double Gx = *(src + 1) - *(src - 1);
			double Gy = *(src + width) - *(src - width);
			// radius
			int amplitude = static_cast<int>(sqrt(Gx * Gx + Gy *Gy));
			// angle
			int direction = abs(static_cast<int>(atan2(Gy, Gx) * Angle));

			amplitudes[col][row] = amplitude;
			directions[col][row] = direction;

			*pur = amplitude;
			src++;
			pur++;
		}
		src += 2;
		pur += 2;
	}
}

void HOG::Gradient(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height)
{
	const double Angle = 180.0 / MNDT::PI;
	src += width + 1;
	pur += width + 1;

	for (UINT32 col = 1; col < height - 1; col++)
	{
		for (UINT32 row = 1; row < width - 1; row++)
		{
			double Gx = *(src + 1) - *(src - 1);
			double Gy = *(src + width) - *(src - width);
			int amplitude = static_cast<int>(sqrt(Gx * Gx + Gy *Gy));

			*pur = amplitude;
			src++;
			pur++;
		}
		src += 2;
		pur += 2;
	}
}

void HOG::CellSplit(double*** bins
	, const int** directions, const int** amplitudes
	, const UINT32 width, const UINT32 height
	, const UINT32 splitW, const UINT32 splitH)
{
	UINT32 binIndexW = 0;
	UINT32 binIndexH = 0;

	for (UINT32 indexH = splitH; indexH <= height; indexH += splitH)
	{
		binIndexW = 0;
		for (UINT32 indexW = splitW; indexW <= width; indexW += splitW)
		{
			CellHistogram(bins[binIndexH][binIndexW]
				, directions, amplitudes
				, indexW - splitW, indexH - splitH
				, indexW, indexH);
			binIndexW++;
		}
		binIndexH++;
	}
}

void HOG::CellHistogram(double* bin
	, const int** directions, const int** amplitudes
	, const UINT32 minWidth, const UINT32 minHeight
	, const UINT32 maxWidth, const UINT32 maxHeight)
{
	for (UINT32 col = minHeight; col < maxHeight; col++)
	{
		for (UINT32 row = minWidth; row < maxWidth; row++)
		{
			UINT32 nowPos = AnglePosition(directions[col][row]);
			UINT32 prePos = (nowPos == 0) ? 8 : nowPos - 1;
			double nowAngleVote = static_cast<double>(directions[col][row])
				* static_cast<double>(directions[col][row] - nowPos * 20)
				/ 20.0;

			bin[nowPos] += nowAngleVote;
			bin[prePos] += (directions[col][row] - nowAngleVote);
		}
	}
}

void HOG::BlockSplit(double*** blockBin, const double*** cellBin
	, const UINT32 cellWidth, const UINT32 cellHeight
	, const UINT32 splitW, const UINT32 splitH)
{

	UINT32 blockIndexW = 0;
	UINT32 blockIndexH = 0;

	for (UINT32 indexH = splitH; indexH <= cellHeight; indexH++)
	{
		blockIndexW = 0;
		for (UINT32 indexW = splitW; indexW <= cellWidth; indexW++)
		{
			NormL2(blockBin[blockIndexH][blockIndexW], cellBin
				, indexW - splitW, indexH - splitH
				, indexW, indexH);
			blockIndexW++;
		}
		blockIndexH++;
	}
}

void HOG::NormL2(double* bin, const double*** cellBin
	, const UINT32 minWidth, const UINT32 minHeight
	, const UINT32 maxWidth, const UINT32 maxHeight)
{
	double sum = 0;

	for (UINT32 col = minHeight; col < maxHeight; col++)
	{
		for (UINT32 row = minWidth; row < maxWidth; row++)
		{
			for (UINT32 index = 0; index < _binSize; index++)
			{
				sum += (cellBin[col][row][index] * cellBin[col][row][index]);
			}
		}
	}
	sum = sqrt(sum + exp(2));

	int binIndex = 0;

	for (UINT32 col = minHeight; col < maxHeight; col++)
	{
		for (UINT32 row = minWidth; row < maxWidth; row++)
		{
			for (UINT32 index = 0; index < _binSize; index++)
			{
				bin[binIndex] = cellBin[col][row][index] / sum;
				binIndex++;
			}
		}
	}
}

void HOG::ViewHOGHistogram(UCHAE* pur
	, const double*** blockBin
	, const UINT32 cellSplitW, const UINT32 cellSplitH
	, const UINT32 blockSplitW, const UINT32 blockSplitH
	, const UINT32 cellWidth, const UINT32 cellHeight
	, const UINT32 blockWidth, const UINT32 blockHeight
	, const double drawBase)
{
	UINT32** counts = nullptr;
	double*** avgBin = nullptr;
	counts = MNDT::CreateArray(counts, cellHeight, cellWidth);
	avgBin = MNDT::CreateArray(avgBin, cellHeight, cellWidth, _binSize);

	// block loop
	for (UINT32 bColIndex = 0; bColIndex < blockHeight; bColIndex++)
	{
		for (UINT32 bRolIndex = 0; bRolIndex < blockWidth; bRolIndex++)
		{
			int binIndex = 0;

			// block's (size = 4) * cell loop
			for (UINT32 cColIndex = bColIndex; cColIndex < bColIndex + blockSplitH; cColIndex++)
			{
				for (UINT32 cRowIndex = bRolIndex; cRowIndex < bRolIndex + blockSplitW; cRowIndex++)
				{
					// histogram bin loop
					for (UINT32 index = 0; index < _binSize; index++)
					{
						avgBin[cColIndex][cRowIndex][index] += blockBin[bColIndex][bRolIndex][binIndex];
						binIndex++;
					}
					counts[cColIndex][cRowIndex]++;
				}
			}
		}
	}

	// block loop compute avg
	for (UINT32 col = 0; col < cellHeight; col++)
	{
		for (UINT32 row = 0; row < cellWidth; row++)
		{
			// histogram bin loop
			for (UINT32 index = 0; index < _binSize; index++)
			{
				avgBin[col][row][index] /= static_cast<double>(counts[col][row]);
			}
		}
	}

	// draw line
	const UINT32 width = cellWidth * cellSplitW;
	UINT32 centerX = 0;
	UINT32 centerY = cellSplitH / 2;
	for (UINT32 col = 0; col < cellHeight; col++)
	{
		centerX = cellSplitW / 2;

		for (UINT32 row = 0; row < cellWidth; row++)
		{
			// histogram bin loop
			for (UINT32 index = 0; index < _binSize; index++)
			{
				if (avgBin[col][row][index] == 0)
				{
					continue;
				}
				double angle = index * _binSize + _binSize / 2;
				double vecX = cos(angle);
				double vecY = sin(angle);
				double maxX = cellSplitW / 2;
				double maxY = cellSplitH / 2;
				int x1 = static_cast<int>(centerX - vecX * avgBin[col][row][index] * maxX * drawBase);
				int y1 = static_cast<int>(centerY - vecY * avgBin[col][row][index] * maxY * drawBase);
				int x2 = static_cast<int>(centerX + vecX * avgBin[col][row][index] * maxX * drawBase);
				int y2 = static_cast<int>(centerY + vecY * avgBin[col][row][index] * maxY * drawBase);
				MNDT::DrawLine(pur, width, Point(x1, y1), Point(x2, y2));
			}
			centerX += cellSplitW;
		}
		centerY += cellSplitH;
	}

	MNDT::DeleteArray(counts, cellHeight);
	MNDT::DeleteArray(avgBin, cellHeight, cellWidth);
}

int HOG::AnglePosition(const int angle)
{
	if (angle > 0 && angle <= 20)
	{
		return 0;
	}
	else if (angle <= 40)
	{
		return 1;
	}
	else if (angle <= 60)
	{
		return 2;
	}
	else if (angle <= 80)
	{
		return 3;
	}
	else if (angle <= 100)
	{
		return 4;
	}
	else if (angle <= 120)
	{
		return 5;
	}
	else if (angle <= 140)
	{
		return 6;
	}
	else if (angle <= 160)
	{
		return 7;
	}
	else
	{
		return 8;
	}
}