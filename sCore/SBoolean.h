/**
*
*	SBoolean类
*	Boolean封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SNumber.h"
#ifndef _SBOOLEAN_H_
#define _SBOOLEAN_H_

class SBoolean :public SNumber<bool>
{
public:
	SBoolean(bool bl);
public:
	static SBoolean ValueOf(bool i);
	static SBoolean ValueOf(SString s);

	static SString ToHexString(bool i, bool bIsUpper = false);	//返回16进制

	static bool ParseBoolean(SString s);								//数值转换
};

#endif