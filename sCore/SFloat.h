/**
*
*	SFloat类
*	float封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/

#include "SNumber.h"
#ifndef _SFLOAT_H_
#define _SFLOAT_H_

class SFloat:public SNumber<float>
{
public:
	static const float MAX_VALUE;
	static const float MIN_VALUE;

	static const int MAX_EXP_VALUE;
	static const int MIN_EXP_VALUE;


	static const int SIZE;
public:
	SFloat(float number);
public:
	static SFloat ValueOf(float i);
	static SFloat ValueOf(SString s);

	static SString ToHexString(float i, bool bIsUpper = false);	//返回16进制

	static float ParseFloat(SString s);								//数值转换

};

#endif