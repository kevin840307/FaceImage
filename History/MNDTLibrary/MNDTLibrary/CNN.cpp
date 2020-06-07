#include "CNN.h"

void CNN::Convolution(const UCHAE* src, UCHAE* pur
					, const UINT32 width, const UINT32 height)
{
	CNNFilter cnnFilter;
	cnnFilter.AddFilter(Filter3X3_1);
	cnnFilter.GetFilters();
}