/**
*
*	SLong类
*	long封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SNumber.h"
#ifndef _SLONG_H
#define _SLONG_H


class SLong :public SNumber<long>
{
public:
	static const int MAX_VALUE;
	static const int MIN_VALUE;
	static const int SIZE;
public:
	SLong(long data);
public:
	static SLong ValueOf(long i);
	static SLong ValueOf(SString s);

	static long ParseLong(SString s);								//数值转换

};

#endif