/**
*
*	SStream��
*	�ļ���
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/
#include "../sCore/SObject.h"
#ifndef _SSTREAM_H_
#define _SSTREAM_H_
#include <fstream>
class SAbstractStream :public SObject
{
public:
	static const int npos = -1;
public:
	//�Ƿ����
	virtual bool Eof() = 0;
	//�����
	virtual void Clear() = 0;
	//�ر���
	virtual void Close() = 0 ;




};

#endif