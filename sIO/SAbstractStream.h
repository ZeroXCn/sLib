/**
*
*	SStream类
*	文件流
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/
#include "../sCore/SObject.h"
#ifndef _SSTREAM_H_
#define _SSTREAM_H_
#include <fstream>
class SAbstractStream :public SObject
{
public:
	static const int npos = -1;
public:
	//是否结束
	virtual bool Eof() = 0;
	//清空流
	virtual void Clear() = 0;
	//关闭流
	virtual void Close() = 0 ;




};

#endif