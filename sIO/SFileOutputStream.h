/**
*
*	SFileOutputStream类
*	文件输出流
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#ifndef _SFILEOUTPUTSTREAM_H_
#define _SFILEOUTPUTSTREAM_H_
#include "SOutputStream.h"

class SFileOutputStream :public SOutputStream
{
public:
	SFileOutputStream();
	~SFileOutputStream();
public:
	//打开文件
	void Open(const char *str, std::ios::open_mode _Mode=std::ios::out);
	bool IsOpen();


	//关闭流
	void Close();
};

#endif