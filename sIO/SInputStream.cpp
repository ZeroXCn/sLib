#include "SInputStream.h"

SInputStream &SInputStream::Read(byte *buffer, size_t n)
{
	
	if (buffer)
	{
		m_pInputStream->read((char *)buffer, n);
	}
	return *this;
}

//ȡ��������
unsigned int SInputStream::Length()
{
	//��ָ���Ƶ��ļ�ĩβ��ȡ���ļ�����
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

//���ñ�־
SInputStream &SInputStream::Seekg(std::istream::off_type _Off, std::istream::seekdir _Way)
{
	m_pInputStream->seekg(_Off, _Way);
	return *this;
}
//��ȡ��־
std::istream::pos_type SInputStream::Tellg()
{
	return m_pInputStream->tellg();
}

//�Ƿ����
bool SInputStream::Eof()
{
	return m_pInputStream->eof();
}

void SInputStream::Clear()
{
	m_pInputStream->clear();
}

//�ر���
void SInputStream::Close()
{
	
}