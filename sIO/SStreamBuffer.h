/**
*
*	SOutputStream��
*	�����
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
	//��������
	SStreamBuffer &Put(byte dat);
	SStreamBuffer &Put(int index, byte dat);
	SStreamBuffer &Put(byte *dat, int length=-1);
	SStreamBuffer &Put(byte *dat, int offset, int length);
	SStreamBuffer &Put(SStreamBuffer &src);

	//���ص�ǰλ��
	byte Get();
	byte Get(int index);
	SStreamBuffer Get(int offset, int length);

	//���������ж�ȡ����
	void Read(SInputStream	*in,int n = -1);
	//���������д���붫��
	void Write(SOutputStream *out, int n = -1);
public:
	//ȡ�ó���
	unsigned int Length();

	//ȡ��ռ���ڴ��С(��λ-Byte)
	std::streamsize Size();
	//���
	void Clear();
	//ȡ������
	byte *ToArray();
	SString ToString();

};

#endif