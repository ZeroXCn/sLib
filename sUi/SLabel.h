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
	SLabel(LPTSTR name=TEXT("This is a Label"),SWidget *parent=NULL);
	virtual ~SLabel();
protected:
	//ע��һ����-������ǿؼ�����
	virtual BOOL OnPreCreate();

};
#endif