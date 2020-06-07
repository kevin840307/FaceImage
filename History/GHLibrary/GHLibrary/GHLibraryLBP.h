#pragma once
#ifndef MAT_LIBRARYLBP
#define MAT_LIBRARYLBP
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <bitset>

using namespace std;

class GHLibraryLBP
{
public:
	GHLibraryLBP();
	~GHLibraryLBP();
	void fnGeneralLBP(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols); // Multiscale Block LBP
	void fnSEMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols); // Statistically Effective MB-LBP
	void fnLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols);
	void fnLBPInvariant(unsigned char* cPurpose, const int iRows, const int iCols);
	void fnLBPEquivalence(unsigned char* cPurpose, const int iRows, const int iCols);
private:
	unsigned char* fnGetLBPTable();
	vector<int> fnGetHistogram(const unsigned char* cData, const int iRows, const int iCols);
	const double PI = atan(1) * 4;
	const char* LOG_FILE = "D:\\Log.txt";
	fstream g_fwLog;
};
#endif // MAT_LIBRARYLBP