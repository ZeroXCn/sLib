/**
* SLabel��
* ��ǩ����
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SString.h"
#include "../sGraphic/SFont.h"
#include "SControl.h"
#ifndef _SLABEL_H_
#define _SLABEL_H_

class SLabel :public SControl
{
public:
	SLabel(SWidget *parent = NULL, LPTSTR name = TEXT("This is a Label"));
	virtual ~SLabel();
public:
	//����ȡ�ð�ť�ı�
	void SetText(SString str);
	SString GetText();

	//�������ı���С
	void AdjustText();

};
#endif