/**
* ������ͷ�ļ� SWindow.h
* ��Ҫ���𴰿ڵĴ���
* @author ZeroX
* @version v1.0 21/07/2017 
*/
#include "../sCore/SThread.h"

#include "SApplication.h"
#include "SMessageHandler.h"
#include "SWidget.h"

#include "SWindowActivityEvent.h"
#include "SWindowInputEvent.h"

#ifndef _SWINDOWS_H_
#define _SWINDOWS_H_
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <set>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SWindow:
	public SThread,
	public SWidget,
	public SMessageHandler,
	public SWindowActivityEvent,
	public SWindowInputEvent
{
	friend class SApplication;
protected:
	static int s_winnum;					//����һ�����ڼ�¼���������Ĳ���
protected:
	HICON 		m_hIcon;					//����ͼ�꣨��
	HICON 		m_hSmallIcon;				//����ͼ�꣨С��
	HCURSOR		m_hCursor;					//���ͼ��

	BOOL		m_bFullScreen;				//�Ƿ�ȫ����ʾ
	int			m_nColorbit;				//ɫ��ģʽ��32λ��24λ��16λ��

	BOOL		m_bIsRunning;				//ѭ�����

	SWindowInputEvent *m_pInputEvent;		//�����¼�
	SWindowActivityEvent *m_pActivityEvent;	//��¼�
protected:
	void Init();

public:
	//�����չ��캯��
	SWindow(SWidget *parent=NULL);
	
	//�����������������������������н�����չ
	virtual ~SWindow();
public:
	//���ô�������
	void SetAttribute(HINSTANCE hInstance,	//���ó���ʵ�����
		LPTSTR szWindowClass,				//���ô�������
		LPTSTR szTitle,						//���ô��ڱ���
		HICON szIcon,						//����ͼ�꣨��
		HICON szSmallIcon,					//����ͼ�꣨С��
		BOOL bFullScreen = FALSE,			//����ȫ����Ĭ��ΪFALSE
		int nColorbit = 32,					//����ɫ��ģʽ��Ĭ��Ϊ32λɫ
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����

	void SetAttribute(
		LPTSTR szWindowClass,				//���ô�������
		LPTSTR szTitle,						//���ô��ڱ���
		HICON szIcon,						//����ͼ�꣨��
		HICON szSmallIcon,					//����ͼ�꣨С��
		BOOL bFullScreen = FALSE,			//����ȫ����Ĭ��ΪFALSE
		int nColorbit = 32,					//����ɫ��ģʽ��Ĭ��Ϊ32λɫ
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����

	void SetAttribute(
		LPTSTR szWindowClass,				//���ô�������
		LPTSTR szTitle,						//���ô��ڱ���
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����


	void SetAttribute(
		LPTSTR szTitle,					//���ô��ڱ���
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����
public:
	/* ���ô�ͼ�� */
	void SetBigIcon(HICON szIcon);

	/* ����Сͼ�� */
	void SetSmallIcon(HICON szIcon);

	/* �������ָ��*/
	long SetCursorIcon(HICON szIcon);

	/* ����ȫ��ģʽ */
	void SetFullScreen(BOOL bFullScreen);

	/* ����ɫ��ģʽ */
	void SetColorbit(int nColorbit);

	/* ������Ϣ������ */
	void SetWndProc(WNDPROC pWndProc);

	/* �����Ƿ񴴽�*/
	BOOL IsCreated();
public:

	/* ��ʾ��� */
	int ShowCursor(BOOL bShow);

protected:
	//�˳���Ϣѭ��-�൱�ڽ����߳�
	void SetRunning(BOOL bRunning);

	//���ô��ڻ
	void SetWindowInputEvent(SWindowInputEvent *pEvent);

	//���ô��������¼�
	void SetWindowActivityEvent(SWindowActivityEvent *pEvent);

	//ȡ�ô��ڻ
	SWindowInputEvent *GetWindowInputEvent();

	//ȡ�ô��������¼�
	SWindowActivityEvent *GetWindowActivityEvent();
public:
	virtual void DoModal();
	//��ʾ�ؼ�
	virtual void Show();
	virtual void Show(int nCmdShow);

	//���ؿؼ�
	virtual void Hide();

protected:
	//IMPORTMENT:���಻�ܵ������ຯ��,���뽫���·���д�ɽӿ�
	/*//IMPORTMENT:���ǵ������þ�̬��Ϣ�ص�����,���º�������public,����̬���������޷�����*/
	//��Ϣ�ص�����
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//�ؼ����
	virtual void OnRun();

	//�ؼ�ѭ���¼�
	virtual void OnRunning();


public:

	//�����ؼ�
	virtual BOOL Create();

	//���ٿؼ�
	virtual void Destroy();

protected:
	//��ں��߳����
	virtual void Run() final;
	
};
#endif
