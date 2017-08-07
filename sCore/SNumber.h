/**
*
*	SNumber抽象类
*	基本类型封装类封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
/* 模板类不支持分离编译 */
/* http://www.cppblog.com/sToa/archive/2009/07/25/91125.html */
#include"SObject.h"
#include "SString.h"

#ifndef _SNUMBER_H_
#define _SNUMBER_H_
#include <limits.h>

template<class _T>
class SNumber :public SObject
{
protected:
	_T m_data;
protected:
	SNumber(_T data);

public:
	virtual SString ToString();

	virtual SString ToHexString();

	virtual SString ToBinString();
	virtual SString ToDecString();

	
public:
	virtual int IntValue();
	virtual double DoubleValue();
	virtual float FloatValue();
	virtual TCHAR CharValue();
	virtual bool BoolValue();
	virtual long LongValue();

	bool operator >(SNumber num);
	bool operator <(SNumber num);
	bool operator ==(SNumber num);
};

#endif