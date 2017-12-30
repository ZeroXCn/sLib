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
	//��ָ���Ƶ��ļ�ĩβ��ȡ���ļ�����
	std::streamoff lastcur = 0;
	unsigned int length = 0;
	lastcur = m_pOutputStream->tellp();
	m_pOutputStream->seekp(std::ios::beg, std::ios::end);
	length = (unsigned int)m_pOutputStream->tellp();
	m_pOutputStream->seekp(std::ios::beg, (std::ios_base::seekdir)lastcur);
	return length;
}

//���ñ�־
SOutputStream &SOutputStream::Seekp(std::istream::off_type _Off, std::istream::seekdir _Way)
{
	m_pOutputStream->seekp(_Off, _Way);
	return *this;
}
//��ȡ��־
std::istream::pos_type SOutputStream::Tellp()
{
	return m_pOutputStream->tellp();
}

//�Ƿ����
bool SOutputStream::Eof()
{
	return m_pOutputStream->eof();
}

void SOutputStream::Clear()
{
	m_pOutputStream->clear();
}

//�ر���
void SOutputStream::Close()
{
	
}