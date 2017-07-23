/*************************************
游戏引擎源文件 SWindow.cpp
*************************************/
#include "SWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//初始化静态变量	
int SWindow::s_winnum = 0;

void SWindow::Init()
{
	//NOTE:这里的ClassName不允许出现重复
	_stprintf_s(m_szClassName, TEXT("Win32%d"), s_winnum++);
	_stprintf_s(m_szTitle, TEXT("Win32%d"), s_winnum++);

	m_hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance(): ::GetModuleHandle(NULL);
	m_wIcon = NULL;
	m_wSmallIcon = NULL;
	m_bFullScreen = FALSE;
	m_nColorbit = 32;

	m_bIsRunning = TRUE;

	SApplication::GetApp()->RegisterWindow(this);
}

/* 窗口空构造函数 */
SWindow::SWindow(SWidget *parent) :
	SWidget(parent)
{
	Init();
	
}

SWindow::SWindow(LPTSTR szTitle) :
	SWidget(NULL)
{
	Init();
	_stprintf_s(m_szTitle, szTitle);

}

/* 窗口析构函数 */
SWindow::~SWindow()
{
	//TODO:只进行资源释放,不能反注册
	//TODO:线程结束不代表对被释放,
	SApplication::GetApp()->DestroyWindow(this);
}


void SWindow::SetAttribute(HINSTANCE hInstance, LPTSTR szClassName, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	m_hInstance = hInstance;						//设置引擎实例为当前程序实例句柄					

	lstrcpy(m_szClassName, szClassName);		//将窗口类注册名称赋给_szWindowClass
	lstrcpy(m_szTitle, szTitle);					//将标题赋给m_szTitle

	/* 设置屏幕模式和大小 */
	m_bFullScreen = bFullScreen;
	m_nColorbit = nColorbit;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	/*设置图标和光标*/
	m_wIcon = wIcon;
	m_wSmallIcon = wSmallIcon;

}

void SWindow::SetAttribute(LPTSTR szWindowClass, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		szWindowClass,
		szTitle,
		wIcon,
		wSmallIcon,
		bFullScreen,
		nColorbit,
		nWidth,
		nHeight);

}

void SWindow::SetAttribute(LPTSTR szWindowClass, LPTSTR szTitle ,int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		szWindowClass,
		szTitle,
		NULL,
		NULL,
		FALSE,
		32,
		nWidth,
		nHeight);

}

void SWindow::SetAttribute(LPTSTR szTitle, int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		m_szClassName,
		szTitle,
		NULL,
		NULL,
		FALSE,
		32,
		nWidth,
		nHeight);

}


long SWindow::SetCursorIcon(WORD wIcon){
	
	long lCur = (long)LoadCursor(GetInstance(), MAKEINTRESOURCE(wIcon));
	if (m_hWnd){
		::SetClassLong(m_hWnd, GCL_HCURSOR, lCur);
		return lCur;
	}
	return 0;
}


void SWindow::SetBigIcon(WORD wIcon)
{
	m_wIcon = wIcon;
}


void SWindow::SetSmallIcon(WORD wIcon)
{
	m_wSmallIcon = wIcon;
}


void SWindow::SetFullScreen(BOOL bFullScreen)
{
	m_bFullScreen = bFullScreen;
}


void SWindow::SetColorbit(int nColorbit)
{
	m_nColorbit = nColorbit;
}

void SWindow::SetWndProc(WNDPROC pWndProc)
{
	Subclass(m_hWnd);
	SetMessageProc(pWndProc);
	::SetWindowLong(m_hWnd, GWL_WNDPROC, (long)pWndProc);
}

void SWindow::SetRunning(BOOL bRunning)
{
	m_bIsRunning = bRunning;
}


/////
void SWindow::DoModal()
{
	if (!m_hWnd){
		if (Create()){
			Show();
			OnRun();
		}
	}
	else SWidget::Show(SW_SHOWNORMAL);
}

//显示控件
void SWindow::Show()
{
	Show(SW_SHOWNORMAL);
}
void SWindow::Show(int nCmdShow)
{
	if (!m_hWnd){
		Start();	//开启线程
	}
	else SWidget::Show(nCmdShow);
	
	return;

}

//隐藏控件
void SWindow::Hide()
{
	Show(SW_HIDE);
}

//////////////

LRESULT CALLBACK SWindow::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:					//窗口建立消息:CreateWindow函数请求创建窗口时发送此消息
		OnCreated();
		break;

	case WM_PAINT:					//窗口重绘消息
		OnPaint();
		break;

	case WM_KEYDOWN:				//按键消息  

		break;
	case WM_KEYUP:					//按键消息  

		break;

	case WM_LBUTTONDOWN:			//鼠标左键按下消息

		break;

	case WM_LBUTTONUP:				//鼠标左键弹起消息

		break;

	case WM_MOUSEWHEEL:				//鼠标滚轮事件

		break;

	case WM_LBUTTONDBLCLK:			//鼠标左键双击消息

		break;

	case WM_RBUTTONDOWN:			//鼠标右键按下消息

		break;
	case WM_RBUTTONUP:				//鼠标右键弹起消息

		break;

	case WM_MOUSEMOVE:				//鼠标移动消息

		break;

	case WM_SETFOCUS:				//游戏窗口得到焦点消息
		OnGetFocus();
		break;

	case WM_KILLFOCUS:				//游戏窗口失去焦点消息
		OnLostFocus();
		break;

	case WM_CLOSE:					//窗口关闭消息
		if (OnClose())				//窗口关闭前的处理
			DestroyWindow(hWnd);	//发出销毁窗口消息
		break;

	case WM_DESTROY:				//程序销毁消息
		OnDestory();
		PostQuitMessage(0);			//DOUBT:不靠谱,并不是退出自身的,会造成接收不到WM_QUIT消息
		break;
		//case	WM_SYSCOMMAND //系统菜单命令：最大化按钮，最小化按，复原按钮，关闭按钮;与用户菜单命令WM_COMMAND有区别哦

	default:
			//IMPORTMENT:此处的hWnd可能不为m_hWnd(对象未构造前会调用静态消息函数,此时m_hWnd==NULL),不应该对HWND封装,因为会变
		return DefWindowProc(hWnd, message, wParam, lParam);
	
	}
	return 0;
}

BOOL SWindow::OnCreate()
{
	WNDCLASSEX wcApp;							//声明窗口类
	wcApp.cbSize = sizeof(wcApp);

	//给窗口属性赋值
	wcApp.lpszClassName = m_szClassName;						//设置窗口类名
	wcApp.style = CS_HREDRAW;									//定义窗口风格
	wcApp.lpfnWndProc = m_pWndProc;								//指定消息处理函数
	wcApp.hInstance = m_hInstance;								//指定义窗口应用程序的句柄
	wcApp.cbWndExtra = 0;										//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	wcApp.cbClsExtra = 0;										//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	wcApp.hIconSm = m_wIcon?LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wIcon)):NULL;			//加载程序图标（大）
	wcApp.hIcon = m_wSmallIcon?LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wSmallIcon)):NULL;	//加载程序图标（小）
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);				//加载鼠标样式
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW);				//设置窗口背景色
	wcApp.lpszMenuName = NULL;									//设置窗口没有菜单
	
	//注册窗口类
	//DOUBT:没Create之前已经开始消息的发送,此时m_hWnd仍为空,所以必须找方法在RegisterClassEx()之前设置m_hWnd
	if (!RegisterClassEx(&wcApp))
		return FALSE;

	/*使用DEVMODE结构设置屏幕显示模式*/
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DevMode));					//将结构DevMode的内存清零
	DevMode.dmSize = sizeof(DevMode);						//设置DevMode存储空间以存储屏幕属性数据

	//用当前屏幕显示模式设置填充DevMode
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DevMode);

	BOOL bDisplayChange = FALSE;							//标识屏幕显示模式是否改变

	//如果屏幕显示模式位数与游戏不同
	if (DevMode.dmBitsPerPel != (unsigned long)m_nColorbit)
	{
		DevMode.dmBitsPerPel = m_nColorbit;					//设置显示模式位数
		bDisplayChange = TRUE;
	}

	//如果全屏状态下的屏幕尺寸与窗口不同；或屏幕尺寸小于窗口,都需要重设显示模式
	if ((m_bFullScreen && m_nWidth != ::GetSystemMetrics(SM_CXSCREEN))
		|| m_nWidth>GetSystemMetrics(SM_CXSCREEN))
	{
		DevMode.dmPelsWidth = m_nWidth;						//屏幕宽度
		DevMode.dmPelsHeight = m_nHeight;					//屏幕高度	
		bDisplayChange = TRUE;
	}

	//如果显示模式发生改变
	if (bDisplayChange)
	{
		LONG result = ::ChangeDisplaySettings(&DevMode, 0);	//动态修改屏幕显示模式	
		//判断修改显示模式是否成功
		if (result == DISP_CHANGE_SUCCESSFUL)
		{
			// 如果动态修改显示模式成功，则修改显示模式
			::ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN);
		}
		else
		{
			//如果动态修改显示模式失败，恢复原来的屏幕属性
			::ChangeDisplaySettings(NULL, 0);		//恢复原来的屏幕属性
			return FALSE;						//返回FALSE
		}
	}

	/* 判断窗口显示方式，并设置相应的窗口属性 */
	if (m_bFullScreen)
	{
		/* 全屏状态下 */
		//设置窗口左上角位置
		m_nPosX = 0;
		m_nPosY = 0;
		m_dwStyle = WS_POPUP;			//设置游戏窗口风格为无边框的弹出式窗口
	}
	else
	{
		/*非全屏状态下，窗口显示在屏幕中心*/
		//计算加上边框后的窗口大小
		m_nWidth = m_nWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		m_nHeight = m_nHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

		//计算在窗口居中时，窗口左上角的位置
		m_nPosX = (GetSystemMetrics(SM_CXSCREEN) - m_nWidth) / 2;
		m_nPosY = (GetSystemMetrics(SM_CYSCREEN) - m_nHeight) / 2;

		//设置游戏窗口风格为带标题栏和系统菜单和最小化的窗口
		m_dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	}

	m_nWidth += 10;
	m_nHeight += 8;

	BOOL lresult=SWidget::OnCreate();
	if (lresult)Subclass(m_hWnd);		//绑定消息函数
	return lresult;
}

//控件创建之后
BOOL SWindow::OnCreated()
{
	return FALSE;
}


void SWindow::OnRun()
{
	MSG msg;					//定义消息结构

	/* 消息循环 */
	while (m_bIsRunning)
	{
		//NOTE:这里不能填句柄,应该以线程为基准,否则服务获取不到消息
		if (PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))	//接收消息
		{
			if (msg.message == WM_QUIT)		//如果是退出消息，则退出循环
				break;

			TranslateMessage(&msg);			//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//处理消息
		}
		else
		{
			//DOUBT:这里没执行到,怎么回事???????
			//DOUBT:如果上面为PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE)则只有窗口关闭时才执行这里,但不在
			//窗口事件循环
			OnEvent();

		}
	}
	//销毁窗口
	Unsubclass(m_hWnd);									//解除绑定消息函数
	SApplication::GetApp()->QuitWindow(this);			//通知主线程,线程结束
}

void SWindow::OnEvent()
{
	//TODO:主要循环的事件:逻辑事件
}

void SWindow::OnPaint()
{
	//TODO:负责窗口绘制工作,并且绘制其下子控件

}

//关闭窗口
BOOL SWindow::OnClose()
{
	//DOUBT:这里的MessageBox无法正常显示,待解决
	/*
	if (MessageBox(NULL, TEXT("你确定要退出吗？"), TEXT("退出程序"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
		return FALSE;
	*/
	return TRUE;
}

//销毁窗口
void SWindow::OnDestory()
{
	//TODO:做销毁前最后的操作
	
}

//取得窗口焦点
void SWindow::OnGetFocus()
{

}

//失去焦点
void SWindow::OnLostFocus()
{

}


//创建控件
BOOL SWindow::Create(){
	if (!m_hWnd){
		if (!OnCreate()){
			MessageBox(NULL, TEXT("注册窗口失败"), TEXT("error"), 0);
			return FALSE;
		}
	}
	return TRUE;
	
}

void SWindow::Run(){
	if (Create()){
		Show();
		OnRun();
	}

}

//销毁控件
void  SWindow::Destroy(){
	
	
	return OnDestroy();
}
