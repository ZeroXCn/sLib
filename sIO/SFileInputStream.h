/**
*
*	SFileInputStream��
*	�ļ������
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#ifndef _SFILEINPUTSTREAM_H_
#define _SFILEINPUTSTREAM_H_
#include "SInputStream.h"

class SFileInputStream:public SInputStream
{
public:
	SFileInputStream();
	~SFileInputStream();
public:
	//���ļ�
	void Open(const char *str, std::ios::open_mode _Mode = std::ios::in);
	bool IsOpen();

	//�ر���
	void Close();
};
#endif