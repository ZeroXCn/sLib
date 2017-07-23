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

#ifndef _SWINDOWS_H_
#define _SWINDOWS_H_
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <set>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SWindow:
	public SThread,
	public SWidget,
	public SMessageHandler
	
{
	friend class SApplication;
protected:
	static int s_winnum;						//����һ�����ڼ�¼���������Ĳ���
protected:

	WORD		m_wIcon;					//����ͼ�꣨��
	WORD		m_wSmallIcon;				//����ͼ�꣨С��

	BOOL		m_bFullScreen;				//�Ƿ�ȫ����ʾ
	int			m_nColorbit;				//ɫ��ģʽ��32λ��24λ��16λ��

	BOOL		m_bIsRunning;				//ѭ�����
protected:
	void Init();

public:
	//�����չ��캯��
	SWindow(SWidget *parent=NULL);

	//��򵥹���
	SWindow(LPTSTR szTitle);
	
	//�����������������������������н�����չ
	virtual ~SWindow();
public:
	//���ô�������
	void SetAttribute(HINSTANCE hInstance,				//���ó���ʵ�����
		LPTSTR szWindowClass,			//���ô�������
		LPTSTR szTitle,					//���ô��ڱ���
		WORD wIcon,						//����ͼ�꣨��
		WORD wSmallIcon,				//����ͼ�꣨С��
		BOOL bFullScreen = FALSE,			//����ȫ����Ĭ��ΪFALSE
		int nColorbit = 32,					//����ɫ��ģʽ��Ĭ��Ϊ32λɫ
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����

	void SetAttribute(
		LPTSTR szWindowClass,			//���ô�������
		LPTSTR szTitle,					//���ô��ڱ���
		WORD wIcon,					//����ͼ�꣨��
		WORD wSmallIcon,				//����ͼ�꣨С��
		BOOL bFullScreen = FALSE,			//����ȫ����Ĭ��ΪFALSE
		int nColorbit = 32,					//����ɫ��ģʽ��Ĭ��Ϊ32λɫ
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����

	void SetAttribute(
		LPTSTR szWindowClass,			//���ô�������
		LPTSTR szTitle,					//���ô��ڱ���
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����


	void SetAttribute(
		LPTSTR szTitle,					//���ô��ڱ���
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����
public:
	/* ���ô�ͼ�� */
	void SetBigIcon(WORD wIcon);

	/* ����Сͼ�� */
	void SetSmallIcon(WORD wIcon);

	/* �������ָ��*/
	long SetCursorIcon(WORD wIcon);

	/* ����ȫ��ģʽ */
	void SetFullScreen(BOOL bFullScreen);

	/* ����ɫ��ģʽ */
	void SetColorbit(int nColorbit);

	/* ������Ϣ������ */
	void SetWndProc(WNDPROC pWndProc);

protected:
	//�˳���Ϣѭ��-�൱�ڽ����߳�
	void SetRunning(BOOL bRunning);
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

	//�ؼ�����֮ǰ
	virtual BOOL OnCreate();

	//�ؼ�����֮��
	virtual BOOL OnCreated();

	//�ؼ����
	virtual void OnRun();

	//�ؼ�ѭ���¼�
	virtual void OnEvent();

	//���ƻ����¼�
	virtual void OnPaint();

	//�رմ���
	virtual BOOL OnClose();

	//���ٴ���
	virtual void OnDestory();

	//ȡ�ô��ڽ���
	virtual void OnGetFocus();

	//ʧȥ����
	virtual void OnLostFocus();
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
