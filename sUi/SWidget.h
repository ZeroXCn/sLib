/**
* SWidget��
* ���в����Ļ���
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SThread.h"
#include "../sGraphic/SDc.h"
#include "SWnd.h"
#include "SApplication.h"
#include "SMessageHandler.h"
#ifndef _SWIDGET_H_
#define _SWIDGET_H_

#include <Windows.h>

//���ڴ���win�����Ա�
typedef struct tagWINATTRIBUTE
{
	LPCTSTR lpClassName;
	LPCTSTR lpWindowName;
	DWORD dwStyle;
	int x;
	int y;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HANDLE hlnstance;
	LPVOID lpParam;
}WINATTRIBUTE;



class SWidget:
	public SObject,
	public SRunnable,
	public SMessageHandler
{
	friend class SApplication;
protected:
	SWidget *m_pParent;				//����ؼ�
	
	SWnd m_Wnd;						//�ؼ����

	BOOL m_bEnabled;				//�ؼ��Ƿ����
	BOOL m_bVisible;				//�Ƿ�ɼ�

	TCHAR m_szTip[64];				//��ʾ

	BOOL m_bIsRunning;				//ѭ�����

	SThread *m_pThread;				//�߳�
	/* TODO:����������������� */
	HINSTANCE m_hInstance;			//��ǰ�ؼ�ʵ�����
	HMENU m_hMenu;					//�˵�ʵ��������߼�¼�ؼ�ID
	LPVOID m_lpParam;				//���ݸ���Ϣ�����Ĳ���ָ��

	TCHAR m_szClassName[64];		//�ؼ���������
	TCHAR m_szTitle[128];			//�ؼ���������
	DWORD m_dwStyle;				//�����ؼ�������

	int	m_nPosX, m_nPosY;			//�ؼ�λ��
	int	m_nWidth, m_nHeight;		//�ؼ���Ⱥ͸߶�


public:
	SWidget(SWidget *parent = NULL);
	virtual ~SWidget();

public:
	/* �ؼ�ͨ�ò��� */
	//��ȡ���ÿؼ�����
	SWidget *GetParent();
	void SetParent(SWidget *parent);

	//��ȡ���ÿؼ�ʵ�����
	HINSTANCE GetInstance();
	void SetInstance(HINSTANCE hInstance);

	//��ȡ���ÿؼ����
	SWnd GetWnd();
	void SetWnd(SWnd pWnd);


	// ���ò˵����-�����ǿؼ�ID 
	void SetMenu(HMENU hMenu);
	HMENU GetMenu();

	// ���ò��� 
	void SetParam(LPVOID lpParam);
	LPVOID GetParam();

	//��ȡ�豸������
	SDc GetDC();

	//���û�ȡ�ؼ���������
	void SetClassName(LPTSTR szClassName);
	LPTSTR GetClassName();

	// ���ÿؼ����� 
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	// ���ÿؼ���ʽ 
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	
	// ��ȡ���ÿؼ�λ�� 
	POINT GetPos();
	void SetPos(int x,int y);
	void SetPos(POINT pt);
	void MovePos(int x, int y);
	void MovePos(POINT pt);

	// ��ȡ���ÿؼ���� 
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);

	// ��ȡ���ÿؼ����� 
	RECT GetRect();
	void SetRect(RECT rt);

	// ��ȡ���ÿؼ�����״̬ 
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	// ��ȡ���ÿؼ��ɼ�״̬ 
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	// ��ȡ���ÿؼ���ʾ 
	LPTSTR GetTip();
	void SetTip(LPTSTR str);

	//ȡ�������ı�����
	void SetFont(HFONT font);
	HFONT GetFont();
public:
	/* �����Ƿ񴴽�*/
	BOOL IsCreated();


protected: 
	//�˳���Ϣѭ��-�൱�ڽ����߳�
		void SetRunning(BOOL bRunning);
public:
	// �ö�����
	BOOL SetForegroundWindow();

	// ȡ�ý���
	HWND SetFocus();
public:
	//IMPORTMENT:���ڴӸ���̳е�ͬ������,���û��д���ط���,�򲻻�Ӹ���̳����������ط���,Ҫô����д
	//��ʾ�ؼ�
	virtual void ShowWindow();
	virtual void ShowWindow(int nCmdShow);

	//���ؿؼ�
	virtual void HideWindow();

	//���¿ؼ�
	void UpdateWindow();
	void UpdateWindow(int left, int top, int right, int bottom);

	//�ػ�ؼ�
	void ReDrawWindow();
protected:
	//IMPORTMENT:���಻�ܵ������ຯ��,���뽫���·���д�ɽӿ�
	/*//IMPORTMENT:���ǵ������þ�̬��Ϣ�ص�����,���º�������public,����̬���������޷�����*/
	//��Ϣ�ص�����
	virtual LRESULT CALLBACK OnProc(MessageParam param);

	//��������֮ǰ-������ǿؼ�����
	virtual BOOL OnPreCreate();

	//��������֮��
	virtual BOOL OnAftCreate(SWnd sWnd);

	//�߳���ѭ������
	virtual void OnRun();

	//�ؼ�ѭ���¼�
	virtual void OnRunning();

	//�ؼ��˳��¼�
	virtual void OnRan();
public:
	//��ں��߳����
	virtual void Run() final;

	//ע��ؼ���-WNDCLASSEX *Ϊ�����ʾʹ��ϵͳĬ��(szName����Ϊ��)
	virtual BOOL Register(LPTSTR szName, WNDCLASSEX *wcApp);

	//�����ؼ�
	virtual BOOL Create() ;

	//���ٿؼ�
	virtual void Destroy() ;
	
	//ģ̬��ʾ
	virtual int DoModal();

	//��ģ̬��ʾ
	virtual void Show();

};

#endif