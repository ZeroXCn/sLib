
/**
*
*	SRegex��
*	������ʽ
*	@author ZeroX
*	@version v1.0 0508/2017
*
*/

#include "SObject.h"

#ifndef _SREGEX_H_
#define _SREGEX_H_

#include <regex>
#ifdef _UNICODE
typedef std::wregex tregex;
typedef std::wsmatch tsmatch;
typedef std::wsregex_token_iterator tsregex_token_iterator;
#else
typedef std::regex tregex;
typedef std::smatch tsmatch;
typedef std::sregex_token_iterator tsregex_token_iterator;
#endif

class SRegex :
	public SObject,
	public tregex
{
public:
	/* ԭ���캯��-���Ÿ� */
	//TODO:���๹����Ժ󲹳�
	SRegex(const tstring &str) :tregex(str){}


	//.....
};


#endif