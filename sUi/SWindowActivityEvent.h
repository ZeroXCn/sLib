/**
* SWindowActivityEvent��
* ������Ϣ
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sGraphic/SGraphics.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_

#include <Windows.h>
class SWindowActivityEvent:public SObject
{
protected:
	SGraphics *m_Graphics;
public:
	SWindowActivityEvent();
	virtual ~SWindowActivityEvent();
public:
	SGraphics *GetGraphics();
	void SetGraphics(SGraphics *g);
public:

	//������Ϣ�������Ĭ�ϵ�ϵͳ������

	//�ؼ�����֮ǰ
	virtual BOOL OnCreate();

	//���ƻ����¼�
	virtual void OnPaint(SGraphics *g);

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