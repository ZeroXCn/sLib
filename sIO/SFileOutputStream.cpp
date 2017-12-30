#include "SFileOutputStream.h"

SFileOutputStream::SFileOutputStream()
{
	m_pOutputStream = new std::ofstream();
}
SFileOutputStream::~SFileOutputStream()
{
	Close();
	delete m_pOutputStream;
}

//���ļ�
void SFileOutputStream::Open(const char *str, std::ios_base::open_mode _Mode)
{
	((std::ofstream *)m_pOutputStream)->open(str, _Mode);
}
bool SFileOutputStream::IsOpen()
{
	return ((std::ofstream *)m_pOutputStream)->is_open();
}


//�ر���
void SFileOutputStream::Close()
{
	((std::ofstream *)m_pOutputStream)->close();
}