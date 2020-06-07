#ifdef MNDTLIBRARY_EXPORTS //�P�M�צW�١A�u�O�᭱�T�w��_EXPORTS
#define MNDTLIBRARY_API __declspec(dllexport) //�Ъ`�N�I���T���OExport�n�G�_
#include "MNDTLibrary.h"
#include "CNN.h"
#include "HOG.h"

extern "C" MNDTLIBRARY_API void mndtChangeColor(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height
	, const UINT32 type)
{
	MNDTLibrary lib;
	lib.ChangeColor(src, pur, width, height, type);
}

extern "C" MNDTLIBRARY_API void mndtConvolution(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height)
{
	CNN cnn;
	cnn.Convolution(src, pur, width, height);
}

extern "C" MNDTLIBRARY_API void mndtGamma(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height
	, const double gamma)
{
	HOG hog;
	hog.Gamma(src, pur, width, height, gamma);
}

extern "C" MNDTLIBRARY_API void mndtGradient(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height)
{
	HOG hog;
	hog.Gradient(src, pur, width, height);
}

extern "C" MNDTLIBRARY_API void mndtGetHOGVector(const UCHAE* src, UCHAE* pur
	, const UINT32 width, const UINT32 height
	, const UINT32 cellSplitW, const UINT32 cellSplitH
	, const UINT32 blockSplitW, const UINT32 blockSplitH
	, const double drawBase)
{
	HOG hog;

	hog.GetHOGVector(src, pur, width, height, cellSplitW, cellSplitH, blockSplitW, blockSplitH, drawBase);
}

#else
#define MNDTLIBRARY_API __declspec(dllimport)
#endif