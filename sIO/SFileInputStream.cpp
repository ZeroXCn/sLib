#include "SFileInputStream.h"

SFileInputStream::SFileInputStream()
{
	m_pInputStream = new std::ifstream();
}
SFileInputStream::~SFileInputStream()
{
	Close();
	delete m_pInputStream;
}

//打开文件
void SFileInputStream::Open(const char *str, std::ios_base::open_mode _Mode)
{
	((std::ifstream*)m_pInputStream)->open(str, _Mode);
}
bool SFileInputStream::IsOpen()
{
	return ((std::ifstream*)m_pInputStream)->is_open();
}

//关闭流
void SFileInputStream::Close()
{
	((std::ifstream*)m_pInputStream)->close();
}