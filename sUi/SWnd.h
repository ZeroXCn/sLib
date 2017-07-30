/**
* SWnd��
* HWND��װ��
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SWND_H_
#define _SWND_H_
#include <Windows.h>

class SWnd:public SObject
{
protected:
	HWND m_hWnd;
public:
	SWnd();
	SWnd(HWND hWnd);

	virtual ~SWnd();
public:
	//�滻ָ�������������WNDCLASSEX�ṹ
	DWORD SetClassLong(int nlndex, LONG dwNewLong);

	//�ı�ָ�����ڵı��������ı�����
	BOOL SetWindowText(LPCTSTR lpString);

	//��ָ�����ڵı������ı���������ڣ�������һ���������ڡ�
	int GetWindowText(LPTSTR lpString, int nMaxCount);

	//�ı�ָ�����ڵ�����
	LONG SetWindowLong(int nlndex,LONG dwNewLong);

	//����ָ�����ڵı߿���εĳߴ�
	BOOL GetWindowRect(LPRECT lpRect);

	//��ȡ���ڿͻ����Ĵ�С��ע��һ�£����ڵĿͻ���Ϊ�����г����������˵���֮��ĵط�
	BOOL GetClientRect(LPRECT lpRect);

	//��Ļ���굽�ͻ��������ת��
	BOOL ScreenToClient(LPPOINT lpPoint);

	//���ε��û�����ת������Ļ����
	BOOL ClientToScreen(LPPOINT lpPoint);

	//�ı��Ӵ��ڡ��������ںͶ��㴰�ڵĴ�С��λ�ú�Z�����
	BOOL SetWindowPos(HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

	//�ı�ָ�����ڵ�λ�úʹ�С
	BOOL MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint);

	//������ָ�����ڵ��߳����õ�ǰ̨�����Ҽ���ô���
	BOOL SetForegroundWindow();

	//��ָ���Ĵ������ü��̽���
	HWND SetFocus();

	//�ú�������ָ�����ڵ���ʾ״̬
	BOOL ShowWindow(int nCmdShow);

	//��ָ���Ĵ�������������һ�����Σ�Ȼ�󴰿ڿͻ��������һ���ֽ������»���
	BOOL InvalidateRect(CONST RECT *lpRect,BOOL bErase );

	//����ָ�����ڵĿͻ���
	BOOL UpdateWindow();

	//����fuRedraw�������ã��ػ�ȫ���򲿷ִ��ڡ�
	BOOL RedrawWindow(CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT fuRedraw);

	//���ڵĿͻ������������Ļ����ʾ�豸�����Ļ����ľ��-���ڿͻ���
	HDC GetDC();

	//����hWnd������ָ���Ĵ��ڵ��豸����--��������������
	HDC GetWindowDC();

	//�ͷ��豸�����Ļ�����DC��������Ӧ�ó���ʹ��--��GetDC��GetWindowDC���ʹ��
	int ReleaseDC(HDC hdc);

	/* ���ÿؼ���� */
	void SetWnd(HWND hWnd);

	//��ȡ�ؼ����
	HWND GetWnd();

	//Ϊָ�����ڽ��л�ͼ������׼��
	HDC BeginPaint(LPPAINTSTRUCT lpPaint);

	//���ָ�����ڵĻ滭���̽���
	BOOL EndPaint(CONST PAINTSTRUCT *lpPaint);

	//��ȡ�����ھ����
	HWND GetParent();

	//����/��ָֹ���Ĵ��ڻ�ؼ��������ͼ��̵�����
	BOOL EnableWindow(BOOL bEnable);

};
#endif