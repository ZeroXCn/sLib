/**
*
*	SInteger类
*	Int封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SNumber.h"
#ifndef SINTEGER_H
#define SINTEGER_H


class SInteger :public SNumber<int>
{
public:
	static const int MAX_VALUE;
	static const int MIN_VALUE;
	static const int SIZE;
public:
	SInteger(int data);
public:
	static SInteger ValueOf(int i);
	static SInteger ValueOf(SString s);							
			
	static int ParseInt(SString s);								//数值转换
public:
	SString ToHexString();

};

#endif