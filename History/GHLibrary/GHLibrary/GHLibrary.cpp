#ifdef GHLIBRARY_EXPORTS //同專案名稱，只是後面固定為_EXPORTS
#define GHLIBRARY_API __declspec(dllexport) //請注意！正確的是Export要亮起
#else
#define GHLIBRARY_API __declspec(dllimport)
#endif

#include "GHLibrary.h"
#include "GHLibraryLBP.h"

extern "C" GHLIBRARY_API void fnBGR2Gray(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnBGR2Gray(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnBGR2Gray8b(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnBGR2Gray8b(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnBGR2HSV(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnBGR2HSV(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnHSV2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dVBase)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnHSV2BGR(cSource, cPurpose, iRows, iCols, dVBase);
}

extern "C" GHLIBRARY_API void fnThresholdingOTSU(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iScale)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnThresholdingOTSU(cSource, cPurpose, iRows, iCols, iScale);
}

extern "C" GHLIBRARY_API int fnGetThresholdingScale(const unsigned char* cSource, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnGetThresholdingScale(cSource, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnHSV2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnHSV2BWFace(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnSobel(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double iScale)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnSobel(cSource, cPurpose, iRows, iCols, iScale);
}

extern "C" GHLIBRARY_API void fnExpansion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnExpansion(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnErosion(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnErosion(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnSub(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnSub(cSource1, cSource2, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnBlur(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnBlur(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnMask(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const int iMask)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnMask(cSource, cPurpose, iRows, iCols, iMask);
}

extern "C" GHLIBRARY_API void fnLSB(const unsigned char* cSource1, const unsigned char* cSource2, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnLSB(cSource1, cSource2, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnBGR2YCbCr(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnBGR2YCbCr(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnYCbCr2BGR(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnYCbCr2BGR(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnYCbCr2BWFace(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnYCbCr2BWFace(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnHaar(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnHaar(cSource, cPurpose, iRows, iCols);
}


extern "C" GHLIBRARY_API void fnContourFrame(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnContourFrame(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnGamma(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols, const double dGamma)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnGamma(cSource, cPurpose, iRows, iCols, dGamma);
}

extern "C" GHLIBRARY_API void fnLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnLBPFeature(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnLBPInvariant(unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnLBPInvariant(cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnLBPEquivalence(unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnLBPEquivalence(cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnMBLBPFeature(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnGeneralLBP(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnGeneralLBP(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnSEMBLBPFeature(const unsigned char* cSource, unsigned char* cPurpose, const int iRows, const int iCols)
{
	GHLibraryLBP ghLibraryLBP;
	return ghLibraryLBP.fnSEMBLBPFeature(cSource, cPurpose, iRows, iCols);
}

extern "C" GHLIBRARY_API void fnTailoring(const unsigned char* cSource, unsigned char* cPurpose, const int iORows, const int iOCols, const int iRows, const int iCols)
{
	GHLibrary ghLibrary;
	return ghLibrary.fnTailoring(cSource, cPurpose, iORows, iOCols, iRows, iCols);
}