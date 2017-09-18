/**
* SWidget��
* ���в����Ļ���
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SThread.h"
#include "../sGraphic/SDc.h"

#include "tagSPOINT.h"
#include "tagSRECT.h"
#include "tagSSIZE.h"

#include "SWnd.h"
#include "SInstance.h"
#include "SMenu.h"
#include "SCursor.h"
#include "SIcon.h"
#include "SApplication.h"
#include "SMessageHandler.h"

#ifndef _SWIDGET_H_
#define _SWIDGET_H_

#include <Windows.h>
#include <queue>

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
	static BOOL SWidget::UnRegisterWidget(LPCTSTR lpClassName, HINSTANCE hInstance);
	static BOOL SWidget::UnRegisterWidget(ATOM atom, HINSTANCE hInstance=NULL);
	//����һ������
	static HWND SWidget::CreateWidget(const WINATTRIBUTE *waWinAttribute);
	static BOOL SWidget::DestroyWidget(HWND hWnd);
protected:
	std::queue<SWidget *> *m_ChildInitList;	//�����ʼ������
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
	BOOL DoInit(SWnd sWnd, SInstance SInstance);
protected:
	//���Ϊ��Ҫ��ʼ��������
	void AddInitChild(SWidget *parent,SWidget *child);
	//��ʼ�����ಢ�ͷŶ���
	void InitChild();
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

public:
	/* ��������-������̬�;�̬���� */
	/* ���²�����Դ���-GWL_ */
	// ��ȡ���ÿؼ�����״̬ 
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	// ��ȡ���ÿؼ��ɼ�״̬ 
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	void SetInstance(SInstance hInstance);
	SInstance GetInstance();

	//ȡ�������ı�����
	void SetFont(SFont font);
	SFont GetFont();

	// ���ÿؼ����� 
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	// ���û�ȡ�ؼ���ʽ 
	void AddStyle(DWORD dwStyle);
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	void ModifyStyle(DWORD dwRemove, DWORD dwAdd=0, UINT nFlags = 0);
	BOOL IsHaveStyle(DWORD dwStyle);

	//����,��ȡ�˵�
	void SetMenu(SMenu hMenu);
	SMenu GetMenu();

	// ��ȡ���ÿؼ�λ�� 
	SPOINT GetPos();
	int GetPosX();
	int GetPosY();
	void SetPos(int x, int y);
	void SetPosAtCenter();//��������Ϊ��Ļ����
	void MovePos(int x, int y);

	//ȡ�ÿͻ������ϽǾ�������
	SPOINT GetClientPos();
	int GetClientPosX();
	int GetClientPosY();
	void SetClientPos(int x, int y);

	/* ����Ҫ���ֿͻ�����ǿͻ�����С */
	// ��ȡ���ÿؼ���� 
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	SSIZE GetSize();
	void LockSize(BOOL bLock = TRUE);
	BOOL IsLockSize();

	//���û�ȡ�ͻ�����С
	int GetClientWidth();
	int GetClientHeight();
	void SetClientWidth(int nWidth);
	void SetClientHeight(int nHeight);
	SSIZE GetClientSize();

	// ��ȡ���ò������� 
	SRECT GetRect();
	void MoveRect(SRECT rt, BOOL bReDraw = TRUE);
	void SetRect(SRECT rt, UINT uFlags, SWnd hWndInsertAfter);
	void MoveRect(int x,int y,int width,int height, BOOL bReDraw = TRUE);
	void SetRect(int x, int y, int width, int height);
	void SetRect(int x, int y, int width, int height, UINT uFlags, SWnd hWndInsertAfter);
	void AdjustRect(LPRECT lprt, DWORD dwStyle, BOOL bMenu);

	//ȡ�ò����ͻ�����С
	SRECT GetClientRect();
	void SetClientRect(SRECT rt, UINT uFlags, SWnd hWndInsertAfter);
	void MoveClientRect(SRECT rt, BOOL bReDraw = TRUE);
	void SetClientRect(int x, int y, int width, int height, UINT uFlags, SWnd hWndInsertAfter);
	void MoveClientRect(int x, int y, int width, int height, BOOL bReDraw = TRUE);

	/* ���²��������-��Ӱ�츸����������� */
	/* WndClass���Ա��-ֻ֧�־�̬GCL_ */
	//�滻�˵���
	void SetMenuName(LPTSTR lpMenuName);
	LPTSTR GetMenuName();
	//���ô�ͼ��
	void SetBigIcon(SIcon szIcon);
	SIcon GetBigIcon();
	//����Сͼ��
	void SetSmallIcon(SIcon szIcon);
	SIcon GetSmallIcon();
	//�������ָ��
	void SetCursorIcon(SCursor szIcon);
	SCursor GetCursorIcon();
	//�滻������ˢ
	void SetBkBr(SBrush hBr);
	SBrush GetBkBr();
	//�滻����
	void AddClassStyle(UINT style);
	void SetClassStyle(UINT style);
	UINT GetClassStyle();

public:
	/* �����Ƿ񴴽�*/
	BOOL IsCreated();

public:
	//��ʱ��
	UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse, TIMERPROC lpTimerFunc=NULL);//ʱ��ID,ʱ����,�ص�����
	BOOL KillTimer(UINT_PTR nIDEvent);

	// �ö�����
	BOOL SetForeground();

	// ȡ�ý���
	SWnd SetFocus();
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

	//����һ���ֲ㴰�ڵ�λ��
	BOOL UpdateLayeredWindow(SDc sdcDst, SPOINT *pptDst, SSIZE *psize, SDc sdcSrc, SPOINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	BOOL UpdateLayeredWindow(SPOINT *pptDst, SSIZE *psize, SDc sdcSrc, SPOINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);

	//���÷ֲ㴰��͸���ȣ����� UpdateLayeredWindow �������ʹ��
	BOOL SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

	//�ػ�ؼ�
	void ReDrawWindow();
protected:
	//IMPORTMENT:���಻�ܵ������ຯ��,���뽫���·���д�ɽӿ�
	/*//IMPORTMENT:���ǵ������þ�̬��Ϣ�ص�����,���º�������public,����̬���������޷�����*/
	//��Ϣ�ص�����
	virtual LRESULT CALLBACK OnProc(MessageParam param);

	//��������֮ǰ-������ǿؼ�����
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx,WINATTRIBUTE *lpWinAttribute);

	//����������
	virtual BOOL OnCreate(MessageParam param);

	//��������֮��
	virtual BOOL OnAftCreate(SWnd sWnd);

	//��ʼ��
	virtual BOOL OnInit(SWnd sWnd, SInstance SInstance);

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