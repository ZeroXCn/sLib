#include "SWidget.h"

SWidget::SWidget(SWidget *parent)
{
	m_pParent = parent;

	m_hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL);

	m_parentWnd = m_pParent ? m_pParent->GetWnd().GetWnd() : NULL;
	m_hMenu = NULL;
	m_lpParam = NULL;

	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_bEnabled = TRUE;
	m_bVisible = TRUE;
	m_bIsRunning = TRUE;
	m_bSysClass = FALSE;

	lstrcpy(m_szTitle, TEXT("Widget"));
	lstrcpy(m_szTip, TEXT(""));

	m_pThread = new SThread((SRunnable *) this);

	//TODO:只有窗口才进行窗口注册

}
SWidget::~SWidget()
{
	//TODO:只进行资源释放,不能反注册
	//TODO:线程结束不代表对被释放,

	delete m_pThread;
}

/////
SWidget *SWidget::GetParent()
{
	return m_pParent;
}
void  SWidget::SetParent(SWidget *parent)
{
	m_pParent = parent;
	m_parentWnd = parent?parent->GetWnd().GetWnd():NULL;
}

/* 设置实例句柄 */
void SWidget::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

/* 设置控件句柄 */
void SWidget::SetWnd(SWnd pWnd)
{
	m_Wnd = pWnd;
}

/* 设置菜单句柄 */
void SWidget::SetMenu(HMENU hMenu)
{
	m_hMenu = hMenu;
}

HMENU SWidget::GetMenu()
{
	return m_hMenu;
}

/* 设置参数 */
void SWidget::SetParam(LPVOID lpParam)
{
	m_lpParam = lpParam;
}

//获取控件实例句柄
HINSTANCE SWidget::GetInstance()
{
	return m_hInstance;
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
	if (m_Wnd.GetWnd())
		dc.SetDC(m_Wnd.GetDC());
	return dc;
}

/* 设置参数 */
LPVOID SWidget::GetParam()
{
	return m_lpParam;
}

/* 设置控件类型名称 */
void SWidget::SetClassName(LPTSTR szClassName)
{
	lstrcpy(m_szClassName, szClassName);
}
LPTSTR SWidget::GetClassName()
{
	return m_szClassName;
}

/* 设置控件标题 */
void SWidget::SetTitle(LPTSTR szTitle)
{
	lstrcpy(m_szTitle, szTitle);					//将标题赋给m_szTitle
	if (m_Wnd.GetWnd())
		m_Wnd.SetWindowText(m_szTitle);
}
LPTSTR SWidget::GetTitle()
{
	return m_szTitle;
}
LPTSTR SWidget::GetTitle(LPTSTR szTitle, int iCount)
{
	if (m_Wnd.GetWnd()){
		m_Wnd.GetWindowText(szTitle, iCount);
		return szTitle;
	}
	else
		return m_szTitle;
}

/* 设置控件样式 */
void SWidget::SetStyle(DWORD dwStyle)
{
	if (m_Wnd.GetWnd()){
		m_Wnd.SetWindowLong(m_dwStyle, dwStyle);
	}
	m_dwStyle = dwStyle;
	
}
DWORD SWidget::GetStyle()
{
	return m_dwStyle;
}

POINT SWidget::GetPos()
{
	POINT pt{ m_nPosX, m_nPosY };
	if (m_Wnd.GetWnd()){
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
	return pt;
}
void SWidget::SetPos(POINT pt)
{
	SetPos(pt.x, pt.y);
}

void SWidget::SetPos(int x, int y)
{
	m_nPosX = x;
	m_nPosY = y;
	if (m_Wnd.GetWnd()){
		m_Wnd.SetWindowPos( NULL, m_nPosX, m_nPosY, m_nWidth, m_nHeight, 0);
	}
}

void SWidget::MovePos(int x, int y)
{
	m_nPosX = x;
	m_nPosY = y;
	if (m_Wnd.GetWnd()){
		m_Wnd.MoveWindow(x, y, m_nWidth, m_nHeight, FALSE);
	}
}
void SWidget::MovePos(POINT pt)
{
	MovePos(pt.x, pt.y);
}

int SWidget::GetWidth()
{
	return m_nWidth;
}
int SWidget::GetHeight()
{
	return m_nHeight;
}
void SWidget::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}
void SWidget::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}


RECT SWidget::GetRect()
{
	RECT rt;

	if (m_Wnd.GetWnd()){
		m_Wnd.GetWindowRect(&rt);
	}
	else{
		rt.left = m_nPosX;
		rt.top = m_nPosY;
		rt.right = m_nWidth + m_nPosX;
		rt.bottom = m_nHeight + m_nPosY;
	}

	return rt;
}
void SWidget::SetRect(RECT rt)
{
	m_nPosX = rt.left;
	m_nPosY = rt.top ;
	m_nWidth = rt.right - m_nPosX;
	m_nHeight = rt.bottom - m_nPosY;
}


BOOL SWidget::IsEnabled()
{
	return m_bEnabled;
}
void SWidget::SetEnabled(BOOL bEnabled)
{
	m_bEnabled = bEnabled;
}

BOOL SWidget::IsVisible()
{
	return m_bVisible;
}
void SWidget::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}


LPTSTR SWidget::GetTip()
{
	return m_szTip;
}
void SWidget::SetTip(LPTSTR str)
{
	lstrcpy(m_szTip, str);
}


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
	return m_Wnd.GetWnd() ? TRUE : FALSE;
}

void SWidget::SetRunning(BOOL bRunning)
{
	m_bIsRunning = bRunning;
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
BOOL SWidget::OnPreCreate()
{
	/* 默认所有的SWidget都是一个窗口类 */
	WNDCLASSEX wcApp;											//声明窗口类
	wcApp.cbSize = sizeof(wcApp);
	//给窗口属性赋值
	//wcApp.lpszClassName = TEXT("swidget");					//设置窗口类名(提供给CreateWindow()使用)
	wcApp.style = CS_HREDRAW;									//定义窗口风格
	wcApp.hInstance = m_hInstance;								//指定义窗口应用程序的句柄
	wcApp.cbWndExtra = 0;										//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	wcApp.cbClsExtra = 0;										//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	wcApp.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			//加载程序图标（大）
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（小）
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);				//加载鼠标样式
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW);				//设置窗口背景色
	wcApp.lpszMenuName = NULL;									//设置窗口没有菜单

	return Register(TEXT("swidget"), &wcApp);
}

//控件消息处理
LRESULT CALLBACK SWidget::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NCCREATE:
		//TODO:感觉此处的hWnd可能与Create()返回的hWnd不一致
		m_Wnd.SetWnd(hWnd);
		//NOTE:必须返回默认操作
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:				//程序销毁消息
		PostQuitMessage(0);			//DOUBT:不靠谱,并不是退出自身的,会造成接收不到WM_QUIT消息
		break;
	default:
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void SWidget::OnRun()
{
	MSG msg;											//定义消息结构

	/* 消息循环 */
	while (m_bIsRunning)
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
	Unsubclass(m_Wnd.GetWnd());									//解除绑定消息函数
	SApplication::GetApp()->DestroyWidget(this);				//通知主线程,线程结束
}
////////////

void SWidget::Run()
{
	if (Create()){
		ShowWindow();
		OnRun();
		OnRan();//出口
	}

}

//注册控件类
BOOL SWidget::Register(LPTSTR szName, WNDCLASSEX *wcApp)
{
	//注册窗口类
	if (szName){
		BOOL result = TRUE;
		if (wcApp){
			m_bSysClass = FALSE;
			SetParam((SMessageHandler *)this);		//设置参数,让消息顺序能正确执行到对象消息,必须带上类型
			wcApp->lpszClassName = szName;
			wcApp->lpfnWndProc = m_pWndProc;		//指定消息处理函数
			result = RegisterClassEx(wcApp);
		}
		else m_bSysClass = TRUE;

		SetClassName(szName);
		return TRUE;
	}
	else return FALSE;
}


//创建控件
BOOL SWidget::Create()
{
	//NOTE:用于注册控件类型
	if (!OnPreCreate())
		return FALSE;

	//IMPORTMENT:如果回调函数中没有对WM_NCCREATE消息进行处理会导致返回 NULL
	//TODO:m_szClassName与m_szTitle如果与其他控件重名会产生冲突
	//调用函数CreateWindow建立窗口

	HWND hWnd = ::CreateWindow(
		m_szClassName,								//窗口类注册名
		m_szTitle,									//设置窗口标题-必须唯一
		m_dwStyle,									//设置窗口风格
		m_nPosX,									//设置窗口左上角X坐标		
		m_nPosY,									//设置窗口左上角Y坐标	
		m_nWidth,									//设置窗口宽度
		m_nHeight,									//设置窗口高度
		m_parentWnd,								//父窗口句柄
		m_hMenu,									//菜单的句柄
		m_hInstance,								//程序实例句柄
		m_lpParam);									//传递给消息函数的指针

	if (!hWnd){										//如果窗口建立失败则返回FALSE
		::MessageBox(NULL, TEXT("注册窗口失败"), TEXT("error"), 0);
		SApplication::GetApp()->UnRegisterWidget(this);	//反注册
		return FALSE;
	}else{
		m_Wnd.SetWnd(hWnd);								//设置句柄

		//如果是自定义消息,则还必须注册到消息管理接收消息
		if (!m_bSysClass)
			Subclass(hWnd);

		return TRUE;
	}
	
}

//销毁控件
void SWidget::Destroy(){
	//销毁窗口
	DestroyWindow(m_Wnd.GetWnd());
}

//模态显示
int SWidget::DoModal()
{
	if (!IsCreated()){
		if (Create()){
			::EnableWindow(m_Wnd.GetParent(), FALSE);  //锁定父窗口

			ShowWindow();
			OnRun();
			OnRan();	//出口

			::EnableWindow(m_Wnd.GetParent(), TRUE);//释放父窗口
			HideWindow();//隐藏自己
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
