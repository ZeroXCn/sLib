/**
*
*	SInputStream类
*	输入流
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#include "SAbstractStream.h"
#ifndef _SINPUTSTREAM_H_
#define _SINPUTSTREAM_H_

class SInputStream :public SAbstractStream
{
protected:
	std::istream	*m_pInputStream;
public:
	SInputStream();
	virtual ~SInputStream();
public:
	//读取数据
	SInputStream &Read(byte *buffer, size_t n);

	//取得流长度
	unsigned int Length();

	//上一次读取了多少个
	std::streamsize GCount();

	//设置标志
	SInputStream &Seekg(std::istream::off_type _Off, std::istream::seekdir _Way);
	//读取标志
	std::istream::pos_type Tellg();

	//是否结束
	bool Eof();
	//清空流
	void Clear();
	//关闭流
	void Close();
};

#endif