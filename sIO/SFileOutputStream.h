/**
*
*	SFileOutputStream��
*	�ļ������
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#ifndef _SFILEOUTPUTSTREAM_H_
#define _SFILEOUTPUTSTREAM_H_
#include "SOutputStream.h"

class SFileOutputStream :public SOutputStream
{
public:
	SFileOutputStream();
	~SFileOutputStream();
public:
	//���ļ�
	void Open(const char *str, std::ios::open_mode _Mode=std::ios::out);
	bool IsOpen();


	//�ر���
	void Close();
};

#endif