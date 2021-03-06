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
		waWinAttribute->lpClassName,							//窗口类注册名
		waWinAttribute->lpWindowName,							//设置窗口标题-必须唯一
		waWinAttribute->dwStyle,								//设置窗口风格
		waWinAttribute->nPosX,									//设置窗口左上角X坐标		
		waWinAttribute->nPosY,									//设置窗口左上角Y坐标	
		waWinAttribute->nWidth,									//设置窗口宽度
		waWinAttribute->nHeight,								//设置窗口高度
		waWinAttribute->hWndParent,								//父窗口句柄
		waWinAttribute->hMenu,									//菜单的句柄
		waWinAttribute->hInstance,								//程序实例句柄
		waWinAttribute->lpParam);								//传递给消息函数的指针
}

BOOL SWidget::DestroyWidget(HWND hWnd)
{
	return ::DestroyWindow(hWnd);
}
////
void SWidget::InitAttribute()
{
	/* 设置属性表的默认值 */

	//WndClassEx初始化
	GetWndClassEx()->lpszClassName = TEXT("swidget");						//设置窗口类名(提供给CreateWindow()使用)
	GetWndClassEx()->style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;			//垂直水平重绘,运行双击传递消息;(游戏窗口不建议采用CS_DBLCLKS样式)
	GetWndClassEx()->hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL);	//指定义窗口应用程序的句柄
	GetWndClassEx()->cbWndExtra = 0;										//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	GetWndClassEx()->cbClsExtra = 0;										//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	GetWndClassEx()->lpfnWndProc = SMessageHandler::GetMessageProc();		//默认选择自定义消息回调
	GetWndClassEx()->hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（大）
	GetWndClassEx()->hIcon = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（小）
	GetWndClassEx()->hCursor = LoadCursor(NULL, IDC_ARROW);					//加载鼠标样式
	GetWndClassEx()->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			//设置窗口背景色
	GetWndClassEx()->lpszMenuName = NULL;									//设置窗口没有菜单
	GetWndClassEx()->cbSize = sizeof(WNDCLASSEX);							//长度

	// WinAttribute初始化
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;			//窗口类注册名
	GetWindowAttribute()->lpWindowName = TEXT("Widget");						//设置窗口标题-必须唯一
	GetWindowAttribute()->hInstance = GetWndClassEx()->hInstance;				//程序实例句柄
	GetWindowAttribute()->dwStyle = WS_OVERLAPPEDWINDOW;						//定义窗口风格(系统菜单--默认只带一个关闭按钮)
	GetWindowAttribute()->hMenu = NULL;											//菜单的句柄
	GetWindowAttribute()->hWndParent = GetParent() ? GetParent()->GetWnd().GetHandle() : NULL;
	GetWindowAttribute()->nPosX = CW_USEDEFAULT;								//设置窗口左上角X坐标	
	GetWindowAttribute()->nPosY = CW_USEDEFAULT;								//设置窗口左上角Y坐标	
	GetWindowAttribute()->nWidth = CW_USEDEFAULT;								//设置窗口宽度
	GetWindowAttribute()->nHeight = CW_USEDEFAULT;								//设置窗口高度
	GetWindowAttribute()->lpParam = (SMessageHandler *)this;					//设置参数,让消息顺序能正确执行到对象消息,必须带上类型

	GetWindowAttribute()->bEnabled=TRUE;										//初始可用
	GetWindowAttribute()->bVisible=TRUE;										//初始不可见

}

BOOL SWidget::DoPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	//保持父类与子类属性一致性
	{
		//保持回调函数的一致
		lpWndClassEx->lpfnWndProc = SMessageHandler::GetMessageProc();
	}

	BOOL ret = OnPreCreate(lpWndClassEx, lpWinAttribute);

	//通用操作
	{
		//类注册
		if (m_pWndClassEx->lpszClassName)	//如果不是系统默认类
		{
			/* NEED:应该先判断类是否存在(16/08/2017) */
			if (!(m_useClass=SWidget::RegisterWidget(m_pWndClassEx))){
				m_useClass = (ATOM)m_pWndClassEx->lpszClassName;
				/*::MessageBox(NULL, TEXT("Class registration failed"), TEXT("Error"), 0);
				return FALSE;*/
				
			}

		}

		//样式附加操作
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
	//通用操作
	{
		{
			if (m_pWinAttribute->bVisible == TRUE) ShowWindow(SApplication::GetCmdShow());
			else HideWindow();
		}

		//释放临时资源
		delete m_pWndClassEx;
		delete m_pWinAttribute;
		m_pWndClassEx = NULL;
		m_pWinAttribute = NULL;
	}
	return OnAftCreate(sWnd);
}

BOOL SWidget::DoInit(SWnd sWnd, SInstance SInstance)
{
	BOOL ret;
	ret = OnInit(sWnd, SInstance);
	if (ret){
		//创建子控件
		InitChild();
	}
	
	return ret;
}
void SWidget::DoRun()
{
	//TODO:由系统处理的主循环
	m_bIsrunning = TRUE;
	OnRun();
}
void SWidget::DoRan()
{	
	//TODO:由系统处理的主循环后
	OnRan();
	m_bIsrunning = FALSE;
}

void SWidget::OnMsgLoopEvent() 
{
	//转回到Widget的重载
	OnRunning();
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
	m_bIsrunning = FALSE;

	m_pThread = new SThread((SRunnable *) this);
	m_pWndClassEx = new WNDCLASSEX();									//类属性
	m_pWinAttribute = new WINATTRIBUTE();								//窗口属性

	//初始化属性表
	InitAttribute();
}
//深拷贝
SWidget::SWidget(SWidget &obj)
{
	m_pParent = obj.m_pParent;
	/* 使用此类生成新窗口 */
	m_pThread = new SThread((SRunnable *) this);
	m_pWndClassEx = new WNDCLASSEX();										//类属性
	m_pWinAttribute = new WINATTRIBUTE();									//窗口属性
	if (obj.GetWndClassEx()){						
		*m_pWndClassEx = *obj.GetWndClassEx();								//拷贝
	}
	if (obj.GetWindowAttribute()){
		*m_pWinAttribute = *obj.GetWindowAttribute();
	}
	else {
		//使用已有类名
		m_pWinAttribute->lpClassName =(LPTSTR) obj.m_useClass;
		
	}

}

SWidget::~SWidget()
{
	//TODO:只进行资源释放,不能反注册
	//TODO:线程结束不代表对被释放,

	delete m_pThread;
	delete m_pWndClassEx;
	delete m_pWinAttribute;
}

////
SWidget *SWidget::GetParent()
{
	return m_pParent;
}


//获取控件句柄
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
/* 设置控件标题 */
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

//获取控件实例句柄
SInstance SWidget::GetInstance()
{
	if (m_Wnd.GetHandle())
		return (HINSTANCE)m_Wnd.GetWindowLong(GWL_HINSTANCE);
	else
		return (SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL));
}

/* 设置控件样式 */
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
		//需要重绘窗口才能显示变更后的菜单
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

	/*非全屏状态下，窗口显示在屏幕中心*/
	//计算加上边框后的窗口大小
	int tw = nWidth + ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int th = nHeight + ::GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//计算在窗口居中时，窗口左上角的位置
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

void SWidget::SetRect(const SRECT rt)
{
	SetRect(rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top);
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
		/* TODo :未初始化前取得客户区大小不正确 */
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

//替换背景画刷
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
/* 置顶窗口 */
BOOL SWidget::SetForeground()
{
	return m_Wnd.SetForegroundWindow();
}

/* 取得焦点 */
SWnd SWidget::SetFocus()
{
	return m_Wnd.SetFocus();
}
///

BOOL SWidget::IsCreated()
{
	return m_Wnd.GetHandle() ? TRUE : FALSE;
}

BOOL SWidget::IsRunning()
{
	return m_bIsrunning ? TRUE : FALSE;
}

////////////////////////
//定时器设置
UINT_PTR SWidget::SetTimer(UINT_PTR nIDEvent, UINT nElapse, TIMERPROC lpTimerFunc)
{
	return m_Wnd.SetTimer(nIDEvent, nElapse, lpTimerFunc);
}
BOOL SWidget::KillTimer(UINT_PTR nIDEvent)
{
	return m_Wnd.KillTimer(nIDEvent);
}


//显示控件
void SWidget::ShowWindow()
{
	ShowWindow(SW_SHOWNORMAL);
}
void SWidget::ShowWindow(int nCmdShow)
{
	m_Wnd.ShowWindow( nCmdShow);	//显示控件
}

//隐藏控件
void SWidget::HideWindow()
{
	ShowWindow(SW_HIDE);
}

//更新控件
void SWidget::UpdateWindow()
{

	m_Wnd.InvalidateRect( NULL, FALSE);	//更新区域添加一个矩形为整个窗体,不要擦掉背景
	m_Wnd.UpdateWindow();					//强制刷新窗口
	
}
//游戏用
void SWidget::UpdateWindow(int left, int top, int right, int bottom)
{
	SRECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	m_Wnd.InvalidateRect(&temp, FALSE);	//更新区域添加一个矩形,不要擦掉背景
	m_Wnd.UpdateWindow();					//强制刷新窗口,
	
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

//设置分层窗口透明度，常和 UpdateLayeredWindow 函数结合使用
BOOL SWidget::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	return m_Wnd.SetLayeredWindowAttributes(crKey, bAlpha, dwFlags);
}

//重绘控件
void SWidget::ReDrawWindow()
{
	m_Wnd.InvalidateRect(NULL, FALSE);	//强制刷新窗口,不要擦掉背景
	m_Wnd.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:关于这个函数理解不是很好
}
/////////////
/* 以下两个函数偏向窗口-控件类需重写 */
BOOL SWidget::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	//给窗口属性赋值
	GetWndClassEx()->lpszClassName = TEXT("swidget");							//设置窗口类名(提供给CreateWindow()使用)
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;			//使用的注册类名
	GetWindowAttribute()->lpWindowName = TEXT("Widget");						//设置窗口标题-必须唯一
	return TRUE;
}

BOOL SWidget::OnCreate(MessageParam param)
{

	return TRUE;
}

BOOL SWidget::OnAftCreate(SWnd sWnd)
{
	if (!sWnd.GetHandle()){
		SApplication::GetApp()->UnRegisterWidget(this);									//如果窗口建立失败则返回FALSE
		::MessageBox(NULL, TEXT("Window creation failed"), TEXT("Error"), 0);

		return FALSE;
	}
	return TRUE;
}

BOOL SWidget::OnInit(SWnd sWnd, SInstance SInstance)
{

	return TRUE;
}

//控件消息处理
LRESULT CALLBACK SWidget::OnProc(MessageParam param)
{
	switch (param.uMsg)
	{
		/* NOTE:非常重要,为OnCreate()函数提供m_Wnd */
		/* TODO:WM_NCCREATE执行应该有消息类处理,放在此处出处理不妥当 */
	case WM_NCCREATE:
		//TODO:感觉此处的hWnd可能与Create()返回的hWnd不一致
		m_Wnd.SetHandle(param.hWnd);
		//NOTE:必须返回默认操作
		return SMessageHandler::OnProc(param);
		break;
	case WM_CREATE:
		m_Wnd.SetHandle(param.hWnd);
		OnCreate(param);
		break;

	case WM_DESTROY:				//程序销毁消息
		PostQuitMessage(0);			//DOUBT:不靠谱,并不是退出自身的,会造成接收不到WM_QUIT消息
		break;
	default:
		return SMessageHandler::OnProc(param);
	}
	return 0;
}


void SWidget::OnRun()
{
	SMessageHandler::OnMsgLoop();
}

//控件循环事件
void SWidget::OnRunning()
{
	//TODO:主要循环的事件:逻辑事件
	//NOTE:空闲时间应该让线程休眠,减少CPU占用
	//TODO:每个部件都暂停10ms将会引发严重后果(除非是子部件)
	//SThread::Sleep(10);
}

//控件退出事件
void SWidget::OnRan()
{
	//TODO:处理OnRun()结束的事
}
////////////

void SWidget::Run()
{
	if (!IsCreated())
	{
		if (!Create())
			return;
	}

	{
		SubClass(m_Wnd.GetHandle());
		m_Wnd.SetParent(NULL);	//TODO:不符合逻辑
		SApplication::GetApp()->RegisterWidget(this);

		DoInit(GetWnd(), GetInstance());
		DoRun();
		DoRan();//出口

		UnSubClass(m_Wnd.GetHandle());									//解除绑定消息函数
		SApplication::GetApp()->DestroyWidget(this);					//通知主线程,线程结束
	}

}


//创建控件
BOOL SWidget::Create()
{
	//NOTE:用于注册控件类型
	if (!SWidget::DoPreCreate(m_pWndClassEx, m_pWinAttribute))
		return FALSE;

	//IMPORTMENT:如果回调函数中没有对WM_NCCREATE消息进行处理会导致返回 NULL
	//TODO:m_szClassName与m_szTitle如果与其他控件重名会产生冲突
	//调用函数CreateWindow建立窗口
	HWND hWnd = SWidget::CreateWidget(m_pWinAttribute);

	if (!SWidget::DoAftCreate(hWnd))
		return FALSE;
	

	return TRUE;
}

//销毁控件
void SWidget::Destroy(){
	//销毁窗口
	DestroyWindow(m_Wnd.GetHandle());
}

//模态显示
int SWidget::DoModal()
{
	if (!IsRunning())
	{
		if (!IsCreated())
		{
			if (!Create())	
				return 1;
		}

		{
			//如果是父窗口,将消息托管给全局
			//如果是自定义消息,则还必须注册到消息管理接收消息
			SWnd parent = m_pParent ? m_pParent->GetWnd() : NULL;
			SubClass(m_Wnd.GetHandle());
			m_Wnd.SetParent(NULL);

			{
				//将父窗口的消息交接给子窗口
				::EnableWindow(parent.GetHandle(), FALSE);  //锁定父窗口

				DoInit(GetWnd(), GetInstance());
				DoRun();
				DoRan();	//出口


				::EnableWindow(parent.GetHandle(), TRUE);//释放父窗口
				HideWindow();//隐藏自己
			}

			//把父窗口置顶到前端-会造成闪烁
			parent.SetForegroundWindow();

		}

	}
	else ShowWindow();
		
	return 0;
}

//非模态显示
void SWidget::Show()
{
	if (!IsRunning()){
		m_pThread->Start();	//开启线程
	}
	else ShowWindow();

}
