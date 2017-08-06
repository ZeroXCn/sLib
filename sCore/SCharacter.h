/**
*
*	SCharacter类
*	Char封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/

#include "SNumber.h"
#ifndef SCHARACTER_H
#define SCHARACTER_H

class SCharacter :public SNumber<TCHAR>
{
public:
	static const char MAX_VALUE;
	static const char MIN_VALUE;

	static const int SIZE;
public:
	SCharacter(TCHAR ch);
public:
	static SCharacter ValueOf(TCHAR i);
	static SCharacter ValueOf(SString s);

	static SString ToHexString(TCHAR num, bool bIsUpper = false);	//返回16进制

	static TCHAR ParseInt(SString s);								//数值转换
};

#endif