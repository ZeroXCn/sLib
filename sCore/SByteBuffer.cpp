#include "SByteBuffer.h"

SByteBuffer::SByteBuffer()
{

}
SByteBuffer::SByteBuffer(SByteBuffer &src)
{
	*this = src;
}
/////////////
//存入数据
SByteBuffer &SByteBuffer::put(byte dat)
{
	SByteArray::push_back(dat);
	return *this;
}
SByteBuffer &SByteBuffer::put(int index, byte dat)
{
	auto it = SByteArray::begin();
	std::advance(it, index);
	SByteArray::insert(it, dat);
	return *this;
}
SByteBuffer &SByteBuffer::put(byte *dat, int length)
{
	if (length == -1)SByteArray::insert(SByteArray::end(), dat, dat + ::strlen((char*)dat));
	else SByteArray::insert(SByteArray::end(), dat, dat + length);
	return *this;
}

SByteBuffer &SByteBuffer::put(byte *dat, int offset, int length)
{
	auto it = SByteArray::begin();
	std::advance(it, offset);
	SByteArray::insert(it, dat, dat + length);
	return *this;
}
SByteBuffer &SByteBuffer::put(SByteBuffer &src)
{
	SByteArray::insert(SByteArray::end(), src.begin(), src.end());
	return *this;
}

//返回当前位置
byte SByteBuffer::get()
{
	return SByteArray::back();
}
byte SByteBuffer::get(int index)
{
	return SByteArray::at(index);
}
SByteBuffer SByteBuffer::get(int offset, int length)
{
	auto iBegin = SByteArray::begin();
	std::advance(iBegin, offset);
	auto iEnd = iBegin;
	std::advance(iEnd, length);
	SByteBuffer tData(iBegin, iEnd);
	return tData;

}

//取得数组
byte *SByteBuffer::toArray()
{
	return SByteArray::data();

}

SString SByteBuffer::toString()
{
	SString tString;
	for (auto it : *this)
	{
		tString += TCHAR(it);
	}
	return tString;
}

//取得长度
size_t SByteBuffer::length()
{
	return SByteArray::size();
}

//取得大小
size_t SByteBuffer::size()
{
	return length() * sizeof(byte);
}

void SByteBuffer::clear()
{
	return SByteArray::clear();
}


	//取得
byte &SByteBuffer::operator [](int index)
{
	return SByteArray::data()[index];
}