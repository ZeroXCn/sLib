#include "SInputStream.h"

SInputStream &SInputStream::Read(byte *buffer, size_t n)
{
	
	if (buffer)
	{
		m_pInputStream->read((char *)buffer, n);
	}
	return *this;
}

//取得流长度
unsigned int SInputStream::Length()
{
	//将指针移到文件末尾来取得文件长度
	std::streamoff lastcur = 0;
	unsigned int length = 0;
	lastcur = m_pInputStream->tellg();
	m_pInputStream->seekg(std::ios::beg,std::ios::end);                       
	length = (unsigned int)m_pInputStream->tellg();
	m_pInputStream->seekg(std::ios::beg, (std::ios_base::seekdir)lastcur);
	return length;

}

std::streamsize SInputStream::GCount()
{
	return m_pInputStream->gcount();
}

//设置标志
SInputStream &SInputStream::Seekg(std::istream::off_type _Off, std::istream::seekdir _Way)
{
	m_pInputStream->seekg(_Off, _Way);
	return *this;
}
//读取标志
std::istream::pos_type SInputStream::Tellg()
{
	return m_pInputStream->tellg();
}

//是否结束
bool SInputStream::Eof()
{
	return m_pInputStream->eof();
}

void SInputStream::Clear()
{
	m_pInputStream->clear();
}

//关闭流
void SInputStream::Close()
{
	
}