#include "GHLibrary.h"

GHLibrary::GHLibrary()
{
	g_fwLog.open(LOG_FILE, ios::app);//開啟檔案
}

GHLibrary::~GHLibrary()
{
	g_fwLog.close();
}

// 灰階
// R 0.299 ≈ 19595
// G 0.587 ≈ 38469
// B 0.114 ≈ 7472 (進位 反推回去比7471接近)
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void GHLibrary::fnBGR2Gray(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		int iB = cSource[0];
		cSource++;

		int iG = cSource[0];
		cSource++;

		int iR = cSource[0];
		cSource++;

		int iPix = (iR * 19595 + iG * 38469 + iB * 7472) >> 16;
		cPurpose[0] = iPix;
		cPurpose++;
		cPurpose[0] = iPix;
		cPurpose++;
		cPurpose[0] = iPix;
		cPurpose++;
	}
}

void GHLibrary::fnBGR2Gray8b(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		int iB = cSource[0];
		cSource++;

		int iG = cSource[0];
		cSource++;

		int iR = cSource[0];
		cSource++;

		int iPix = (iR * 19595 + iG * 38469 + iB * 7472) >> 16;
		*cPurpose = iPix;
		cPurpose++;
	}
}

// BGR轉HSV
// MAX(R, G, B) MIN(R, G, B)
// 300° ~ 60° R 中間值 0°
// 60° ~ 180° G 中間值 120°
// 180° ~ 300° B 中間值 240°
//
// H = 0, S = 0 條件：MAX == MIN
//
// H 公式
// 60° * (G - B) / (MAX - MIN) 條件：if MAX == R && G >= B
// 60° * (G - B) / (MAX - MIN) + 360° 條件：if MAX == R && G < B
// 60° * (B - R) / (MAX - MIN) + 120° 條件：if MAX == G
// 60° * (R - G) / (MAX - MIN) + 240° 條件：if MAX == B
//
// S 公式
// (MAX - MIN) / MAX * 100(轉百分比整數)
//
// V 公式
// MAX / 255 * 100(轉百分比整數)
void GHLibrary::fnBGR2HSV(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		double dH = 0;
		double dS = 0;
		double dV = 0;
		int iB = 0;
		int iG = 0;
		int iR = 0;
		int iMax = 0;
		int iMin = 0;

		iB = cSource[0];
		cSource++;
		iG = cSource[0];
		cSource++;
		iR = cSource[0];
		cSource++;
		iMax = std::max(std::max(iR, iG), iB);
		iMin = std::min(std::min(iR, iG), iB);

		if (iMax == iMin)
		{
			dS = 0;
			dH = 0;
		}
		else
		{
			if (iR == iMax)
			{
				dH = (double)(iG - iB) / (double)(iMax - iMin);
			}
			else if (iG == iMax)
			{
				dH = 2.0 + (double)(iB - iR) / (double)(iMax - iMin);
			}
			else if (iB == iMax)
			{
				dH = 4.0 + (double)(iR - iG) / (double)(iMax - iMin);
			}
			dH = dH * 60.0;
			dH = (dH < 0) ? dH + 360 : dH;
			dH /= 2;
			dS = (double)(iMax - iMin) / (double)iMax * 255.0 + 0.5; // -(dMax * iS / 100 - dMax)
		}
		dV = iMax;
		cPurpose[0] = (int)dH;
		cPurpose++;
		cPurpose[0] = (int)dS;
		cPurpose++;
		cPurpose[0] = (int)dV;
		cPurpose++;
	}
}

// HSV轉BGR
void GHLibrary::fnHSV2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dVBase)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		double dH = 0;
		double dS = 0;
		double dV = 0;
		double dMax = 0;
		double dMin = 0;
		double dOffset = 0;
		int iBase = 0;

		dH = (double)cSource[0] * 2.0;
		cSource++;
		dS = (double)cSource[0];
		cSource++;
		dV = (double)cSource[0] * dVBase;
		dV = (dV > 255.0) ? 255.0 : dV;
		cSource++;
		dMax = dV;
		dMin = dMax * (255.0 - dS) / 255.0; // -(dMax * iS / 255 - dMax)
		iBase = (int)dH / 60;
		dOffset = ((dMax - dMin) * ((int)dH % 60)) / 60.0; // (X - Y) = (MAX - MIN) * H % 60 * 60 (H % 60 = 取得不滿足1的剩餘角度)

		switch (iBase)
		{
		case 0:
			cPurpose[0] = (int)dMin;
			cPurpose++;
			cPurpose[0] = (int)(dMin + dOffset);
			cPurpose++;
			cPurpose[0] = (int)dMax;
			cPurpose++;
			break;
		case 1:
			cPurpose[0] = (int)dMin;
			cPurpose++;
			cPurpose[0] = (int)dMax;
			cPurpose++;
			cPurpose[0] = (int)(dMax - dOffset); // -(((double)iH / 60.0 - 2) * (dMax - dMin) - dMin)
			cPurpose++;
			break;
		case 2:
			cPurpose[0] = (int)(dMin + dOffset);
			cPurpose++;
			cPurpose[0] = (int)dMax;
			cPurpose++;
			cPurpose[0] = (int)dMin;
			cPurpose++;
			break;
		case 3:
			cPurpose[0] = (int)dMax;
			cPurpose++;
			cPurpose[0] = (int)(dMax - dOffset); // -(((double)iH / 60.0 - 4) * (dMax - dMin) - dMin)
			cPurpose++;
			cPurpose[0] = (int)dMin;
			cPurpose++;
			break;
		case 4:
			cPurpose[0] = (int)dMax;
			cPurpose++;
			cPurpose[0] = (int)dMin;
			cPurpose++;
			cPurpose[0] = (int)(dMin + dOffset);
			cPurpose++;
			break;
		case 5:
			cPurpose[0] = (int)(dMax - dOffset); //-((iH - 360) / 60 * (dMax - dMin) - dMin)
			cPurpose++;
			cPurpose[0] = (int)dMin;
			cPurpose++;
			cPurpose[0] = (int)dMax;
			cPurpose++;
			break;
		}
	}
}

// 灰階二值化
void GHLibrary::fnThresholdingOTSU(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iScale)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		unsigned char cPix = 0;
		if (cSource[0] < iScale)
		{
			cPix = 255;
		}
		*cPurpose = cPix;
		cPurpose++;
		cSource++;
	}
}

// 8位元OTUS闊值
// OTUS
// 先將圖片顏色分類計算數量.平均
// 計算1 ~ 255背景和前景擴值差距, 取得其中最大擴值
// W0 = 第一類(背景)概率, 
// S0 = 第一類(背景)數值和, 
// U0 = 第一類(背景)均值, 
// W1 = 第二類(背景)概率, 
// S1 = 第二類(背景)數值和, 
// U1 = 第二類(背景)均值
// U = 總數值和
// 公式
// W0 = sigma(index)
// S0 = sigma(index) * value(Gray像素)
// W1 = sigma(index + 1 ~ 255)
// S1 = sigma(index + 1 ~ 255) * value(Gray像素)
// U0 = S0 / W0 
// U1 = S1 / W1
// U = S0 + S1
// Scale = W0 * (U0 - U) * (U0 - U) + W1 * (U1 - U) * (U1 - U) // (sqrt(X ^ 2, Y ^ 2))相似於算距離
int GHLibrary::fnGetThresholdingScale(const unsigned char* cSource, const int iRows, const int iCols)
{

	const int iIndexMax = iRows * iCols;
	std::vector<int> vcGrayHistogram(256, 0);
	std::vector<double> vcGrayAvg(256, 0);

	for (int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		vcGrayHistogram[*cSource]++;
		cSource++;
	}

	for (int iIndex = 0; iIndex < 256; iIndex++)
	{
		vcGrayAvg[iIndex] = (double)(vcGrayHistogram[iIndex]) / (double)iIndexMax;
	}

	int indexMax = 0;
	double dMaxScale = -1;

	for (int iPos = 0; iPos < 256; iPos++)
	{
		double dW0 = 0;
		double dS0 = 0;
		double dU0 = 0;
		double dW1 = 0;
		double dS1 = 0;
		double dU1 = 0;
		double dArgU = 0;
		double dScale = -1;

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			if (iIndex <= iPos) //背景部分  
			{
				dW0 += vcGrayAvg[iIndex];
				dS0 += iIndex * vcGrayAvg[iIndex];
			}
			else			//前景部分  
			{
				dW1 += vcGrayAvg[iIndex];
				dS1 += iIndex * vcGrayAvg[iIndex];
			}
		}

		dU0 = dS0 / dW0;
		dU1 = dS1 / dW1;
		dArgU = dS0 + dS1;
		dScale = dW0 * (dU0 - dArgU) * (dU0 - dArgU) + dW1 * (dU1 - dArgU) * (dU1 - dArgU);

		if (dScale > dMaxScale)
		{
			dMaxScale = dScale;
			indexMax = iPos;
		}
	}

	return indexMax;
}

void GHLibrary::fnHSV2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		unsigned char cH = cSource[0];
		cSource++;
		unsigned char cS = cSource[0];
		cSource++;
		unsigned char cV = cSource[0];
		cSource++;
		unsigned char cPix = 0;

		if (cH <= 20 && cS >= 48 && cV >= 50)
		{
			cPix = 255;
		}

		cPurpose[0] = cPix;
		cPurpose++;
		cPurpose[0] = cPix;
		cPurpose++;
		cPurpose[0] = cPix;
		cPurpose++;
	}
}

// 邊緣偵測8bit
// 3 X 3 X濾鏡 + Y濾鏡 算權重 與闊值相比
void GHLibrary::fnSobel(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dScale)
{
	const int iXBase[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	const int iYBase[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };

	cPurpose += iRows;
	cSource += iRows;

	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		const unsigned char* cLastSource = (cSource - iRows);
		const unsigned char* cNextSource = (cSource + iRows);

		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			int iXPix = 0;
			int iYPix = 0;
			double dPix = 0.0;

			// X
			iXPix += *(cLastSource + (iRow - 1)) * iXBase[0];
			iXPix += *(cLastSource + iRow) * iXBase[1];
			iXPix += *(cLastSource + (iRow + 1)) * iXBase[2];

			iXPix += *(cNextSource + (iRow - 1)) * iXBase[6];
			iXPix += *(cNextSource + iRow) * iXBase[7];
			iXPix += *(cNextSource + (iRow + 1)) * iXBase[8];

			//Y
			iYPix += *(cLastSource + (iRow - 1)) * iYBase[0];
			iYPix += *(cLastSource + (iRow + 1)) * iYBase[2];

			iYPix += *(cSource + (iRow - 1)) * iYBase[3];
			iYPix += *(cSource + (iRow + 1)) * iYBase[5];

			iYPix += *(cNextSource + (iRow - 1)) * iYBase[6];
			iYPix += *(cNextSource + (iRow + 1)) * iYBase[8];

			dPix = (double)(std::abs(iXPix) + std::abs(iYPix) + 0.5);
			dPix = (dPix > (100 * dScale)) ? dPix = 255.0 : dPix = 0.0;

			*cPurpose = (unsigned char)dPix;
			cPurpose++;
		}
		cSource += iRows;
		cPurpose += 2; // 位移6個記憶體位置 因左右邊不算
	}
}

// 8位元膨脹
void GHLibrary::fnExpansion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const int iBase[] = { 1, 2, 1, 3, 1, 2, 1, 0, 3 };

	cSource += iRows;
	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		const unsigned char* cLastSource = cSource - iRows;
		const unsigned char* cNextSource = cSource + iRows;

		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			int iMax = 0;
			int iSave[9];

			iSave[0] = *cLastSource + iBase[0];
			iSave[1] = *(cLastSource + 1) + iBase[1];
			iSave[2] = *(cLastSource + 2) + iBase[2];
			iSave[3] = *cSource + iBase[3];
			iSave[4] = *(cSource + 1) + iBase[4];
			iSave[5] = *(cSource + 2) + iBase[5];
			iSave[6] = *cNextSource + iBase[6];
			iSave[7] = *(cNextSource + 1) + iBase[7];
			iSave[8] = *(cNextSource + 2) + iBase[8];

			for (int iIndex = 0; iIndex < 9; iIndex++)
			{
				if (iSave[iIndex] > iMax)
				{
					iMax = iSave[iIndex];
				}
			}

			iMax = iMax > 255 ? 255 : iMax;
			*cPurpose = iMax;
			cPurpose++;
			cSource++;
			cLastSource++;
			cNextSource++;
		}
		cPurpose += 2;
		cSource += 2;
	}
}

// 侵蝕
void GHLibrary::fnErosion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const int iBase[] = { 1, 2, 1, 3, 1, 2, 1, 0, 3 };

	cSource += iRows;
	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		const unsigned char* cLastSource = cSource - iRows;
		const unsigned char* cNextSource = cSource + iRows;

		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			int iMin = 255;
			int iSave[9];

			iSave[0] = *cLastSource - iBase[0];
			iSave[1] = *(cLastSource + 1) - iBase[1];
			iSave[2] = *(cLastSource + 2) - iBase[2];
			iSave[3] = *cSource - iBase[3];
			iSave[4] = *(cSource + 1) - iBase[4];
			iSave[5] = *(cSource + 2) - iBase[5];
			iSave[6] = *cNextSource - iBase[6];
			iSave[7] = *(cNextSource + 1) - iBase[7];
			iSave[8] = *(cNextSource + 2) - iBase[8];

			for (int iIndex = 0; iIndex < 9; iIndex++)
			{
				if (iSave[iIndex] < iMin)
				{
					iMin = iSave[iIndex];
				}
			}

			iMin = iMin < 0 ? 0 : iMin;
			*cPurpose = iMin;
			cPurpose++;
			cSource++;
			cLastSource++;
			cNextSource++;
		}

		cSource += 2;
		cPurpose += 2;
	}
}

void GHLibrary::fnSub(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;
	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		cPurpose[0] = cSource1[0] - cSource2[0];
		cPurpose++;
		cSource1++;
		cSource2++;
		cPurpose[0] = cSource1[0] - cSource2[0];
		cPurpose++;
		cSource1++;
		cSource2++;
		cPurpose[0] = cSource1[0] - cSource2[0];
		cPurpose++;
		cSource1++;
		cSource2++;
	}
}

// 平滑
void GHLibrary::fnBlur(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iRBGWidth = iRows * 3;
	const unsigned int iMaxWidth = iRBGWidth - 3;
	const unsigned char* cLastSource = cSource;
	const unsigned char* cNextSource = cSource + iRBGWidth;

	cSource += iRBGWidth;
	cPurpose += iRBGWidth;

	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		cLastSource = cSource - iRBGWidth;
		cNextSource = cSource + iRBGWidth;
		for (unsigned int iRow = 3; iRow < iMaxWidth; iRow++)
		{
			int iSum = 0;

			iSum += *(cLastSource + (iRow - 3));
			iSum += *(cLastSource + iRow);
			iSum += *(cLastSource + (iRow + 3));
			iSum += *(cSource + (iRow - 3));
			iSum += *(cSource + iRow);
			iSum += *(cSource + (iRow + 3));
			iSum += *(cNextSource + (iRow - 3));
			iSum += *(cNextSource + iRow);
			iSum += *(cNextSource + (iRow + 3));

			iSum = (int)((double)iSum / 9.0 + 0.5);
			cPurpose[0] = iSum;
			cPurpose++;
		}
		cSource += iRBGWidth;
		cPurpose += 6; // 位移6個記憶體位置 因左右邊不算
	}
}

//// 平滑
//void GHLibrary::fnBlur(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
//{
//	const unsigned int iRBGWidth = iRows * 3;
//
//	for (int iIndex = 0; iIndex < iRBGWidth; iIndex++)
//	{
//		cPurpose[0] = cSource[0];
//		cSource++;
//		cPurpose++;
//	}
//
//	for (int iCol = 1; iCol < iCols - 1; iCol++)
//	{
//		cPurpose[0] = cSource[0];
//		cPurpose++;
//		cPurpose[0] = (cSource + 1)[0];
//		cPurpose++;
//		cPurpose[0] = (cSource + 2)[0];
//		cPurpose++;
//		const unsigned char* cLastSource = cSource - iRBGWidth;
//		const unsigned char* cNextSource = cSource + iRBGWidth;
//		const unsigned int iMaxWidth = iRBGWidth - 3;
//		for (unsigned int iRow = 3; iRow < iMaxWidth; iRow++)
//		{
//			int iMin = 255;
//			int iSum = 0;
//
//			iSum += *(cLastSource + (iRow - 3));
//			iSum += *(cLastSource + iRow);
//			iSum += *(cLastSource + (iRow + 3));
//			iSum += *(cSource + (iRow - 3));
//			iSum += *(cSource + iRow);
//			iSum += *(cSource + (iRow + 3));
//			iSum += *(cNextSource + (iRow - 3));
//			iSum += *(cNextSource + iRow);
//			iSum += *(cNextSource + (iRow + 3));
//
//			iSum = (int)((double)iSum / 9.0 + 0.5);
//			cPurpose[0] = iSum;
//			cPurpose++;
//		}
//		cSource += iRBGWidth;
//		cPurpose[0] = cSource[0];
//		cPurpose++;
//		cPurpose[0] = (cSource - 1)[0];
//		cPurpose++;
//		cPurpose[0] = (cSource - 2)[0];
//		cPurpose++;
//	}
//
//	for (int iIndex = 0; iIndex < iRBGWidth; iIndex++)
//	{
//		cPurpose[0] = cSource[0];
//		cSource++;
//		cPurpose++;
//	}
//}

//// 平滑8位元灰階處理
//void GHLibrary::fnBlur(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
//{
//	const int iRBGWidth = iRows * 3;
//
//	cSource += iRBGWidth;
//	cPurpose += iRBGWidth;
//	for (int iCol = 1; iCol < iCols - 1; iCol++)
//	{
//		const unsigned char* cLastSource = cSource - iRBGWidth;
//		const unsigned char* cNextSource = cSource + iRBGWidth;
//		for (int iRow = 1; iRow < iRows - 1; iRow++)
//		{
//			int iMin = 255;
//			int iSum = 0;
//
//			iSum += *(cLastSource + (iRow - 1) * 3);
//			iSum += *(cLastSource + iRow * 3);
//			iSum += *(cLastSource + (iRow + 1) * 3);
//			iSum += *(cSource + (iRow - 1) * 3);
//			iSum += *(cSource + iRow * 3);
//			iSum += *(cSource + (iRow + 1) * 3);
//			iSum += *(cNextSource + (iRow - 1) * 3);
//			iSum += *(cNextSource + iRow * 3);
//			iSum += *(cNextSource + (iRow + 1) * 3);
//
//			iSum = (int)((double)iSum / 9.0 + 0.5);
//			cPurpose[0] = iSum;
//			cPurpose++;
//			cPurpose[0] = iSum;
//			cPurpose++;
//			cPurpose[0] = iSum;
//			cPurpose++;
//		}
//		cSource += iRBGWidth;
//		cPurpose += 6; // 位移6個記憶體位置 因左右邊不算
//	}
//}

// 統一遮罩
void GHLibrary::fnMask(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iMask)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		cPurpose[0] = cSource[0] & iMask;
		cPurpose++;
		cSource++;
		cPurpose[0] = cSource[0] & iMask;
		cPurpose++;
		cSource++;
		cPurpose[0] = cSource[0] & iMask;
		cPurpose++;
		cSource++;
	}
}

// 浮水印
void GHLibrary::fnLSB(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		cPurpose[0] = (cSource1[0] & 0xf0) | (cSource2[0] & 0x0f);
		cPurpose++;
		cSource1++;
		cSource2++;
		cPurpose[0] = (cSource1[0] & 0xf0) | (cSource2[0] & 0x0f);
		cPurpose++;
		cSource1++;
		cSource2++;
		cPurpose[0] = (cSource1[0] & 0xf0) | (cSource2[0] & 0x0f);
		cPurpose++;
		cSource1++;
		cSource2++;
	}
}

// BGR轉YCbCr
// Y = (66 * R + 129 * G + 25 * B + 128) >> 8 + 16
// Cb = (-38 * R - 74 * G + 112 * B + 128) >> 8 + 128
// Cr = (112 * R - 94 * G - 18 * B + 128) >> 8 + 128
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void GHLibrary::fnBGR2YCbCr(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		int iB = cSource[0];
		cSource++;

		int iG = cSource[0];
		cSource++;

		int iR = cSource[0];
		cSource++;

		int iY = ((66 * iR + 129 * iG + 25 * iB + 128) >> 8) + 16;
		int iCb = ((-38 * iR - 74 * iG + 112 * iB + 128) >> 8) + 128;
		int iCr = ((112 * iR - 94 * iG - 18 * iB + 128) >> 8) + 128;

		iY = (iY < 0 ? 0 : (iY > 255 ? 255 : iY));
		iCb = (iCb < 0 ? 0 : (iCb > 255 ? 255 : iCb));
		iCr = (iCr < 0 ? 0 : (iCr > 255 ? 255 : iCr));

		cPurpose[0] = iY;
		cPurpose++;
		cPurpose[0] = iCr;
		cPurpose++;
		cPurpose[0] = iCb;
		cPurpose++;
	}
}

// YCbCr轉BGR
// R = (298 * (Y - 16) + 409 * (Cr - 128) + 128) >> 8
// G = (298 * (Y - 16) - 100 * (Cb - 128) - 208 * (Cr - 128) + 128) >> 8
// B = (298 * (Y - 16) + 516 * (Cr - 128) + 128) >> 8
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void GHLibrary::fnYCbCr2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		int iY = cSource[0] - 16;
		cSource++;

		int iCr = cSource[0] - 128;
		cSource++;

		int iCb = cSource[0] - 128;
		cSource++;

		int iR = (298 * iY + 409 * iCr + 128) >> 8;
		int iG = (298 * iY - 100 * iCb - 208 * iCr + 128) >> 8;
		int iB = (298 * iY + 516 * iCb + 128) >> 8;

		iR = (iR < 0 ? 0 : (iR > 255 ? 255 : iR));
		iG = (iG < 0 ? 0 : (iG > 255 ? 255 : iG));
		iB = (iB < 0 ? 0 : (iB > 255 ? 255 : iB));

		cPurpose[0] = iB;
		cPurpose++;
		cPurpose[0] = iG;
		cPurpose++;
		cPurpose[0] = iR;
		cPurpose++;
	}
}

void GHLibrary::fnYCbCr2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned int iIndexMax = iRows * iCols;

	for (unsigned int iIndex = 0; iIndex < iIndexMax; iIndex++)
	{
		unsigned char uY = cSource[0];
		cSource++;
		unsigned char uCr = cSource[0];
		cSource++;
		unsigned char uCb = cSource[0];
		cSource++;
		unsigned char uPix = 0;

		if (uCb >= 77 && uCb <= 127 && uCr >= 133 && uCr <= 173) // (uCb >= 77 && uCb <= 127 && uCr >= 133 && uCr <= 173)
		{
			uPix = 255;
		}

		cPurpose[0] = uPix;
		cPurpose++;
		cPurpose[0] = uPix;
		cPurpose++;
		cPurpose[0] = uPix;
		cPurpose++;
	}
}

// Haar小波轉換 將圖片縮小至 1/4
// 垂直低頻:H(x, y) = (F(x, y) + F(x, y + 1)) / 2
// 垂直高頻:H(x, y) = (F(x, y) - F(x, y + 1)) / 2
// 水平低頻:H(x, y) = (F(x, y) + F(x + 1, y)) / 2
// 水平高頻:H(x, y) = (F(x, y) - F(x + 1, y)) / 2
void GHLibrary::fnHaar(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const int kiWidthHalf = (iRows >> 1) * 3;
	unsigned char* cVertical = new unsigned char[iRows * iCols * 3];
	const unsigned char* kcVertical2 = cVertical;

	//垂直處理(左右)
	const unsigned char* kcSourceNext = cSource + 3;
	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 1; iRow < iRows; iRow += 2)
		{
			*cVertical = (*cSource + *kcSourceNext) >> 1;
			*(cVertical + kiWidthHalf) = std::abs((*cSource - *kcSourceNext) >> 1);
			cVertical += 1;
			cSource += 1;
			kcSourceNext += 1;
			*cVertical = (*cSource + *kcSourceNext) >> 1;
			*(cVertical + kiWidthHalf) = std::abs((*cSource - *kcSourceNext) >> 1);
			cVertical += 1;
			cSource += 1;
			kcSourceNext += 1;
			*cVertical = (*cSource + *kcSourceNext) >> 1;
			*(cVertical + kiWidthHalf) = std::abs((*cSource - *kcSourceNext) >> 1);
			cVertical += 1;
			cSource += 4;		// +4主要移到下一對位置
			kcSourceNext += 4;

		}
		cVertical += kiWidthHalf;
	}

	const int kiHeightHalf = (iRows * 3 * iCols) >> 1;
	const unsigned char* kcVerticalNext = kcVertical2 + (iRows * 3);
	const int kiMaxWidth = iRows * 3;
	// 水平處理(上下)
	for (int iCol = 1; iCol < iCols; iCol += 2)
	{
		for (int iRow = 0; iRow < kiMaxWidth; iRow++)
		{
			*cPurpose = (*kcVertical2 + *kcVerticalNext) >> 1;
			*(cPurpose + kiHeightHalf) = std::abs((*kcVertical2 - *kcVerticalNext) >> 1);
			cPurpose += 1;
			kcVertical2 += 1;
			kcVerticalNext += 1;
		}
		kcVertical2 += kiMaxWidth;
		kcVerticalNext += kiMaxWidth;
	}
}

// 0最小X
// 1最小Y
// 2最大X
// 3最大Y
void GHLibrary::fnSquare(unsigned char* cSource, const vector<vector<int>>* vcPoints, const int iRows, const int iCols)
{
	int iCount = 0;
	int iOffset1 = 0;
	int iOffset2 = 0;
	for (int iIndex = 1; iIndex < vcPoints->size(); iIndex++)
	{
		int iXLen = vcPoints->at(iIndex)[2] - vcPoints->at(iIndex)[0];
		int iYLen = vcPoints->at(iIndex)[3] - vcPoints->at(iIndex)[1];
		if (vcPoints->at(iIndex)[0] != INT_MAX && iXLen * iYLen > 50)
		{
			g_fwLog << "小X:" << vcPoints->at(iIndex)[0] << "小Y:" << vcPoints->at(iIndex)[1] << "大X:" << vcPoints->at(iIndex)[2] << "大Y:" << vcPoints->at(iIndex)[3] << endl;
			iCount = vcPoints->at(iIndex)[0];
			iOffset1 = iRows * vcPoints->at(iIndex)[1] + iCount;
			iOffset2 = iRows * vcPoints->at(iIndex)[3] + iCount;
			while (iCount < vcPoints->at(iIndex)[2])
			{
				*(cSource + iOffset1) = 105;
				iOffset1 += 1;

				*(cSource + iOffset2) = 105;
				iOffset2 += 1;

				iCount++;
			}

			iCount = vcPoints->at(iIndex)[1];
			iOffset1 = vcPoints->at(iIndex)[0] + iCount * iRows;
			iOffset2 = vcPoints->at(iIndex)[2] + iCount * iRows;
			while (iCount < vcPoints->at(iIndex)[3])
			{
				*(cSource + iOffset1) = 105;

				iOffset1 +=  iRows;

				*(cSource + iOffset2) = 105;

				iOffset2 +=  iRows;

				iCount++;
			}
		}
	}
}

void GHLibrary::fnContourFrame(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const unsigned char* cSourceNow = cSource + iRows + 1;
	unsigned char* cPurposeNow = cPurpose + iRows + 1;
	vector<int> vcLinks(1, 0);
	vector<int> vcMark(iRows * iCols, 0);
	int iPreviousIndex = 0;
	int iLeftIndex = iRows;
	int linkNum = 1;

	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			if (*cSourceNow == 255)
			{
				vector<int> vcLink;
				if (vcMark[iLeftIndex] != 0)
				{
					vcLink.push_back(vcMark[iLeftIndex]);
				}

				if (vcMark[iPreviousIndex] != 0)
				{
					vcLink.push_back(vcMark[iPreviousIndex]);
				}

				if (vcMark[iPreviousIndex + 1] != 0)
				{
					vcLink.push_back(vcMark[iPreviousIndex + 1]);
				}

				if (vcMark[iPreviousIndex + 2] != 0)
				{
					vcLink.push_back(vcMark[iPreviousIndex + 2]);
				}

				if (vcLink.empty())
				{
					vcMark[iLeftIndex + 1] = linkNum;
					vcLinks.push_back(linkNum);
					linkNum++;
				}
				else
				{
					sort(vcLink.begin(), vcLink.end());
					vcMark[iLeftIndex + 1] = vcLinks[vcLink[0]];
					for (int iIndex = 1; iIndex < vcLink.size(); iIndex++)
					{
						//和原本的最小等價比較
						if (vcLinks[vcLink[0]] < vcLinks[vcLink[iIndex]])
						{
							vcLinks[vcLink[iIndex]] = vcLinks[vcLink[0]];
						}
						else if (vcLinks[vcLink[0]] > vcLinks[vcLink[iIndex]])
						{
							vcLinks[vcLink[0]] = vcLinks[vcLink[iIndex]];
						}
					}
				}
			}
			iPreviousIndex++;
			iLeftIndex++;
			*cPurposeNow = *cSourceNow;
			cPurposeNow++;
			cSourceNow++;
		}
		iPreviousIndex += 2;
		iLeftIndex += 2;
		cSourceNow += 2;
		cPurposeNow += 2;
	}

	// 修正權重
	for (int iIndex = 1; iIndex < vcLinks.size(); iIndex++)
	{
		int iSaveValue = vcLinks[iIndex];
		int iSaveIndex = iIndex;
		while (iSaveValue != iSaveIndex)
		{
			iSaveValue = vcLinks[vcLinks[iSaveIndex]];
			iSaveIndex = vcLinks[iSaveIndex];
		}
		vcLinks[iIndex] = iSaveValue;
		//g_fwLog << vcLinks[iIndex] << " ";
	}

	// 掃描矩形座標
	// 0最小X
	// 1最小Y
	// 2最大X
	// 3最大Y
	vector<vector<int>> vcPoints(vcLinks.size(), vector<int>(4, INT_MAX));
	int iFindIndex = 0;
	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 0; iRow < iRows; iRow++)
		{
			if (vcMark[iFindIndex] > 0)
			{
				vector<int>* vcLinkPoint = &vcPoints[vcLinks[vcMark[iFindIndex]]];

				if (vcLinkPoint->at(0) == INT_MAX)
				{
					vcLinkPoint->at(0) = iRow;
					vcLinkPoint->at(1) = iCol;
					vcLinkPoint->at(2) = iRow;
					vcLinkPoint->at(3) = iCol;
				}
				else
				{
					if (vcLinkPoint->at(0) > iRow)
					{
						vcLinkPoint->at(0) = iRow;
					}
					else if (vcLinkPoint->at(2) < iRow)
					{
						vcLinkPoint->at(2) = iRow;
					}

					if (vcLinkPoint->at(1) > iCol)
					{
						vcLinkPoint->at(1) = iCol;
					}
					else if (vcLinkPoint->at(3) < iCol)
					{
						vcLinkPoint->at(3) = iCol;
					}
				}
			}
			iFindIndex += 1;
		}
	}

	fnSquare(cPurpose, &vcPoints, iRows, iCols);
}

void GHLibrary::fnGamma(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dGamma)
{
	const int kiMaxWidth = iRows * 3;
	float fSave = 0.0f;
	int gammaLUT[256];
	for (int iIndex = 0; iIndex < 256; iIndex++)
	{
		fSave = (iIndex + 0.5F) / 256;//歸一化
		fSave = (float)pow(fSave, dGamma);
		gammaLUT[iIndex] = static_cast<int>((fSave * 256 - 0.5F));//反歸一化
	}

	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 0; iRow < kiMaxWidth; iRow++)
		{
			cPurpose[0] = gammaLUT[cSource[0]];
			cPurpose++;
			cSource++;
		}
	}
}

void GHLibrary::fnTailoring(const unsigned char* cSource, unsigned char* cPurpose, const int iORows, const int iOCols, const int iRows, const int iCols)
{
	int iRowOffset = iORows - iRows;

	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 0; iRow < iRows; iRow++)
		{
			*cPurpose = *cSource;
			cPurpose++;
			cSource++;
		}
		cSource += iRowOffset;
	}
}

