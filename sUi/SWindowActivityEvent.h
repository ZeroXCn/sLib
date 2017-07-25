/**
* SWindowActivityEvent��
* ������Ϣ
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sGraphic/SDc.h"
#include "SWnd.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_

#include <Windows.h>
class SWindowActivityEvent:public SObject
{
public:

	//������Ϣ�������Ĭ�ϵ�ϵͳ������

	//�ؼ�����֮ǰ
	virtual BOOL OnCreate();

	//���ƻ����¼�
	virtual void OnPaint(SDc dc);

	//���ڿ����¼�
	virtual void OnEvent();

	//�رմ���
	virtual BOOL OnClose(HWND hWnd);

	//���ٴ���
	virtual void OnDestory();

	//ȡ�ô��ڽ���
	virtual void OnGetFocus();

	//ʧȥ����
	virtual void OnLostFocus();
};

#endif