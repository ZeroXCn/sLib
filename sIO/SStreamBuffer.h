/**
*
*	SOutputStream类
*	输出流
*	@author ZeroX
*	@version v1.0 22/12/2017(22/07/2017)
*
*/

#include "SInputStream.h"
#include "SOutputStream.h"
#ifndef _SSTREAMBUFFER_H_
#define _SSTREAMBUFFER_H_
#include <vector>
class SStreamBuffer :public SObject
{
private:
	std::vector<byte>		*m_pBuffer;
public:
	template<class InputIterator>SStreamBuffer(InputIterator begin, InputIterator end);
	SStreamBuffer(size_t size = 1024);
	~SStreamBuffer();
public:
	//存入数据
	SStreamBuffer &Put(byte dat);
	SStreamBuffer &Put(int index, byte dat);
	SStreamBuffer &Put(byte *dat, int length=-1);
	SStreamBuffer &Put(byte *dat, int offset, int length);
	SStreamBuffer &Put(SStreamBuffer &src);

	//返回当前位置
	byte Get();
	byte Get(int index);
	SStreamBuffer Get(int offset, int length);

	//向输入流中读取东西
	void Read(SInputStream	*in,int n = -1);
	//向输出流中写如入东西
	void Write(SOutputStream *out, int n = -1);
public:
	//取得长度
	unsigned int Length();

	//取得占用内存大小(单位-Byte)
	std::streamsize Size();
	//清空
	void Clear();
	//取得数组
	byte *ToArray();
	SString ToString();

};

#endif