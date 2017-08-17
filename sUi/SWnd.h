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
	/* ���ÿؼ���� */
	void SetHandle(HWND hWnd);

	//��ȡ�ؼ����
	HWND GetHandle();
public:
	//�滻,��ȡָ�������������WNDCLASSEX�ṹ
	DWORD SetClassLong(int nlndex, LONG dwNewLong);
	DWORD GetClassLong(int nlndex);

	//�ı�ָ�����ڵı��������ı�����
	BOOL SetWindowText(LPCTSTR lpString);

	//��ָ�����ڵı������ı���������ڣ�������һ���������ڡ�
	int GetWindowText(LPTSTR lpString, int nMaxCount);

	//�ı�ָ�����ڵ�����-���ڸı�ص�����-���ؾɵĻص�����
	LONG SetWindowLong(int nIndex,LONG dwNewLong);
	LONG GetWindowLong(int nIndex);


	//����ָ�����ڵı߿���εĳߴ�
	BOOL GetWindowRect(LPRECT lpRect);
	RECT GetWindowRect();

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

	//Ϊָ�����ڽ��л�ͼ������׼��
	HDC BeginPaint(LPPAINTSTRUCT lpPaint);

	//���ָ�����ڵĻ滭���̽���
	BOOL EndPaint(CONST PAINTSTRUCT *lpPaint);

	//���ø����ھ����
	HWND SetParent(HWND parent);

	//��ȡ�����ھ����
	HWND GetParent();

	//�����ӿؼ�
	HWND GetDlgItem(int nIDDDlgItem);

	//��uValue��ֵ��Ϊ�Ի���ؼ����ı�
	BOOL SetDlgItemInt(int nIDDDlgItem, UINT uValue, BOOL bSigned);
	BOOL SetDlgItemText(int nIDDDlgItem, LPCTSTR IpString);

	//��ȡָ�����ڵ����洰�ڵľ����
	HWND GetAncestor(UINT gaFlags);

	//����/��ָֹ���Ĵ��ڻ�ؼ��������ͼ��̵�����
	BOOL EnableWindow(BOOL bEnable);

	//������Ϣ
	LRESULT SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam);

	//Ͷ����Ϣ
	BOOL PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

	//ö��һ�������ڵ������Ӵ��ڡ�
	BOOL EnumChildWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);

	//�����Ƿ�����
	BOOL IsWindowVisible();

	//�����²˵�
	BOOL SetMenu(HMENU hMenu);

	//ȡ�ò˵�
	HMENU GetMenu();

};
#endif