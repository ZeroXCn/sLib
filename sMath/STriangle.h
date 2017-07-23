#ifndef STRIANGLE_H
#define STRIANGLE_H
#include "SRect.h"
#include <math.h>
class STriangle
{
public:
	float x1, y1;
	float x2, y2;
	float x3, y3;

	SRect GetScopeRect(){
		float left = (x1 < x2 ? x1 : x2)<x3 ? (x1 < x2 ? x1 : x2) : x3;
		float top = (y1 < y2 ? y1 : y2)<y3 ? (y1 < y2 ? y1 : y2) : y3;
		float right = (x1 > x2 ? x1 : x2)>x3 ? (x1 > x2 ? x1 : x2) : x3;
		float bottom = (y1 > y2 ? y1 : y2)>y3 ? (y1 > y2 ? y1 : y2) : y3;
		return SRect(left, top, right, bottom);
	}

	STriangle(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		this->x1 = x1; this->y1 = y1;
		this->x2 = x2; this->y2 = y2;
		this->x3 = x3; this->y3 = y3;
	}

	float GetArea(){
		if (isTriangle()){
			float p = (float)((GetSideA() + GetSideB() + GetSideC()) / 2.0);
			float area =(float) (sqrt(p*(p - GetSideA())*(p - GetSideB())*(p - GetSideC())));
			return area;
		}
		return 0;
	}

	float GetSideA(){
		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}
	float GetSideB(){
		return sqrt((x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3));
	}
	float GetSideC(){
		return sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));
	}

	bool isTriangle(){
		if (GetSideA()<GetSideB() + GetSideC() && GetSideB()<GetSideA() + GetSideC() && GetSideC()<GetSideA() + GetSideB())
			return true;
		else return false;
	}

};
#endif

