/**
* ������ͷ�ļ� SWindow.h
* ��Ҫ���𴰿ڵĴ���
* @author ZeroX
* @version v1.0 21/07/2017 
*/
#include "../sOS/SThread.h"
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
	public SWidget,
	public SWindowActivityEvent,
	public SWindowInputEvent
{
	static int s_winnum;					//����һ�����ڼ�¼���������Ĳ���
protected:

	BOOL		m_bFullScreen;				//�Ƿ�ȫ����ʾ
	int			m_nColorbit;				//ɫ��ģʽ��32λ��24λ��16λ��

	
	SWindowInputEvent *m_pInputEvent;		//�����¼�
	SWindowActivityEvent *m_pActivityEvent;	//��¼�

public:

	//�����չ��캯��
	SWindow(SWidget *parent = NULL,LPTSTR name=TEXT("Window") );
	
	//�����������������������������н�����չ
	virtual ~SWindow();
public:
	//���ô�������
	void SetAttribute(
		LPTSTR szTitle,						//���ô��ڱ���
		HICON szIcon,						//����ͼ�꣨��
		HICON szSmallIcon,					//����ͼ�꣨С��
		BOOL bFullScreen = FALSE,			//����ȫ����Ĭ��ΪFALSE
		int nColorbit = 32,					//����ɫ��ģʽ��Ĭ��Ϊ32λɫ
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����


	void SetAttribute(
		LPTSTR szTitle,					//���ô��ڱ���
		int nWidth = 800,					//���ô��ڿ�ȣ�Ĭ��Ϊ800����
		int nHeight = 600);					//���ô��ڸ߶ȣ�Ĭ��Ϊ600����
public:

	/* ����ȫ��ģʽ */
	void SetFullScreen(BOOL bFullScreen);

	/* ����ɫ��ģʽ */
	void SetColorbit(int nColorbit);

public:
	/* ��ʾ��� */
	int ShowCursor(BOOL bShow=TRUE);
	int HideCursor();

	/* ȡ��������λ�� */
	POINT GetCursorPos();
	void SetCursorPos(POINT pt);

	/* �����ͷ�����ƶ���Χ */
	RECT GetClipCursor();
	void ClipCursor(const RECT *rt);
	void FreeCursor();

	//�ػ���Ϣ
	void RePaint();
protected:

	//���ô��ڻ
	void SetWindowInputEvent(SWindowInputEvent *pEvent);

	//���ô��������¼�
	void SetWindowActivityEvent(SWindowActivityEvent *pEvent);

	//ȡ�ô��ڻ
	SWindowInputEvent *GetWindowInputEvent();

	//ȡ�ô��������¼�
	SWindowActivityEvent *GetWindowActivityEvent();

protected:
	/* ���º���Ϊ�ӿ���д���� */

	//��Ϣ�ص�����
	virtual LRESULT CALLBACK OnProc(MessageParam param);

	//��������֮ǰ
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);
	
	//����������
	virtual BOOL OnCreate(MessageParam param) final;

	//��������֮��
	virtual BOOL OnAftCreate(SWnd sWnd);

	//�߳̿�������ִ�к���
	virtual void OnRunning();

};
#endif
