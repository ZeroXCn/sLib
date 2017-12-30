/**
*
*	SOutputStream��
*	�����
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#include "SAbstractStream.h"
#ifndef _SOUTPUTSTREAM_H_
#define _SOUTPUTSTREAM_H_

class SOutputStream :public SAbstractStream
{
protected:
	std::ostream	*m_pOutputStream;
public:
	SOutputStream();
	virtual ~SOutputStream();
public:
	//д������
	SOutputStream &Write(byte *buffer, size_t n);
	//ȡ������
	unsigned int Length();

	//���ñ�־
	SOutputStream &Seekp(std::istream::off_type _Off, std::istream::seekdir _Way);
	//��ȡ��־
	std::istream::pos_type Tellp();

	//�Ƿ����
	bool Eof();
	//�����
	void Clear();
	//�ر���
	void Close();
};

#endif