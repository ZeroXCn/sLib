/**
* SButton��
* ��ť�ؼ�
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWidget.h"
#ifndef _SBUTTON_H_
#define _SBUTTON_H_

class SButton :public SWidget
{
public:

	SButton(LPTSTR name = TEXT("button"), SWidget *parent = NULL);
	virtual ~SButton();
protected:
	//ע��һ����-������ǿؼ�����
	virtual BOOL OnPreCreate();

};

#endif