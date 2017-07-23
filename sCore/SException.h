/**
*
*	SException类
*	异常处理基类
*	@author ZeroX
*	@version v1.0 22/07/2017(03/02/2017)
*
*/
#include "SObject.h"
#include "SString.h"

#ifndef SEXCEPTION_H
#define SEXCEPTION_H

using namespace std;
class SException:public SObject
{
private:
	int m_nTime;			//异常时间
	SString m_strOri;		//异常来源
	SString m_strDesc;		//记录异常问题描述
protected:

public:
	SException();
	SException(SString m_strDesc);
	SException(SString strOri, const TCHAR* pszFormat, ...);
public:
	int GetTime();
	SString GetDesc();
	SString GetOri();

	virtual void Print();
	virtual void PrintException();

};

#endif