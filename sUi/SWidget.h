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
#include "SInstance.h"
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
	int nPosX;
	int nPosY;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;

	//������
	BOOL bEnabled;
	BOOL bVisible;

}WINATTRIBUTE, *LPWINATTRIBUTE;



class SWidget:
	public SObject,
	public SRunnable,
	public SMessageHandler
{
	friend class SApplication;
public:
	//ע��һ����
	static ATOM SWidget::RegisterWidget(const WNDCLASSEX *wxClassEx);
	//����һ������
	static HWND SWidget::CreateWidget(const WINATTRIBUTE *waWinAttribute);
protected:
	SWidget *m_pParent;				//����ؼ�
	
	SWnd m_Wnd;						//�ؼ����
	SThread *m_pThread;				//�߳�

	/* ��������ֻ�ṩ��ʱʹ��,Create()��ɺ��Զ��ͷ� */
	ATOM m_useClass;				//ʹ�õ�������
	WNDCLASSEX *m_pWndClassEx;		//������
	WINATTRIBUTE *m_pWinAttribute;	//��������

public:
	SWidget(SWidget *parent = NULL);
	SWidget(SWidget &obj);	//���
	virtual ~SWidget();
private:
	/* ˽�в��� */
	void InitAttribute();
	BOOL DoPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);
	BOOL DoAftCreate(SWnd sWnd);
public:
	/* �ؼ�ͨ�ò��� */
	/* ���Ա��ȡ������ */
	LPWNDCLASSEX GetWndClassEx();
	LPWINATTRIBUTE GetWindowAttribute();
public:
	/* ������һЩͨ�ò��� */
	//��ȡ���ÿؼ�����
	SWidget *GetParent();

	//��ȡ���ÿؼ����
	SWnd GetWnd();

	//��ȡ�豸������
	SDc GetDC();
public:
	/* ��������-������̬�;�̬���� */
	/* ���²�����Դ���-GWL_ */
	// ��ȡ���ÿؼ�����״̬ 
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	// ��ȡ���ÿؼ��ɼ�״̬ 
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	void SetInstance(HINSTANCE hInstance);
	HINSTANCE GetInstance();

	//ȡ�������ı�����
	void SetFont(HFONT font);
	HFONT GetFont();

	// ���ÿؼ����� 
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	// ���ÿؼ���ʽ 
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	BOOL IsHaveStyle(DWORD dwStyle);

	// ��ȡ���ÿؼ�λ�� 
	POINT GetPos();
	int GetPosX();
	int GetPosY();
	void SetPos(int x, int y);
	void SetPosAtCenter();//��������Ϊ��Ļ����
	void MovePos(int x, int y);

	// ��ȡ���ÿؼ���� 
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	SIZE GetSize();

	//����,��ȡ�˵�
	void SetMenu(HMENU hMenu);
	HMENU GetMenu();

	// ��ȡ���ÿؼ����� 
	RECT GetRect();
	void SetRect(RECT rt);

	/* ���²��������-��Ӱ�츸����������� */
	/* WndClass���Ա��-ֻ֧�־�̬GCL_ */
	//�滻�˵���
	void SetMenuName(LPTSTR lpMenuName);
	LPTSTR GetMenuName();
	//���ô�ͼ��
	void SetBigIcon(HICON szIcon);
	HICON GetBigIcon();
	//����Сͼ��
	void SetSmallIcon(HICON szIcon);
	HICON GetSmallIcon();
	//�������ָ��
	void SetCursorIcon(HICON szIcon);
	HICON GetCursorIcon();
	//�滻������ˢ
	void SetBkBr(HBRUSH hBr);
	HBRUSH GetBkBr();

public:
	/* �����Ƿ񴴽�*/
	BOOL IsCreated();

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
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx,WINATTRIBUTE *lpWinAttribute);

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

	//�����ؼ�
	virtual BOOL Create();

	//���ٿؼ�
	virtual void Destroy() ;
	
	//ģ̬��ʾ
	virtual int DoModal();

	//��ģ̬��ʾ
	virtual void Show();

};

#endif