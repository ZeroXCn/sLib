/**
* SWindowActivityEvent�ӿ���
* ������Ϣ
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sGraphic/SDc.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_

#include <Windows.h>
class SWindowActivityEvent
{
public:
	class ActivityParam
	{
	public:
		HWND &hWnd;			//���
		UINT &message;		//��Ϣ
		WPARAM &wParam;		//����1
		LPARAM &lParam;		//����2
	public:
		ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);
	public:
		HWND &GetWnd();
		UINT &GetMessage();
		WPARAM &GetWParam();
		LPARAM &GetLParam();

		void SetWnd(HWND &hWnd);
		void SetMessage(UINT &message);
		void SetWParam(WPARAM &wParam);
		void SetLParam(LPARAM &lParam);

	};
public:

	//������Ϣ�������Ĭ�ϵ�ϵͳ������

	//�ؼ�����֮ǰ
	virtual BOOL OnCreate(ActivityParam &param);

	//���ƻ����¼�
	virtual void OnPaint(SDc dc);

	//���ڿ����¼�
	virtual void OnEvent();

	//�����ӿؼ�
	virtual void OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�رմ���
	virtual BOOL OnClose(ActivityParam &param);

	//���ٴ���
	virtual void OnDestory(ActivityParam &param);

	//ȡ�ô��ڽ���
	virtual void OnGetFocus(ActivityParam &param);

	//ʧȥ����
	virtual void OnLostFocus(ActivityParam &param);
};

#endif