/**
*
*	SDouble��
*	double��װ��
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/

#include "SNumber.h"
#ifndef _SDOUBLE_H_
#define _SDOUBLE_H_

class SDouble :public SNumber<double>
{
public:
	static const double MAX_VALUE;
	static const double MIN_VALUE;

	static const int MAX_EXP_VALUE;
	static const int MIN_EXP_VALUE;

	static const int SIZE;
public:
	SDouble(double num);
public:
	static SDouble ValueOf(double i);
	static SDouble ValueOf(SString s);

	static SString ToHexString(double i, bool bIsUpper = false);	//����16����

	static double ParseDouble(SString s);								//��ֵת��
};

#endif