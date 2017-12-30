#include "SStreamBuffer.h"

template<class InputIterator>
SStreamBuffer::SStreamBuffer(InputIterator begin, InputIterator end)
{
	m_pBuffer = new std::vector<byte>(begin, end);
}
SStreamBuffer::SStreamBuffer(size_t size)
{
	m_pBuffer = new std::vector<byte>(size);
}
SStreamBuffer::~SStreamBuffer()
{
	delete m_pBuffer;
}
/////////////
//��������
SStreamBuffer &SStreamBuffer::Put(byte dat)
{
	m_pBuffer->push_back(dat);
	return *this;
}
SStreamBuffer &SStreamBuffer::Put(int index, byte dat)
{
	auto it = m_pBuffer->begin();
	std::advance(it, index);
	m_pBuffer->insert(it, dat);
	return *this;
}
SStreamBuffer &SStreamBuffer::Put(byte *dat, int length)
{
	if (length == -1)m_pBuffer->insert(m_pBuffer->end(), dat, dat + ::strlen((char*)dat));
	else m_pBuffer->insert(m_pBuffer->end(), dat, dat + length);
	
	return *this;
}

SStreamBuffer &SStreamBuffer::Put(byte *dat, int offset, int length)
{
	auto it = m_pBuffer->begin();
	std::advance(it, offset);
	m_pBuffer->insert(it, dat, dat + length);
	return *this;
}
SStreamBuffer &SStreamBuffer::Put(SStreamBuffer &src)
{
	m_pBuffer->insert(m_pBuffer->end(), src.m_pBuffer->begin(), src.m_pBuffer->end());
	return *this;
}

//���ص�ǰλ��
byte SStreamBuffer::Get()
{
	return m_pBuffer->back();
}
byte SStreamBuffer::Get(int index)
{
	return m_pBuffer->at(index);
}
SStreamBuffer SStreamBuffer::Get(int offset, int length)
{
	auto iBegin = m_pBuffer->begin();
	std::advance(iBegin, offset);
	auto iEnd = iBegin;
	std::advance(iEnd, length);
	SStreamBuffer tData(iBegin, iEnd);
	return tData;

}

//���������ж�ȡ����
void SStreamBuffer::Read(SInputStream	*in, int n)
{
	if (in)
	{
		const int bufsize = 1024;
		byte buf[bufsize];
		std::streamsize readCount = -1;
		if (n == -1)
		{
			//�ļ�û����
			while (!in->Eof())
			{
				in->Read(buf, bufsize);
				readCount = in->GCount();
				Put(buf, (int)readCount);
			}
		}
		else
		{
			int newbufsize = bufsize;
			for (size_t i = 0; i * bufsize < (size_t)n; i++)
			{
				if ((i + 1)*bufsize <= (size_t)n)newbufsize = bufsize;
				else newbufsize = n - i * bufsize;

				in->Read(buf, newbufsize);
				readCount = in->GCount();
				Put(buf, (int)readCount);

				if (in->Eof())
					break;

			}

		}
	}
}
//���������д���붫��
void SStreamBuffer::Write(SOutputStream *out, int n)
{
	if (out)
	{
		if (n == -1)
			out->Write(ToArray(), Length());
		else
			out->Write(ToArray(), n);
	}

}

////
//ȡ������
byte *SStreamBuffer::ToArray()
{
	return m_pBuffer->data();

}

SString SStreamBuffer::ToString()
{
	SString tString;
	for (auto it : *m_pBuffer)
	{
		tString += TCHAR(it);
	}
	return tString;
}

//ȡ�ó���
unsigned int SStreamBuffer::Length()
{
	return m_pBuffer->size();
}

//ȡ�ô�С
std::streamsize SStreamBuffer::Size()
{
	return Length() * sizeof(byte);
}

void SStreamBuffer::Clear()
{
	return m_pBuffer->clear();
}

