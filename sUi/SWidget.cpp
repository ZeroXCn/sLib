#include "SWidget.h"

////
ATOM SWidget::RegisterWidget(const WNDCLASSEX *wxClassEx)
{
	return ::RegisterClassEx(wxClassEx);
}
BOOL SWidget::UnRegisterWidget(LPCTSTR lpClassName, HINSTANCE hInstance)
{
	return ::UnregisterClass(lpClassName, hInstance);
}
BOOL SWidget::UnRegisterWidget(ATOM atom, HINSTANCE hInstance)
{
	if (!hInstance)hInstance = SApplication::GetApp()->GetInstance();
	return ::UnregisterClass((LPTSTR)atom, hInstance);
}
HWND SWidget::CreateWidget(const WINATTRIBUTE *waWinAttribute)
{
	return ::CreateWindow(
		waWinAttribute->lpClassName,							//������ע����
		waWinAttribute->lpWindowName,							//���ô��ڱ���-����Ψһ
		waWinAttribute->dwStyle,								//���ô��ڷ��
		waWinAttribute->nPosX,									//���ô������Ͻ�X����		
		waWinAttribute->nPosY,									//���ô������Ͻ�Y����	
		waWinAttribute->nWidth,									//���ô��ڿ��
		waWinAttribute->nHeight,								//���ô��ڸ߶�
		waWinAttribute->hWndParent,								//�����ھ��
		waWinAttribute->hMenu,									//�˵��ľ��
		waWinAttribute->hInstance,								//����ʵ�����
		waWinAttribute->lpParam);								//���ݸ���Ϣ������ָ��
}

BOOL SWidget::DestroyWidget(HWND hWnd)
{
	return ::DestroyWindow(hWnd);
}
////
void SWidget::InitAttribute()
{
	/* �������Ա��Ĭ��ֵ */

	//WndClassEx��ʼ��
	GetWndClassEx()->lpszClassName = TEXT("swidget");						//���ô�������(�ṩ��CreateWindow()ʹ��)
	GetWndClassEx()->style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;			//��ֱˮƽ�ػ�,����˫��������Ϣ;(��Ϸ���ڲ��������CS_DBLCLKS��ʽ)
	GetWndClassEx()->hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL);	//ָ���崰��Ӧ�ó���ľ��
	GetWndClassEx()->cbWndExtra = 0;										//ָ�򴰿ڹ��̺�����ָ��. ����ʹ�� CallWindowProc�������ô��ڹ���.
	GetWndClassEx()->cbClsExtra = 0;										//ָ����������֮��ĸ����ڴ�ռ���ֽ���. ϵͳ��ʼ��Ϊ0.
	GetWndClassEx()->lpfnWndProc = SMessageHandler::GetMessageProc();		//Ĭ��ѡ���Զ�����Ϣ�ص�
	GetWndClassEx()->hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//���س���ͼ�꣨��
	GetWndClassEx()->hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���س���ͼ�꣨С��
	GetWndClassEx()->hCursor = LoadCursor(NULL, IDC_ARROW);					//���������ʽ
	GetWndClassEx()->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			//���ô��ڱ���ɫ
	GetWndClassEx()->lpszMenuName = NULL;									//���ô���û�в˵�
	GetWndClassEx()->cbSize = sizeof(WNDCLASSEX);							//����

	// WinAttribute��ʼ��
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;			//������ע����
	GetWindowAttribute()->lpWindowName = TEXT("Widget");						//���ô��ڱ���-����Ψһ
	GetWindowAttribute()->hInstance = GetWndClassEx()->hInstance;				//����ʵ�����
	GetWindowAttribute()->dwStyle = WS_OVERLAPPEDWINDOW;						//���崰�ڷ��(ϵͳ�˵�--Ĭ��ֻ��һ���رհ�ť)
	GetWindowAttribute()->hMenu = NULL;											//�˵��ľ��
	GetWindowAttribute()->hWndParent = GetParent() ? GetParent()->GetWnd().GetHandle() : NULL;
	GetWindowAttribute()->nPosX = CW_USEDEFAULT;								//���ô������Ͻ�X����	
	GetWindowAttribute()->nPosY = CW_USEDEFAULT;								//���ô������Ͻ�Y����	
	GetWindowAttribute()->nWidth = CW_USEDEFAULT;								//���ô��ڿ��
	GetWindowAttribute()->nHeight = CW_USEDEFAULT;								//���ô��ڸ߶�
	GetWindowAttribute()->lpParam = (SMessageHandler *)this;					//���ò���,����Ϣ˳������ȷִ�е�������Ϣ,�����������

	GetWindowAttribute()->bEnabled=TRUE;										//��ʼ����
	GetWindowAttribute()->bVisible=TRUE;										//��ʼ���ɼ�

}

BOOL SWidget::DoPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	//���ָ�������������һ����
	{
		//���ֻص�������һ��
		lpWndClassEx->lpfnWndProc = SMessageHandler::GetMessageProc();
	}

	BOOL ret = OnPreCreate(lpWndClassEx, lpWinAttribute);

	//ͨ�ò���
	{
		//��ע��
		if (m_pWndClassEx->lpszClassName)	//�������ϵͳĬ����
		{
			/* NEED:Ӧ�����ж����Ƿ����(16/08/2017) */
			if (!(m_useClass=SWidget::RegisterWidget(m_pWndClassEx))){
				m_useClass = (ATOM)m_pWndClassEx->lpszClassName;
				/*::MessageBox(NULL, TEXT("Class registration failed"), TEXT("Error"), 0);
				return FALSE;*/
				
			}

		}

		//��ʽ���Ӳ���
		{
			if (!lpWinAttribute->bEnabled)
				lpWinAttribute->dwStyle |= WS_DISABLED;
			if (lpWinAttribute->bVisible)
				lpWinAttribute->dwStyle |= WS_VISIBLE;
		}
		
		
	}
	return ret;
}
BOOL SWidget::DoAftCreate(SWnd sWnd)
{
	//ͨ�ò���
	{
		{
			if (m_pWinAttribute->bVisible == TRUE) ShowWindow(SApplication::GetCmdShow());
			else HideWindow();
		}

		//�ͷ���ʱ��Դ
		delete m_pWndClassEx;
		delete m_pWinAttribute;
		m_pWndClassEx = NULL;
		m_pWinAttribute = NULL;
	}
	return OnAftCreate(sWnd);
}

BOOL SWidget::DoInit(SWnd sWnd, SInstance SInstance)
{
	BOOL ret = OnInit(sWnd, SInstance);
	if (ret){
		//�����ӿؼ�
		InitChild();
	}
	return ret;
}
////////////////////
void SWidget::AddInitChild(SWidget *parent, SWidget *child)
{
	if (child){
		if (parent->m_ChildInitList == NULL)
			parent->m_ChildInitList = new std::queue<SWidget *>();
		parent->m_ChildInitList->push(child);
	}

}
void SWidget::InitChild()
{
	if (m_ChildInitList){
		SWidget *child = NULL;
		while (!m_ChildInitList->empty()){
			child = m_ChildInitList->front();
			if (child->IsCreated() == FALSE){
				child->GetWindowAttribute()->hWndParent = GetWnd().GetHandle();
				child->Create();
			}
			m_ChildInitList->pop(); 

		}
		delete m_ChildInitList;
		m_ChildInitList = NULL;
	}
	
}

////////////////////
SWidget::SWidget(SWidget *parent):
m_pParent(parent)
{
	m_ChildInitList=NULL;

	m_pThread = new SThread((SRunnable *) this);
	m_pWndClassEx = new WNDCLASSEX();									//������
	m_pWinAttribute = new WINATTRIBUTE();								//��������

	//��ʼ�����Ա�
	InitAttribute();
}
//���
SWidget::SWidget(SWidget &obj)
{
	m_pParent = obj.m_pParent;
	/* ʹ�ô��������´��� */
	m_pThread = new SThread((SRunnable *) this);
	m_pWndClassEx = new WNDCLASSEX();										//������
	m_pWinAttribute = new WINATTRIBUTE();									//��������
	if (obj.GetWndClassEx()){						
		*m_pWndClassEx = *obj.GetWndClassEx();								//����
	}
	if (obj.GetWindowAttribute()){
		*m_pWinAttribute = *obj.GetWindowAttribute();
	}
	else {
		//ʹ����������
		m_pWinAttribute->lpClassName =(LPTSTR) obj.m_useClass;
		
	}

}

SWidget::~SWidget()
{
	//TODO:ֻ������Դ�ͷ�,���ܷ�ע��
	//TODO:�߳̽���������Ա��ͷ�,

	delete m_pThread;
	delete m_pWndClassEx;
	delete m_pWinAttribute;
}

////
SWidget *SWidget::GetParent()
{
	return m_pParent;
}


//��ȡ�ؼ����
SWnd SWidget::GetWnd()
{
	return m_Wnd;
}


///////////////////
//
LPWNDCLASSEX SWidget::GetWndClassEx()
{
	return m_pWndClassEx;
}
LPWINATTRIBUTE SWidget::GetWindowAttribute()
{
	return m_pWinAttribute;
}
/* ���ÿؼ����� */
void SWidget::SetTitle(LPTSTR szTitle)
{
	if (m_Wnd.GetHandle())
		m_Wnd.SetWindowText(szTitle);
	else
		GetWindowAttribute()->lpWindowName = szTitle;
}
LPTSTR SWidget::GetTitle()
{
	static TCHAR title[256]; 
	if (m_Wnd.GetHandle()){
		m_Wnd.GetWindowText(title, 256);
		return title;
	}
	else
	{
		return (LPTSTR)GetWindowAttribute()->lpWindowName;
	}
}
LPTSTR SWidget::GetTitle(LPTSTR szTitle, int iCount)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.GetWindowText(szTitle, iCount);
		return szTitle;
	}
	else
		return (LPTSTR)GetWindowAttribute()->lpWindowName;
}

void SWidget::SetInstance(SInstance hInstance)
{
	if (m_Wnd.GetHandle())
		m_Wnd.SetWindowLong(GWL_HINSTANCE, (LONG)hInstance.GetHandle());
	else
		GetWndClassEx()->hInstance = hInstance.GetHandle();
}

//��ȡ�ؼ�ʵ�����
SInstance SWidget::GetInstance()
{
	if (m_Wnd.GetHandle())
		return (HINSTANCE)m_Wnd.GetWindowLong(GWL_HINSTANCE);
	else
		return (SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL));
}

/* ���ÿؼ���ʽ */
void SWidget::AddStyle(DWORD dwStyle)
{
	DWORD dOldstyle = GetStyle();
	SetStyle(dOldstyle | dwStyle);
}

void SWidget::SetStyle(DWORD dwStyle)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetWindowLong(GWL_STYLE, dwStyle);
	}
	else{
		GetWindowAttribute()->dwStyle = dwStyle;
	}
	
}
DWORD SWidget::GetStyle()
{
	if (m_Wnd.GetHandle()){
		return m_Wnd.GetWindowLong(GWL_STYLE);
	}
	else{
		return GetWindowAttribute()->dwStyle;
	}
}

void SWidget::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	DWORD oldStyle = GetStyle();
	DWORD newStyle = oldStyle & ~dwRemove | dwAdd;
	SetStyle(newStyle);
	if (nFlags != 0){
		SRECT rt = GetRect();
		SetRect(rt, nFlags, 0);
	}
	UpdateWindow();

}

BOOL SWidget::IsHaveStyle(DWORD dwStyle)
{
	DWORD tstyle=0;
	BOOL ret = FALSE;
	if (m_Wnd.GetHandle()){
		tstyle = m_Wnd.GetWindowLong(GWL_STYLE);
	}
	else{
		tstyle=GetWindowAttribute()->dwStyle;
	}
	ret = ((tstyle & dwStyle) != 0) ? TRUE : FALSE;
	return ret;
}

void SWidget::SetMenu(SMenu hMenu)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetMenu(hMenu.GetHandle());
		//��Ҫ�ػ洰�ڲ�����ʾ�����Ĳ˵�
		UpdateWindow();
	}
	else{
		GetWindowAttribute()->hMenu = hMenu.GetHandle();
	}
}
SMenu SWidget::GetMenu()
{
	if (m_Wnd.GetHandle()){
		return m_Wnd.GetMenu();
	}
	else{
		return GetWindowAttribute()->hMenu;
	}
}


SPOINT SWidget::GetPos()
{
	SPOINT pt{ 0, 0 };
	SRECT rt = GetRect();
	pt.x = rt.left; pt.y = rt.top;

	return pt;
}

int SWidget::GetPosX()
{
	return GetPos().x;
}
int SWidget::GetPosY()
{
	return GetPos().y;
}


void SWidget::SetPos(int x, int y)
{
	SetRect(x, y, GetWidth(), GetHeight(), 0, NULL);
}

void SWidget::SetPosAtCenter()
{
	SRECT rt = GetRect();
	int nPosX = rt.left;
	int nPosY = rt.top;
	int nWidth = rt.right - rt.left;
	int nHeight = rt.bottom - rt.top;

	/*��ȫ��״̬�£�������ʾ����Ļ����*/
	//������ϱ߿��Ĵ��ڴ�С
	int tw = nWidth + ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int th = nHeight + ::GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//�����ڴ��ھ���ʱ���������Ͻǵ�λ��
	nPosX = (::GetSystemMetrics(SM_CXSCREEN) - tw) / 2;
	nPosY = (::GetSystemMetrics(SM_CYSCREEN) - th) / 2;

	rt.left = nPosX;
	rt.top = nPosY;
	rt.right = nPosX + nWidth;
	rt.bottom = nPosY + nHeight;

	MoveRect(rt);
}

void SWidget::MovePos(int x, int y)
{
	MoveRect(x, y, GetWidth(), GetHeight());
}

SPOINT SWidget::GetClientPos()
{
	SPOINT pt{ 0, 0 };
	SRECT rtOri = GetRect();
	SRECT rtClient = GetClientRect();

	pt.x = rtOri.left + ((rtOri.right - rtOri.left) - (rtClient.right - rtClient.left))/2;
	pt.y = rtOri.top + ((rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top)) / 2;

	return pt;

}
int SWidget::GetClientPosX(){
	return GetClientPos().x;
}
int SWidget::GetClientPosY()
{
	return GetClientPos().y;
}
void SWidget::SetClientPos(int x, int y)
{
	MoveClientRect(x, y, GetClientWidth(), GetClientHeight());
}



int SWidget::GetWidth()
{
	SRECT rt = GetRect();
	return rt.right - rt.left;
}
int SWidget::GetHeight()
{
	SRECT rt = GetRect();
	return rt.bottom - rt.top;
}
void SWidget::SetWidth(int nWidth)
{
	MoveRect(GetPosX(), GetPosY(), nWidth, GetHeight());
}
void SWidget::SetHeight(int nHeight)
{
	MoveRect(GetPosX(), GetPosY(), GetWidth(), nHeight);
}

SSIZE SWidget::GetSize()
{
	SSIZE size = { 0, 0 };
	SRECT rt = GetRect();
	size.cx = rt.left + rt.right;
	size.cy = rt.top + rt.bottom;
	return size;
}

void SWidget::SetSize(SSIZE size)
{
	SetSize(size.cx, size.cy);
}

void SWidget::SetSize(int nWidth, int nHeight)
{
	SetWidth(nWidth);
	SetHeight(nHeight);
}

void SWidget::LockSize(BOOL bLock)
{
	if (bLock)
		ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, 0);
	else
		ModifyStyle(0, WS_THICKFRAME | WS_MAXIMIZEBOX);
}

BOOL SWidget::IsLockSize()
{
	return IsHaveStyle(WS_THICKFRAME | WS_MAXIMIZEBOX);
}


int SWidget::GetClientWidth()
{
	SRECT rt = GetClientRect();
	return rt.right - rt.left;
	
}
int SWidget::GetClientHeight()
{
	SRECT rt = GetClientRect();
	return rt.bottom - rt.top;
}
void SWidget::SetClientWidth(int nWidth)
{
	MoveClientRect(GetClientPosX(), GetClientPosY(), nWidth, GetClientHeight());
}
void SWidget::SetClientHeight(int nHeight)
{
	MoveClientRect(GetClientPosX(), GetClientPosY(), GetClientWidth(), nHeight);
}
SSIZE SWidget::GetClientSize()
{
	SSIZE size = { 0, 0 };
	SRECT rt = GetClientRect();
	size.cx = rt.left + rt.right;
	size.cy = rt.top + rt.bottom;
	return size;
}


SRECT SWidget::GetRect()
{
	SRECT rt;

	if (m_Wnd.GetHandle()){
		m_Wnd.GetWindowRect(&rt);
	}
	else{
		rt.left = GetWindowAttribute()->nPosX;
		rt.top = GetWindowAttribute()->nPosY;
		rt.right = GetWindowAttribute()->nWidth + GetWindowAttribute()->nPosX;
		rt.bottom = GetWindowAttribute()->nHeight + GetWindowAttribute()->nPosY;
	}

	return rt;
}
void SWidget::MoveRect(SRECT rt, BOOL bReDraw)
{

	if (m_Wnd.GetHandle()){
		m_Wnd.MoveWindow(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, bReDraw);
	}
	else{
		GetWindowAttribute()->nPosX = rt.left;
		GetWindowAttribute()->nPosY = rt.top;
		GetWindowAttribute()->nWidth = rt.right - rt.left;
		GetWindowAttribute()->nHeight = rt.bottom - rt.top;
	}

}

void SWidget::MoveRect(int x, int y, int width, int height, BOOL bReDraw)
{
	SRECT rt;
	rt.left = x; rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	MoveRect(rt, bReDraw);
}

void SWidget::SetRect(SRECT rt, UINT uFlags, SWnd hWndInsertAfter)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetWindowPos(hWndInsertAfter.GetHandle(), rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, uFlags);
	}
	else{
		GetWindowAttribute()->nPosX = rt.left;
		GetWindowAttribute()->nPosY = rt.top;
		GetWindowAttribute()->nWidth = rt.right - rt.left;
		GetWindowAttribute()->nHeight = rt.bottom - rt.top;

	}
}
void SWidget::SetRect(int x, int y, int width, int height, UINT uFlags, SWnd hWndInsertAfter)
{
	SRECT rt;
	rt.left = x; rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	SetRect(rt, uFlags, hWndInsertAfter);
}

void SWidget::SetRect(int x, int y, int width, int height)
{
	SRECT rt;
	rt.left = x; rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	SetRect(rt, SWP_NOZORDER, nullptr);
}

void SWidget::AdjustRect(LPRECT lprt,DWORD dwStyle,BOOL bMenu)
{
	::AdjustWindowRect(lprt, dwStyle, bMenu);
}

SRECT SWidget::GetClientRect()
{
	SRECT rt;

	if (m_Wnd.GetHandle()){
		m_Wnd.GetClientRect(&rt);
	}
	else{
		rt.left = 0;
		rt.top = 0;
		/* TODo :δ��ʼ��ǰȡ�ÿͻ�����С����ȷ */
		rt.right = GetWindowAttribute()->nWidth + GetWindowAttribute()->nPosX - 10;
		rt.bottom = GetWindowAttribute()->nHeight + GetWindowAttribute()->nPosY - 8;
	}

	return rt;
}

void SWidget::SetClientRect(SRECT rt, UINT uFlags, SWnd hWndInsertAfter)
{
	SRECT rtOri = GetRect();
	SRECT rtClient = GetClientRect();

	int nNewX = rt.left - ((rtOri.right - rtOri.left) - (rtClient.right - rtClient.left)) / 2;
	int nNewY = rt.top - ((rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top)) / 2 ;
	int nNewWidth = (rtOri.right - rtOri.left) - (rtClient.right - rtClient.left) + (rt.right - rt.left);
	int nNewHeight = (rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top) + (rt.bottom - rt.top);

	SetRect(nNewX, nNewY, nNewWidth, nNewHeight, uFlags, hWndInsertAfter);

}
void SWidget::SetClientRect(int x, int y, int width, int height, UINT uFlags, SWnd hWndInsertAfter)
{
	SRECT rt;
	rt.left = x; rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	SetClientRect(rt, uFlags, hWndInsertAfter);
}
void SWidget::MoveClientRect(SRECT rt, BOOL bReDraw )
{
	SRECT rtOri = GetRect();
	SRECT rtClient = GetClientRect();

	int nNewX = rt.left - ((rtOri.right - rtOri.left) - (rtClient.right - rtClient.left)) / 2;
	int nNewY = rt.top - ((rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top)) / 2;
	int nNewWidth = (rtOri.right - rtOri.left) - (rtClient.right - rtClient.left) + (rt.right - rt.left);
	int nNewHeight = (rtOri.bottom - rtOri.top) - (rtClient.bottom - rtClient.top) + (rt.bottom - rt.top);

	MoveRect(nNewX, nNewY, nNewWidth, nNewHeight, bReDraw);
}

void SWidget::MoveClientRect(int x, int y, int width, int height, BOOL bReDraw)
{
	SRECT rt;
	rt.left = x; rt.top = y;
	rt.right = x + width;
	rt.bottom = y + height;
	MoveClientRect(rt, bReDraw);
}


BOOL SWidget::IsEnabled()
{
	if (m_Wnd.GetHandle()){
		BOOL ret = FALSE;
		DWORD tstyle = m_Wnd.GetWindowLong(GWL_STYLE);
		ret = ((tstyle & WS_DISABLED) != 0) ? TRUE: FALSE;
		return ret;
	}
	else
		return GetWindowAttribute()->bEnabled;
}
void SWidget::SetEnabled(BOOL bEnabled)
{
	if (m_Wnd.GetHandle())
		m_Wnd.EnableWindow(bEnabled);
	else
		GetWindowAttribute()->bEnabled = bEnabled;
}

BOOL SWidget::IsVisible()
{
	if (m_Wnd.GetHandle())
		return m_Wnd.IsWindowVisible();
	else 
		return GetWindowAttribute()->bVisible;
}
void SWidget::SetVisible(BOOL bVisible)
{
	if (m_Wnd.GetHandle()){
		if (bVisible)
			ShowWindow();
		else
			HideWindow();
	}
	else
		GetWindowAttribute()->bVisible = bVisible;

}
///////////////////
void SWidget::SetMenuName(LPTSTR lpMenuName)
{
	if (m_Wnd.GetHandle())
		m_Wnd.SetClassLong(GCL_MENUNAME, (LONG)lpMenuName);
	else
		GetWndClassEx()->lpszMenuName = lpMenuName;
}
LPTSTR SWidget::GetMenuName()
{
	if (m_Wnd.GetHandle())
		return (LPTSTR)m_Wnd.GetClassLong(GCL_MENUNAME);
	else
		return (LPTSTR)GetWndClassEx()->lpszMenuName;
}

void SWidget::SetCursorIcon(SCursor hIcon){

	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon.GetHandle();
		m_Wnd.SetClassLong(GCL_HCURSOR, lCur);
	}
	else 
		GetWndClassEx()->hCursor = hIcon.GetHandle();
}
SCursor SWidget::GetCursorIcon(){

	if (m_Wnd.GetHandle()){
		return (HCURSOR)m_Wnd.GetClassLong(GCL_HCURSOR);
	}
	else
		return GetWndClassEx()->hCursor;
}

void SWidget::SetBigIcon(SIcon hIcon)
{
	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon.GetHandle();
		m_Wnd.SetClassLong(GCL_HICON, lCur);
	}
	else
		GetWndClassEx()->hIcon = hIcon.GetHandle();
}

SIcon SWidget::GetBigIcon()
{
	if (m_Wnd.GetHandle()){
		return (HICON)m_Wnd.GetClassLong(GCL_HICON);
	}
	else
		return GetWndClassEx()->hIcon;
}


void SWidget::SetSmallIcon(SIcon hIcon)
{
	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon.GetHandle();
		m_Wnd.SetClassLong(GCL_HICONSM, lCur);
	}
	else
		GetWndClassEx()->hIconSm = hIcon.GetHandle();
}

SIcon SWidget::GetSmallIcon()
{
	if (m_Wnd.GetHandle()){
		return (HICON)m_Wnd.GetClassLong(GCL_HICONSM);
	}
	else
		return GetWndClassEx()->hIconSm;
}

//�滻������ˢ
void SWidget::SetBkBr(SBrush hBr)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetClassLong(GCL_HBRBACKGROUND, (LONG)hBr.GetHandle());
	}
	else
		GetWndClassEx()->hbrBackground = hBr.GetHandle();
}

SBrush SWidget::GetBkBr()
{
	if (m_Wnd.GetHandle()){
		return (HBRUSH)m_Wnd.GetClassLong(GCL_HBRBACKGROUND);
	}
	else
		return GetWndClassEx()->hbrBackground ;
}

void SWidget::AddClassStyle(UINT style)
{
	UINT uOldStyle = GetClassStyle();
	SetClassStyle(uOldStyle | style);
}
void SWidget::SetClassStyle(UINT style)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetClassLong(GCL_STYLE, (LONG)style);
	}
	else
		GetWndClassEx()->style = style;
}
UINT SWidget::GetClassStyle()
{
	if (m_Wnd.GetHandle()){
		return (UINT)m_Wnd.GetClassLong(GCL_STYLE);
	}
	else
		return GetWndClassEx()->style;
}
////////////////////////////////////////////
void SWidget::SetFont(SFont font)
{
	m_Wnd.SendMessage(WM_SETFONT, (WPARAM)font.GetHandle(), 0);
}
SFont SWidget::GetFont()
{
	return (HFONT)m_Wnd.SendMessage(WM_GETFONT, 0, 0);
}


//////////////////////////////////
/* �ö����� */
BOOL SWidget::SetForeground()
{
	return m_Wnd.SetForegroundWindow();
}

/* ȡ�ý��� */
SWnd SWidget::SetFocus()
{
	return m_Wnd.SetFocus();
}
///

BOOL SWidget::IsCreated()
{
	return m_Wnd.GetHandle() ? TRUE : FALSE;
}

////////////////////////
//��ʱ������
UINT_PTR SWidget::SetTimer(UINT_PTR nIDEvent, UINT nElapse, TIMERPROC lpTimerFunc)
{
	return m_Wnd.SetTimer(nIDEvent, nElapse, lpTimerFunc);
}
BOOL SWidget::KillTimer(UINT_PTR nIDEvent)
{
	return m_Wnd.KillTimer(nIDEvent);
}


//��ʾ�ؼ�
void SWidget::ShowWindow()
{
	ShowWindow(SW_SHOWNORMAL);
}
void SWidget::ShowWindow(int nCmdShow)
{
	m_Wnd.ShowWindow( nCmdShow);	//��ʾ�ؼ�
}

//���ؿؼ�
void SWidget::HideWindow()
{
	ShowWindow(SW_HIDE);
}

//���¿ؼ�
void SWidget::UpdateWindow()
{

	m_Wnd.InvalidateRect( NULL, FALSE);	//�����������һ������Ϊ��������,��Ҫ��������
	m_Wnd.UpdateWindow();					//ǿ��ˢ�´���
	
}
//��Ϸ��
void SWidget::UpdateWindow(int left, int top, int right, int bottom)
{
	SRECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	m_Wnd.InvalidateRect(&temp, FALSE);	//�����������һ������,��Ҫ��������
	m_Wnd.UpdateWindow();					//ǿ��ˢ�´���,
	
}

BOOL SWidget::UpdateLayeredWindow(SDc sdcDst, SPOINT *pptDst, SSIZE *psize, SDc sdcSrc, SPOINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	return m_Wnd.UpdateLayeredWindow(sdcDst.GetHandle(), pptDst, psize, sdcSrc.GetHandle(), pptSrc, crKey, pblend, dwFlags);
}
BOOL SWidget::UpdateLayeredWindow(SPOINT *pptDst, SSIZE *psize, SDc sdcSrc, SPOINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	HDC hdcDst = m_Wnd.GetDC();
	BOOL ret = m_Wnd.UpdateLayeredWindow(hdcDst, pptDst, psize, sdcSrc.GetHandle(), pptSrc, crKey, pblend, dwFlags);
	m_Wnd.ReleaseDC(hdcDst);
	return ret;
}

//���÷ֲ㴰��͸���ȣ����� UpdateLayeredWindow �������ʹ��
BOOL SWidget::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	return m_Wnd.SetLayeredWindowAttributes(crKey, bAlpha, dwFlags);
}

//�ػ�ؼ�
void SWidget::ReDrawWindow()
{
	m_Wnd.InvalidateRect(NULL, FALSE);	//ǿ��ˢ�´���,��Ҫ��������
	m_Wnd.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:�������������ⲻ�Ǻܺ�
}
/////////////
/* ������������ƫ�򴰿�-�ؼ�������д */
BOOL SWidget::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	//���������Ը�ֵ
	GetWndClassEx()->lpszClassName = TEXT("swidget");							//���ô�������(�ṩ��CreateWindow()ʹ��)
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;			//ʹ�õ�ע������
	GetWindowAttribute()->lpWindowName = TEXT("Widget");						//���ô��ڱ���-����Ψһ
	return TRUE;
}

BOOL SWidget::OnCreate(MessageParam param)
{

	return TRUE;
}

BOOL SWidget::OnAftCreate(SWnd sWnd)
{
	if (!sWnd.GetHandle()){
		SApplication::GetApp()->UnRegisterWidget(this);									//������ڽ���ʧ���򷵻�FALSE
		::MessageBox(NULL, TEXT("Window creation failed"), TEXT("Error"), 0);

		return FALSE;
	}
	return TRUE;
}

BOOL SWidget::OnInit(SWnd sWnd, SInstance SInstance)
{

	return TRUE;
}

//�ؼ���Ϣ����
LRESULT CALLBACK SWidget::OnProc(MessageParam param)
{
	switch (param.uMsg)
	{
		/* NOTE:�ǳ���Ҫ,ΪOnCreate()�����ṩm_Wnd */
		/* TODO:WM_NCCREATEִ��Ӧ������Ϣ�ദ��,���ڴ˴��������׵� */
	case WM_NCCREATE:
		//TODO:�о��˴���hWnd������Create()���ص�hWnd��һ��
		m_Wnd.SetHandle(param.hWnd);
		//NOTE:���뷵��Ĭ�ϲ���
		return SMessageHandler::OnProc(param);
		break;
	case WM_CREATE:
		m_Wnd.SetHandle(param.hWnd);
		OnCreate(param);
		break;

	case WM_DESTROY:				//����������Ϣ
		PostQuitMessage(0);			//DOUBT:������,�������˳������,����ɽ��ղ���WM_QUIT��Ϣ
		break;
	default:
		return SMessageHandler::OnProc(param);
	}
	return 0;
}


void SWidget::OnRun()
{
	MSG msg;											//������Ϣ�ṹ

	/* ��Ϣѭ�� */
	while (true)
	{
		//NOTE:����ڶ�����Ϊm_hWnd�ᵼ���޷�����WM_QUIT��Ϣ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//������Ϣ
		{
			if (msg.message == WM_QUIT)					//������˳���Ϣ�����˳�ѭ��
				break;

			TranslateMessage(&msg);						//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);						//������Ϣ
		}
		else
		{
			OnRunning();								//����ϵͳ����
		}
	}
}

//�ؼ�ѭ���¼�
void SWidget::OnRunning()
{
	//TODO:��Ҫѭ�����¼�:�߼��¼�
	//NOTE:����ʱ��Ӧ�����߳�����,����CPUռ��
	SThread::Sleep(10);
}

//�ؼ��˳��¼�
void SWidget::OnRan()
{
	//TODO:����OnRun()��������
}
////////////

void SWidget::Run()
{
	if (Create()){
		SubClass(m_Wnd.GetHandle());
		m_Wnd.SetParent(NULL);	//TODO:�������߼�
		SApplication::GetApp()->RegisterWidget(this);

		DoInit(GetWnd(), GetInstance());
		OnRun();
		OnRan();//����

		UnSubClass(m_Wnd.GetHandle());									//�������Ϣ����
		SApplication::GetApp()->DestroyWidget(this);					//֪ͨ���߳�,�߳̽���
	}

}


//�����ؼ�
BOOL SWidget::Create()
{
	//NOTE:����ע��ؼ�����
	if (!SWidget::DoPreCreate(m_pWndClassEx, m_pWinAttribute))
		return FALSE;

	//IMPORTMENT:����ص�������û�ж�WM_NCCREATE��Ϣ���д���ᵼ�·��� NULL
	//TODO:m_szClassName��m_szTitle����������ؼ������������ͻ
	//���ú���CreateWindow��������
	HWND hWnd = SWidget::CreateWidget(m_pWinAttribute);

	if (!SWidget::DoAftCreate(hWnd))
		return FALSE;
	

	return TRUE;
}

//���ٿؼ�
void SWidget::Destroy(){
	//���ٴ���
	DestroyWindow(m_Wnd.GetHandle());
}

//ģ̬��ʾ
int SWidget::DoModal()
{

	if (!IsCreated()){
		if (Create()){
			//����Ǹ�����,����Ϣ�йܸ�ȫ��
			//������Զ�����Ϣ,�򻹱���ע�ᵽ��Ϣ���������Ϣ
			SWnd parent = m_pParent ? m_pParent->GetWnd() : NULL;
			SubClass(m_Wnd.GetHandle());
			m_Wnd.SetParent(NULL);

			{
				//�������ڵ���Ϣ���Ӹ��Ӵ���
				::EnableWindow(parent.GetHandle(), FALSE);  //����������

				DoInit(GetWnd(), GetInstance());
				OnRun();
				OnRan();	//����


				::EnableWindow(parent.GetHandle(), TRUE);//�ͷŸ�����
				HideWindow();//�����Լ�
			}

			//�Ѹ������ö���ǰ��-�������˸
			parent.SetForegroundWindow();

		}
	}
	else ShowWindow();

	return 0;
}

//��ģ̬��ʾ
void SWidget::Show()
{
	if (!IsCreated()){
		m_pThread->Start();	//�����߳�
	}
	else ShowWindow();

	return;
}
