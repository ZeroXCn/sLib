#include "SOutputStream.h"

SOutputStream &SOutputStream::Write(byte *buffer, size_t n )
{
	if (buffer)
	{
		m_pOutputStream->write((char *)buffer, n);
	}

	return *this;
}

unsigned int SOutputStream::Length()
{
	//将指针移到文件末尾来取得文件长度
	std::streamoff lastcur = 0;
	unsigned int length = 0;
	lastcur = m_pOutputStream->tellp();
	m_pOutputStream->seekp(std::ios::beg, std::ios::end);
	length = (unsigned int)m_pOutputStream->tellp();
	m_pOutputStream->seekp(std::ios::beg, (std::ios_base::seekdir)lastcur);
	return length;
}

//设置标志
SOutputStream &SOutputStream::Seekp(std::istream::off_type _Off, std::istream::seekdir _Way)
{
	m_pOutputStream->seekp(_Off, _Way);
	return *this;
}
//读取标志
std::istream::pos_type SOutputStream::Tellp()
{
	return m_pOutputStream->tellp();
}

//是否结束
bool SOutputStream::Eof()
{
	return m_pOutputStream->eof();
}

void SOutputStream::Clear()
{
	m_pOutputStream->clear();
}

//关闭流
void SOutputStream::Close()
{
	
}