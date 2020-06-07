#include "MNDTLibrary.h"
#include <stdarg.h>

MNDTLibrary::MNDTLibrary()
{
	LOG_FILE = "D:\\Log.txt";
	_fwLog.open(LOG_FILE, std::ios::app);
}

MNDTLibrary::~MNDTLibrary()
{
	_fwLog.close();
}

void MNDTLibrary::ChangeColor(const UCHAE* src, UCHAE* pur
							, const UINT32 width, const UINT32 height
							, const UINT32 type)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	switch (type)
	{
	case BGR2GRAY_8BIT:
		BGR2Gray8Bit(src, pur, width, height);
		break;
	}
}

// 灰階
// R 0.299 ≈ 19595
// G 0.587 ≈ 38469
// B 0.114 ≈ 7472 (進位 反推回去比7471接近)
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void MNDTLibrary::BGR2Gray8Bit(const UCHAE* src, UCHAE* pur
							, const UINT32 width, const UINT32 height)
{
	const int maxLen = width * height;

	for (int index = 0; index < maxLen; index++)
	{
		int B = *src;
		src++;

		int G = *src;
		src++;

		int R = *src;
		src++;

		int pix = (R * 19595 + G * 38469 + B * 7472) >> 16;
		*pur = pix;
		pur++;

	}
}