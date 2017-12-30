/**
*
*	SInputStream��
*	������
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#include "SAbstractStream.h"
#ifndef _SINPUTSTREAM_H_
#define _SINPUTSTREAM_H_

class SInputStream :public SAbstractStream
{
protected:
	std::istream	*m_pInputStream;
public:
	SInputStream();
	virtual ~SInputStream();
public:
	//��ȡ����
	SInputStream &Read(byte *buffer, size_t n);

	//ȡ��������
	unsigned int Length();

	//��һ�ζ�ȡ�˶��ٸ�
	std::streamsize GCount();

	//���ñ�־
	SInputStream &Seekg(std::istream::off_type _Off, std::istream::seekdir _Way);
	//��ȡ��־
	std::istream::pos_type Tellg();

	//�Ƿ����
	bool Eof();
	//�����
	void Clear();
	//�ر���
	void Close();
};

#endif