#include "general.h"



extern void MNDT::DrawLine(UCHAE* pur, const int width, Point& p1, Point& p2)
{
	int minX = p1._x < p2._x ? p1._x : p2._x;
	int maxX = p1._x > p2._x ? p1._x : p2._x;

	//y = ax + b
	double a = static_cast<double>((p2._y - p1._y)) / static_cast<double>((p2._x - p1._x));
	double b = static_cast<double>(p2._y) - a * static_cast<double>(p2._x);

	while(minX <= maxX)
	{
		int y = static_cast<int>(a * static_cast<double>(minX) + b);
		*(pur + y * width + minX) = 255;
		minX++;
	}
}

extern double MNDT::PI = 3.1415926535;