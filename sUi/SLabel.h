/**
* SLabel��
* ��ǩ����
* @author ZeroX
* @version v1.0 21/07/2017
*/

#include "SWidget.h"
#ifndef _SLABEL_H_
#define _SLABEL_H_

class SLabel :public SWidget
{
public:
	SLabel(SWidget *parent=NULL);
	virtual ~SLabel();
public:
	//�����ؼ�
	virtual BOOL Create();

};
#endif