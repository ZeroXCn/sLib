/**
* SControl��
* �ؼ�����
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWidget.h"
#ifndef _SCONTROL_H_
#define _SCONTROL_H_

#define DEFAULT_MENU_VALUE g_nControlId

class SControl :public SWidget
{
protected:
	static unsigned int g_nControlId;			//��¼�ؼ�ID������
protected:
	SControl(SWidget *parent = NULL);
protected:
	//�����ɹ���
	virtual BOOL OnAftCreate(SWnd sWnd);
	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(MessageParam param);
};

#endif