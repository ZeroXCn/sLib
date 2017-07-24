/**
* SWidget��
* ���пؼ��Ļ���
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SWIDGET_H_
#define _SWIDGET_H_

#include <Windows.h>

class SWidget:public SObject
{
protected:
	SWidget *m_pParent;				//����ؼ�

	HWND m_hWnd;					//�ؼ����
	HINSTANCE m_hInstance;			//��ǰ�ؼ�ʵ�����
	HMENU m_hMenu;					//�˵�ʵ�����
	LPVOID m_lpParam;				//���ݸ���Ϣ�����Ĳ���ָ��

	TCHAR m_szClassName[64];		//�ؼ���������
	TCHAR m_szTitle[128];			//�ؼ���������
	DWORD m_dwStyle;				//�����ؼ�������

	int	m_nPosX, m_nPosY;			//�ؼ�λ��
	int	m_nWidth, m_nHeight;		//�ؼ���Ⱥ͸߶�
	BOOL m_bEnabled;				//�ؼ��Ƿ����
	BOOL m_bVisible;				//�Ƿ�ɼ�

	TCHAR m_szTip[64];				//��ʾ
public:
	SWidget(SWidget *parent = NULL);
	virtual ~SWidget();

protected:
	/* ����ʵ����� */
	void SetInstance(HINSTANCE hInstance);

	/* ���ÿؼ���� */
	void SetWnd(HWND hWnd);

	/* ���ò˵����-�����ǿؼ�ID */
	void SetMenu(HMENU hMenu);

	/* ���ò��� */
	void SetParam(LPVOID lpParam);
public:
	//��ȡ�ؼ�ʵ�����
	HINSTANCE GetInstance();

	//��ȡ�ؼ����
	HWND GetWnd();

	//��ȡ�豸������
	HDC GetDC();

	/* ���ò��� */
	LPVOID GetParam();

	/* ���ÿؼ��������� */
	void SetClassName(LPTSTR szClassName);
	LPTSTR(GetClassName)();

	/* ���ÿؼ����� */
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	/* ���ÿؼ���ʽ */
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	
	/* ��ȡ���ÿؼ�λ�� */
	POINT GetPos();
	void SetPos(int x,int y);
	void SetPos(POINT pt);
	void MovePos(int x, int y);
	void MovePos(POINT pt);

	/* ��ȡ���ÿؼ���� */
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);

	/* ��ȡ���ÿؼ����� */
	RECT GetRect();
	void SetRect(RECT rt);

	/* ��ȡ���ÿؼ�����״̬ */
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	/* ��ȡ���ÿؼ��ɼ�״̬ */
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	/* ��ȡ���ÿؼ���ʾ */
	LPTSTR GetTip();
	void SetTip(LPTSTR str);
public:
	//IMPORTMENT:���ڴӸ���̳е�ͬ������,���û��д���ط���,�򲻻�Ӹ���̳����������ط���,Ҫô����д
	//��ʾ�ؼ�
	virtual void Show();
	virtual void Show(int nCmdShow);

	//���ؿؼ�
	virtual void Hide();

	//���¿ؼ�
	void Update();
	void Update(int left, int top, int right, int bottom);

	//�ػ�ؼ�
	void RePaint();

public:
	//�����ؼ�
	virtual BOOL Create() ;

	//���ٿؼ�
	virtual void Destroy() ;

};

#endif