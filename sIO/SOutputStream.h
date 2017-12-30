/**
*
*	SOutputStream类
*	输出流
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#include "SAbstractStream.h"
#ifndef _SOUTPUTSTREAM_H_
#define _SOUTPUTSTREAM_H_

class SOutputStream :public SAbstractStream
{
protected:
	std::ostream	*m_pOutputStream;
public:
	SOutputStream();
	virtual ~SOutputStream();
public:
	//写入数据
	SOutputStream &Write(byte *buffer, size_t n);
	//取流长度
	unsigned int Length();

	//设置标志
	SOutputStream &Seekp(std::istream::off_type _Off, std::istream::seekdir _Way);
	//读取标志
	std::istream::pos_type Tellp();

	//是否结束
	bool Eof();
	//清空流
	void Clear();
	//关闭流
	void Close();
};

#endif