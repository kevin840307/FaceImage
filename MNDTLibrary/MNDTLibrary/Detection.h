#pragma once
#ifndef DETECTION_H
#define DETECTION_H
#include "general.h"
#include "Segment.h"
#include "LBP.h"
#include "AdaBoost.h"
#include "Image.h"

namespace MNDT {
	namespace Detection {
		extern  void PredictFeature(C_UCHAR* src
			, C_UINT32 width, C_UINT32 height
			, std::map<UINT32, Region>& R);
	}
}

#endif // !DETECTION_H