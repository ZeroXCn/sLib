/**
*
*	SByteArray类
*	byte数据的处理
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SObject.h"
#ifndef _SBYTEBUFFER_H_
#define _SBYTEBUFFER_H_
#include <vector>


//TODO:待补充
typedef std::vector<byte> SByteArray;
class SByteBuffer :
	public SObject,
	private SByteArray
{
public:
	template<class InputIterator>SByteBuffer(InputIterator begin, InputIterator end) :SByteArray(begin, end){};
	SByteBuffer();
	SByteBuffer(SByteBuffer &src);

public:
	//存入数据
	SByteBuffer &put(byte dat);
	SByteBuffer &put(int index, byte dat);
	SByteBuffer &put(byte *dat,int length=-1);
	SByteBuffer &put(byte *dat,int offset,int length);
	SByteBuffer &put(SByteBuffer &src);

	//返回当前位置
	byte get();
	byte get(int index);
	SByteBuffer get(int offset, int length);

	//取得长度
	size_t length();

	//取得占用内存大小(单位-Byte)
	size_t size();

	//清空
	void clear();
	//取得数组
	byte *toArray();
	SString toString();
public:
	//取得
	byte &operator [](int index);
};

#endif