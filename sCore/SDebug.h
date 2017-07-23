/**
*
*	SDebug类
*	用来输出debug信息
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SObject.h"
#include "SString.h"

#ifndef _SDEBUG_H_
#define _SDEBUG_H_

#include <windows.h>

#ifdef SDEBUG
#define sDebug(x) 
#else
#define sDebug(x) SDebug::WriteLine(x)
#endif

class SDebug:public SObject
{
public:
	static void Write(const TCHAR* pszFormat, ...);
	static void Write(SString str);
	static void WriteLine(const TCHAR* pszFormat, ...);
	static void WriteLine(SString str);
};

#endif