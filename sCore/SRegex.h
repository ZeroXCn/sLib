
/**
*
*	SRegex类
*	正则表达式
*	@author ZeroX
*	@version v1.0 0508/2017
*
*/

#include "SObject.h"

#ifndef _SREGEX_H_
#define _SREGEX_H_

#include <regex>
#ifdef _UNICODE
typedef wregex tregex;
typedef wsmatch tsmatch;
#else
typedef regex tregex;
typedef smatch tsmatch;
#endif

class SRegex :
	public SObject,
	public tregex
{
public:
	/* 原构造函数-共九个 */
	//TODO:其余构造待以后补充
	SRegex(const tstring &str) :tregex(str){}


	//.....
};


#endif