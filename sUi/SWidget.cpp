#include "SWidget.h"

////
ATOM SWidget::RegisterWidget(const WNDCLASSEX *wxClassEx)
{
	return ::RegisterClassEx(wxClassEx);
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
////
void SWidget::InitAttribute()
{
	/* 设置属性表的默认值 */

	//WndClassEx初始化
	GetWndClassEx()->cbSize = sizeof(WNDCLASSEX);							//长度
	GetWndClassEx()->lpszClassName = TEXT("swidget");						//设置窗口类名(提供给CreateWindow()使用)
	GetWndClassEx()->style = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;		//定义窗口风格
	GetWndClassEx()->hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL);	//指定义窗口应用程序的句柄
	GetWndClassEx()->cbWndExtra = 0;										//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	GetWndClassEx()->cbClsExtra = 0;										//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	GetWndClassEx()->lpfnWndProc = SMessageHandler::GetMessageProc();		//默认选择自定义消息回调
	GetWndClassEx()->hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（大）
	GetWndClassEx()->hIcon = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（小）
	GetWndClassEx()->hCursor = LoadCursor(NULL, IDC_ARROW);					//加载鼠标样式
	GetWndClassEx()->hbrBackground = (HBRUSH)(COLOR_WINDOW);				//设置窗口背景色
	GetWndClassEx()->lpszMenuName = NULL;									//设置窗口没有菜单
	GetWndClassEx()->cbSize = sizeof(WNDCLASSEX);							//长度

	// WinAttribute初始化
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;			//窗口类注册名
	GetWindowAttribute()->lpWindowName = TEXT("Widget");						//设置窗口标题-必须唯一
	GetWindowAttribute()->hInstance = GetWndClassEx()->hInstance;				//程序实例句柄
	GetWindowAttribute()->dwStyle = GetWndClassEx()->style;						//设置窗口风格
	GetWindowAttribute()->hMenu = NULL;											//菜单的句柄
	GetWindowAttribute()->lpParam = NULL;										//传递给消息函数的指针
	GetWindowAttribute()->hWndParent = GetParent() ? GetParent()->GetWnd().GetHandle() : NULL;
	GetWindowAttribute()->nPosX = 0;											//设置窗口左上角X坐标	
	GetWindowAttribute()->nPosY = 0;											//设置窗口左上角Y坐标	
	GetWindowAttribute()->nWidth = 800;											//设置窗口宽度
	GetWindowAttribute()->nHeight = 600;										//设置窗口高度
	GetWindowAttribute()->lpParam = (SMessageHandler *)this;					//设置参数,让消息顺序能正确执行到对象消息,必须带上类型

	GetWindowAttribute()->bEnabled=TRUE;										//初始可用
	GetWindowAttribute()->bVisible=FALSE;										//初始不可见

}

BOOL SWidget::DoPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	BOOL ret = OnPreCreate(lpWndClassEx, lpWinAttribute);

	//通用操作
	{
		//类注册
		if (m_pWndClassEx->lpszClassName)	//如果不是系统默认类
		{
			/* NEED:应该先判断类是否存在(16/08/2017) */
			if (!SWidget::RegisterWidget(m_pWndClassEx)){
				/*::MessageBox(NULL, TEXT("Class registration failed"), TEXT("Error"), 0);
				return FALSE;*/
				
			}

			SApplication::GetApp()->RegisterWidget(this);
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
		if (!sWnd.GetHandle())
		{
			if (m_pWndClassEx->lpszClassName)	//如果不是系统默认类
				SApplication::GetApp()->UnRegisterWidget(this);		//反注册
		}

		//释放临时资源
		delete m_pWndClassEx;
		delete m_pWinAttribute;
		m_pWndClassEx = NULL;
		m_pWinAttribute = NULL;
	}
	return OnAftCreate(sWnd);
}

SWidget::SWidget(SWidget *parent):
m_pParent(parent)
{
	m_pThread = new SThread((SRunnable *) this);
	m_pWndClassEx = new WNDCLASSEX();									//类属性
	m_pWinAttribute = new WINATTRIBUTE();								//窗口属性

	//初始化属性表
	InitAttribute();
}

SWidget::~SWidget()
{
	//TODO:只进行资源释放,不能反注册
	//TODO:线程结束不代表对被释放,

	delete m_pThread;
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

//获取设备上下文
SDc SWidget::GetDC()
{
	SDc dc;
	if (m_Wnd.GetHandle())
		dc.SetHandle(m_Wnd.GetDC());
	return dc;
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

void SWidget::SetInstance(HINSTANCE hInstance)
{
	if (m_Wnd.GetHandle())
		m_Wnd.SetWindowLong(GWL_HINSTANCE, (LONG)hInstance);
	else
		GetWndClassEx()->hInstance = hInstance;
}

//获取控件实例句柄
HINSTANCE SWidget::GetInstance()
{
	if (m_Wnd.GetHandle())
		return (HINSTANCE)m_Wnd.GetWindowLong(GWL_HINSTANCE);
	else
		return (SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL));
}

/* 设置控件样式 */
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
POINT SWidget::GetPos()
{
	POINT pt{ 0, 0 };
	if (m_Wnd.GetHandle()){
		RECT rt{ 0, 0, 0, 0 };
		m_Wnd.GetWindowRect(&rt); //获得window区域
		/**/
		pt.x = rt.left; pt.y = rt.top;
		m_Wnd.ScreenToClient(&pt); //转到client
		/* //else
		pt.x = = rt.right - rt.left;
		l pt.y = rt.bottom - rt.top
		*/

	}
	else
	{
		pt.x = GetWindowAttribute()->nPosX;
		pt.y = GetWindowAttribute()->nPosY;
	}
	return pt;
}

int SWidget::GetPosX()
{
	if (m_Wnd.GetHandle()){
		return GetPos().x;
	}
	else{
		return GetWindowAttribute()->nPosY;
	}
}
int SWidget::GetPosY()
{
	if (m_Wnd.GetHandle()){
		return GetPos().y;
	}
	else{
		return GetWindowAttribute()->nPosX;
	}
}


void SWidget::SetPos(int x, int y)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetWindowPos(NULL, x, y, GetWidth(), GetHeight(), 0);
	}
	else
	{
		GetWindowAttribute()->nPosX=x;
		GetWindowAttribute()->nPosY=y;
	}
}

void SWidget::SetPosAtCenter()
{
	RECT rt = GetRect();
	int nPosX = rt.left;
	int nPosY = rt.top;
	int nWidth = rt.right - rt.left;
	int nHeight = rt.bottom - rt.top;

	/*非全屏状态下，窗口显示在屏幕中心*/
	//计算加上边框后的窗口大小
	nWidth = nWidth + ::GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	nHeight = nHeight + ::GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//计算在窗口居中时，窗口左上角的位置
	nPosX = (::GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
	nPosY = (::GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;

	nWidth += 10;
	nHeight += 8;

	rt.left = nPosX;
	rt.top = nPosY;
	rt.right = nPosX + nWidth;
	rt.bottom = nPosY + nHeight;

	SetRect(rt);
}

void SWidget::MovePos(int x, int y)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.MoveWindow(x, y, GetWidth(), GetHeight(), FALSE);
	}
	else{
		GetWindowAttribute()->nPosX = x;
		GetWindowAttribute()->nPosY = y;
	}
}


int SWidget::GetWidth()
{
	if (m_Wnd.GetHandle()){
		RECT rt;
		m_Wnd.GetWindowRect(&rt);
		return rt.right - rt.left;
	}
	else{
		return GetWindowAttribute()->nWidth;
	}
}
int SWidget::GetHeight()
{
	if (m_Wnd.GetHandle()){
		RECT rt;
		m_Wnd.GetWindowRect(&rt);
		return rt.bottom - rt.top ;
	}
	else{
		return GetWindowAttribute()->nWidth;
	}
}
void SWidget::SetWidth(int nWidth)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.MoveWindow(GetPosX(), GetPosY(), nWidth, GetHeight(),TRUE);
	}
	else{
		GetWindowAttribute()->nWidth = nWidth;
	}
}
void SWidget::SetHeight(int nHeight)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.MoveWindow(GetPosX(), GetPosY(), GetWidth(), nHeight, TRUE);
	}
	else{
		GetWindowAttribute()->nHeight = nHeight;
	}
}

SIZE SWidget::GetSize()
{
	SIZE size = { 0, 0 };
	if (m_Wnd.GetHandle()){
		RECT rt;
		m_Wnd.GetWindowRect(&rt);
		size.cx = rt.left + rt.right;
		size.cy = rt.top + rt.bottom;
	}
	else{
		size.cx = GetWindowAttribute()->nWidth;
		size.cy = GetWindowAttribute()->nHeight;
	}
	return size;
}


RECT SWidget::GetRect()
{
	RECT rt;

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
void SWidget::SetRect(RECT rt)
{

	if (m_Wnd.GetHandle()){
		m_Wnd.MoveWindow(rt.left, rt.top, rt.right, rt.bottom,TRUE);
	}
	else{
		GetWindowAttribute()->nPosX = rt.left;
		GetWindowAttribute()->nPosY = rt.top;
		GetWindowAttribute()->nWidth = rt.right - rt.left;
		GetWindowAttribute()->nHeight = rt.bottom - rt.top;

	}

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

void SWidget::SetCursorIcon(HCURSOR hIcon){

	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon;
		m_Wnd.SetClassLong(GCL_HCURSOR, lCur);
	}
	else 
		GetWndClassEx()->hCursor = hIcon;
}
HCURSOR SWidget::GetCursorIcon(){

	if (m_Wnd.GetHandle()){
		return (HCURSOR)m_Wnd.GetClassLong(GCL_HCURSOR);
	}
	else
		return GetWndClassEx()->hCursor;
}

void SWidget::SetBigIcon(HICON hIcon)
{
	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon;
		m_Wnd.SetClassLong(GCL_HICON, lCur);
	}
	else
		GetWndClassEx()->hIcon = hIcon;
}

HICON SWidget::GetBigIcon()
{
	if (m_Wnd.GetHandle()){
		return (HICON)m_Wnd.GetClassLong(GCL_HICON);
	}
	else
		return GetWndClassEx()->hIcon;
}


void SWidget::SetSmallIcon(HICON hIcon)
{
	if (m_Wnd.GetHandle()){
		long lCur = (long)hIcon;
		m_Wnd.SetClassLong(GCL_HICONSM, lCur);
	}
	else
		GetWndClassEx()->hIconSm = hIcon;
}

HICON SWidget::GetSmallIcon()
{
	if (m_Wnd.GetHandle()){
		return (HICON)m_Wnd.GetClassLong(GCL_HICONSM);
	}
	else
		return GetWndClassEx()->hIconSm;
}

//替换背景画刷
void SWidget::SetBkBr(HBRUSH hBr)
{
	if (m_Wnd.GetHandle()){
		m_Wnd.SetClassLong(GCL_HBRBACKGROUND, (LONG)hBr);
	}
	else
		GetWndClassEx()->hbrBackground = hBr;
}

HBRUSH SWidget::GetBkBr()
{
	if (m_Wnd.GetHandle()){
		return (HBRUSH)m_Wnd.GetClassLong(GCL_HBRBACKGROUND);
	}
	else
		return GetWndClassEx()->hbrBackground ;
}
////////////////////////////////////////////
void SWidget::SetFont(HFONT font)
{
	m_Wnd.SendMessage(WM_SETFONT, (WPARAM)font, 0);
}
HFONT SWidget::GetFont()
{
	return (HFONT)m_Wnd.SendMessage(WM_GETFONT, 0, 0);
}


//////////////////////////////////
/* 置顶窗口 */
BOOL SWidget::SetForegroundWindow()
{
	return m_Wnd.SetForegroundWindow();
}

/* 取得焦点 */
HWND SWidget::SetFocus()
{
	return m_Wnd.SetFocus();
}
///

BOOL SWidget::IsCreated()
{
	return m_Wnd.GetHandle() ? TRUE : FALSE;
}

////////////////////////
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
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	m_Wnd.InvalidateRect(&temp, FALSE);	//更新区域添加一个矩形,不要擦掉背景
	m_Wnd.UpdateWindow();					//强制刷新窗口,
	
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


BOOL SWidget::OnAftCreate(SWnd sWnd)
{
	if (!sWnd.GetHandle()){
		SApplication::GetApp()->UnRegisterWidget(this);									//如果窗口建立失败则返回FALSE
		::MessageBox(NULL, TEXT("Window creation failed"), TEXT("Error"), 0);

		return FALSE;
	}
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
	MSG msg;											//定义消息结构

	/* 消息循环 */
	while (true)
	{
		//NOTE:如果第二参数为m_hWnd会导致无法接收WM_QUIT消息
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//接收消息
		{
			if (msg.message == WM_QUIT)					//如果是退出消息，则退出循环
				break;

			TranslateMessage(&msg);						//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);						//处理消息
		}
		else
		{
			OnRunning();								//交由系统处理
		}
	}
}

//控件循环事件
void SWidget::OnRunning()
{
	//TODO:主要循环的事件:逻辑事件
	//NOTE:空闲时间应该让线程休眠,减少CPU占用
	SThread::Sleep(10);
}

//控件退出事件
void SWidget::OnRan()
{
	//TODO:处理OnRun()结束的事
	UnSubClass(m_Wnd.GetHandle());									//解除绑定消息函数
	SApplication::GetApp()->DestroyWidget(this);				//通知主线程,线程结束
}
////////////

void SWidget::Run()
{
	if (Create()){
		SubClass(m_Wnd.GetHandle());
		m_Wnd.SetParent(NULL);
		ShowWindow();
		OnRun();
		OnRan();//出口
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

	if (!IsCreated()){
		if (Create()){
			//如果是父窗口,将消息托管给全局
			//如果是自定义消息,则还必须注册到消息管理接收消息
			SWnd parent = m_pParent ? m_pParent->GetWnd() : NULL;
			SubClass(m_Wnd.GetHandle());
			m_Wnd.SetParent(NULL);

			{
				//将父窗口的消息交接给子窗口
				::EnableWindow(parent.GetHandle(), FALSE);  //锁定父窗口

				ShowWindow();
				OnRun();
				OnRan();	//出口


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
	if (!IsCreated()){
		m_pThread->Start();	//开启线程
	}
	else ShowWindow();

	return;
}
