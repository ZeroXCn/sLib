/**
* SWindowActivityEvent�ӿ���
* ������Ϣ
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sGraphic/SDc.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_
#include <functional>
#include <Windows.h>
class SWindowActivityEvent
{
public:
	class ActivityParam
	{
	public:
		HWND hWnd;			//���
		UINT uMsg;		//��Ϣ
		WPARAM wParam;		//����1
		LPARAM lParam;		//����2
	public:
		ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

	public:
		WORD GetItemId();
		WORD GetCode();					//ȡ��֪ͨ��
		HWND GetChildHandle();			//�Ӵ��ھ��
		WORD GetClientWidth();			//ȡ�ÿͻ������
		WORD GetClientHeight();			//ȡ�ÿͻ����߶�

	};
private:
	std::function<BOOL(ActivityParam)> m_fCreate;
	std::function<void(SDc)> m_fPaint;
	std::function<void()> m_fEvent;
	std::function<void(ActivityParam)> m_fTimer;
	std::function<void(ActivityParam)> m_fCommand;
	std::function<void(ActivityParam)> m_fSize;
	std::function<BOOL(ActivityParam)> m_fClose;
	std::function<void(ActivityParam)> m_fDestory;
	std::function<void(ActivityParam)> m_fGetFocus;
	std::function<void(ActivityParam)> m_fLostFocus;
public:
	SWindowActivityEvent();
	virtual ~SWindowActivityEvent();
public:
	//������Ϣ�������Ĭ�ϵ�ϵͳ������

	//�ؼ�����֮ʱ
	virtual BOOL OnCreate(ActivityParam param);

	//���ƻ����¼�
	virtual void OnPaint(ActivityParam param);
	virtual void OnPaint(SDc dc);				//�ɸ�ΪHDC

	//���ڿ����¼�
	virtual void OnEvent();

	//��ʱ��
	virtual void OnTimer(ActivityParam param);

	//�����ӿؼ�
	virtual void OnCommand(ActivityParam param);

	//�����ڴ�С�ı�
	virtual void OnSize(ActivityParam param);

	//�رմ���
	virtual BOOL OnClose(ActivityParam param);

	//���ٴ���
	virtual void OnDestory(ActivityParam param);

	//ȡ�ô��ڽ���
	virtual void OnGetFocus(ActivityParam param);

	//ʧȥ����
	virtual void OnLostFocus(ActivityParam param);

public:
	//�ؼ�����֮ʱ
	void OnCreate(std::function<BOOL(ActivityParam)> fCreate);

	//���ƻ����¼�
	void OnPaint(std::function<void(SDc)> fPaint);

	//���ڿ����¼�
	void OnEvent(std::function<void()> fEvent);

	//���ڿ����¼�
	void OnTimer(std::function<void(ActivityParam)> fTimer);

	//�����ӿؼ�
	void OnCommand(std::function<void(ActivityParam)> fCommand);

	//�����ڳߴ緢���仯�¼�
	void OnSize(std::function<void(ActivityParam)> fSize);

	//�رմ���
	void OnClose(std::function<BOOL(ActivityParam)> fClose);

	//���ٴ���
	void OnDestory(std::function<void(ActivityParam)> fDestory);

	//ȡ�ô��ڽ���
	void OnGetFocus(std::function<void(ActivityParam)> fGetFocus);

	//ʧȥ����
	void OnLostFocus(std::function<void(ActivityParam)> fLostFocus);
};

#endif