#include "GHLibraryLBP.h"

GHLibraryLBP::GHLibraryLBP()
{
	g_fwLog.open(LOG_FILE, ios::app);//開啟檔案
}

GHLibraryLBP::~GHLibraryLBP()
{
	g_fwLog.close();
}

void GHLibraryLBP::fnGeneralLBP(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	cSource += iRows + 1;

	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		const unsigned char* LastcSource = cSource - iRows;
		const unsigned char* NextcSource = cSource + iRows;

		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			unsigned char uPix = 0;
			uPix |= static_cast<int>((*(LastcSource - 1) > *cSource)) << 7;
			uPix |= static_cast<int>((*LastcSource > *cSource)) << 6;
			uPix |= static_cast<int>((*(LastcSource + 1) > *cSource)) << 5;
			uPix |= static_cast<int>((*(cSource + 1) > *cSource)) << 4;
			uPix |= static_cast<int>((*(NextcSource + 1) > *cSource)) << 3;
			uPix |= static_cast<int>((*NextcSource > *cSource)) << 2;
			uPix |= static_cast<int>((*(NextcSource - 1) > *cSource)) << 1;
			uPix |= static_cast<int>((*(cSource - 1) > *cSource));
			*cPurpose = uPix;
			cPurpose++;
			cSource++;
			LastcSource++;
			NextcSource++;
		}
		cPurpose += 2;
		cSource += 2;
	}
}

// 3X3
void GHLibraryLBP::fnMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	cSource += iRows;

	for (int iCol = 1; iCol < iCols - 1; iCol++)
	{
		const unsigned char* LastcSource = cSource - iRows;
		const unsigned char* NextcSource = cSource + iRows;

		for (int iRow = 1; iRow < iRows - 1; iRow++)
		{
			int iSave = 0;
			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				iSave += *(LastcSource + iIndex) + *(cSource + iIndex) + *(NextcSource + iIndex);
			}
			*cPurpose = iSave / 9;
			cPurpose++;
			cSource++;
			LastcSource++;
			NextcSource++;
		}
		cPurpose += 2;
		cSource += 2;
	}
}

void GHLibraryLBP::fnSEMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	vector<int> vcHistogram = fnGetHistogram(cSource, iRows, iCols);
	vector<int> vcSortHistogram(vcHistogram);

	sort(vcSortHistogram.begin(), vcSortHistogram.end(), greater<int>());

	unsigned char cTable[256] = { 0 };
	for (int iBinIndex = 0; iBinIndex < 63; iBinIndex++)
	{
		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			if (vcHistogram[iIndex] == vcSortHistogram[iBinIndex])
			{
				cTable[iIndex] = iBinIndex;
				g_fwLog << iIndex << "：" << vcSortHistogram[iBinIndex] << " ";
			}
		}
	}
	g_fwLog << endl;
	const int kiSize = iRows * iCols;
	for (int iIndex = 0; iIndex < kiSize; iIndex++)
	{
		*cPurpose = cTable[*cSource];
		cPurpose++;
		cSource++;
	}
}

void GHLibraryLBP::fnLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	const int kiSize = 8;
	const int kiRadius = 1;
	int iOffset = kiSize - 1;

	for (int iIndexSize = 0; iIndexSize < kiSize; iIndexSize++)
	{
		float fX = static_cast<float>(cos(2 * PI * iIndexSize / kiSize));
		float fY = static_cast<float>(sin(2 * PI * iIndexSize / kiSize));
		int iX1 = static_cast<int>(floor(fX)); // 無條件捨去
		int iX2 = static_cast<int>(ceil(fX)); // 無條件進位
		int iY1 = static_cast<int>(floor(fY));
		int iY2 = static_cast<int>(ceil(fY));

		float fXOffset = fX - iX1; // 左邊權重比例
		float fYOffset = fY - iY1; // 上邊權重比例

								   // 利用線性內插特性算權重(比例方式) (y - y1) / (x - x1) = (y2 - y1) / (x2 - x1)
		float fW1 = (1 - fXOffset) * (1 - fYOffset);
		float fW2 = fXOffset * (1 - fYOffset);
		float fW3 = (1 - fXOffset) * fYOffset;
		float fW4 = fXOffset * fYOffset;

		for (int iCol = kiRadius; iCol < iCols - kiRadius; iCol++)
		{
			int iRGBY1 = (iY1 + iCol) * iRows;
			int iRGBY2 = (iY2 + iCol) * iRows;

			for (int iRow = kiRadius; iRow < iRows - kiRadius; iRow++)
			{
				unsigned char cNowSource = *(cSource + iRows * iCol + iRow);
				unsigned char* cNowPurpose = cPurpose + iRows * iCol + iRow;
				unsigned char cPix = 0;
				int iRGBX1 = iX1 + iRow;
				int iRGBX2 = iX2 + iRow;

				cPix = static_cast<unsigned char>(*(cSource + iRGBY1 + iRGBX1) * fW1
					+ *(cSource + iRGBY1 + iRGBX2) * fW2
					+ *(cSource + iRGBY2 + iRGBX1) * fW3
					+ *(cSource + iRGBY2 + iRGBX2) * fW4);
				cPix = (cPix > cNowSource) << iOffset;
				*(cNowPurpose) |= cPix;
			}
		}
		iOffset--;
	}
}

void GHLibraryLBP::fnLBPInvariant(unsigned char* cPurpose, const int iRows, const int iCols)
{
	const int kiSize = 8;
	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 0; iRow < iRows; iRow++)
		{
			unsigned char iNowPix = *cPurpose;
			unsigned char iNowSmall = *cPurpose;
			for (int iIndex = 1; iIndex < kiSize; iIndex++)
			{
				// 逆時鐘轉 例: 10100011 左移1 = 01000110 右移7 = 00000001 最後 = 01000111
				unsigned char iSave = ((iNowPix >> (kiSize - iIndex)) | (iNowPix << iIndex));

				if (iNowSmall > iSave)
				{
					iNowSmall = iSave;
				}
			}
			*cPurpose = iNowSmall;
			cPurpose++;
		}
	}
}

void GHLibraryLBP::fnLBPEquivalence(unsigned char* cPurpose, const int iRows, const int iCols)
{
	unsigned char* uTable = fnGetLBPTable();
	const int kiSize = 8;
	for (int iCol = 0; iCol < iCols; iCol++)
	{
		for (int iRow = 0; iRow < iRows; iRow++)
		{
			*cPurpose = uTable[*cPurpose];
			cPurpose++;
		}
	}
	delete[] uTable;
}

//void GHLibraryLBP::fnLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
//{
//	const int kiSize = 8;
//	const int kiRadius = 1;
//	const int iRBGWidth = iRows * 3;
//
//	for (int iCol = kiRadius; iCol < iCols; iCol++)
//	{
//		for (int iRow = kiRadius; iRow < iRows; iRow++)
//		{
//			char cNowPix = *(cSource + iRBGWidth * iCol + iRow * 3);
//			char cPix = 0;
//			int iOffset = kiSize - 1;
//
//			for (int iIndexSize = 0; iIndexSize < kiSize; iIndexSize++)
//			{
//				float fX = iRow + (float)cos(2 * PI * iIndexSize / kiSize);
//				float fY = iCol + (float)sin(2 * PI * iIndexSize / kiSize);
//				int iX1 = floor(fX); // 無條件捨去
//				int iX2 = ceil(fX); // 無條件進位
//				int iY1 = floor(fY);
//				int iY2 = ceil(fY);
//
//				float fXOffset = fX - (float)iX1; // 左邊權重比例
//				float fYOffset = fY - (float)iY1; // 上邊權重比例
//
//				// 利用線性內插特性(比例方式) (y - y1) / (x - x1) = (y2 - y1) / (x2 - x1)
//				float fW1 = (1 - fXOffset) * (1 - fYOffset);
//				float fW2 = fXOffset * (1 - fYOffset);
//				float fW3 = (1 - fXOffset) * fYOffset;
//				float fW4 = fXOffset * fYOffset;
//
//				char cRadiusPix = 0;
//				iX1 *= 3;
//				iX2 *= 3;
//				iY1 *= iRBGWidth;
//				iY2 *= iRBGWidth;
//				cRadiusPix = *(cSource + iY1 + iX1) * fW1
//					+ *(cSource + iY1 + iX2) * fW2
//					+ *(cSource + iY2 + iX1) * fW3
//					+ *(cSource + iY2 + iX2) * fW4;
//				cPix |= (cRadiusPix > cNowPix) << iOffset;
//				iOffset--;
//			}
//			*cPurpose = cPix;
//			cPurpose++;
//			*cPurpose = cPix;
//			cPurpose++;
//			*cPurpose = cPix;
//			cPurpose++;
//		}
//		cPurpose += kiRadius * 3;
//	}
//}

unsigned char* GHLibraryLBP::fnGetLBPTable()
{
	unsigned char cNewValue = 1;
	unsigned char* cTable = new unsigned char[256]();
	for (int iIndex = 0; iIndex < 256; iIndex++)
	{
		int iCount = 0;
		bitset<8> binaryCode = iIndex;
		for (int iIndex = 0; iIndex < 8; iIndex++)
		{
			if (binaryCode[iIndex] != binaryCode[(iIndex + 1) % 8])
			{
				iCount++;
			}
		}

		if (iCount < 3)
		{
			cTable[iIndex] = cNewValue;
			cNewValue++;
		}
	}
	return cTable;
}

vector<int> GHLibraryLBP::fnGetHistogram(const unsigned char* cData, const int iRows, const int iCols)
{
	vector<int> vcHistogram(256, 0);
	const int kiSize = iRows * iCols;
	for (int iIndex = 0; iIndex < kiSize; iIndex++)
	{
		vcHistogram[*cData]++;
		cData++;
	}
	return vcHistogram;
}