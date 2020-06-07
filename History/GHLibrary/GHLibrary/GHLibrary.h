#pragma once
#ifndef MAT_LIBRARY
#define MAT_LIBRARY
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <bitset>

using namespace std;

class GHLibrary
{
public:
	GHLibrary();
	~GHLibrary();
	void fnBGR2Gray(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnBGR2Gray8b(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnBGR2HSV(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnHSV2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dV);
	void fnThresholdingOTSU(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iScale);
	int fnGetThresholdingScale(const unsigned char* cSource, const int iRows, const int iCols);
	void fnHSV2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnSobel(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dScale);
	void fnExpansion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnErosion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnSub(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnBlur(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnMask(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iMask);
	void fnLSB(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnBGR2YCbCr(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnYCbCr2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnYCbCr2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnHaar(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnSquare(unsigned char* cSource, const vector<vector<int>>* vcPoints, const int iRows, const int iCols);
	void fnContourFrame(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnContourFind(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iMaxRow, const int iMaxCol);
	void fnGamma(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dGamma);
	void fnTailoring(const unsigned char* cSource, unsigned char* cPurpose, const int iORows, const int iOCols, const int iRows, const int iCols);
private:
	const double PI = atan(1) * 4;
	const char* LOG_FILE = "D:\\Log.txt";
	fstream g_fwLog;
};
#endif // MAT_LIBRARY