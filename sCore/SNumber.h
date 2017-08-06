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
	SNumber(_T data)
	{
		m_data = data;
	}

public:
	virtual SString ToString()
	{
		return SString(m_data);
	}

	virtual SString ToHexString()
	{
		return SString::Format(_T("%x"), m_data);
	}

	virtual SString ToBinString()
	{
		return SString::Format(_T("%b"), m_data);
	}

	virtual SString ToDecString()
	{
		return SString::Format(_T("%d"),(int)m_data);
	}

	static SString ToString(_T num)
	{
		return SString(num);
	}

	
public:
	virtual int IntValue(){
		return (int)m_data;
	}
	virtual double DoubleValue(){
		return (double)m_data;
	}
	virtual float FloatValue(){
		return (float)m_data;
	}
	virtual TCHAR CharValue(){
		return (TCHAR)m_data;
	}
	virtual bool BoolValue(){
		return m_data?true:false;
	}

	bool operator >(SNumber num){
		return m_data > num;
	}
	bool operator <(SNumber num){
		return m_data < num;
	}
	bool operator ==(SNumber num){
		return m_data == num;
	}
};

#endif