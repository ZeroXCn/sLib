/*************************************
游戏引擎源文件 SWindow.cpp
*************************************/
#include "SWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 窗口空构造函数 */
SWindow::SWindow(LPTSTR name, SWidget *parent) :
	SWidget(parent)
{
	//NOTE:这里的m_szTitle不允许出现重复,因为按标题查找可能会查到多个窗口

	_stprintf_s(m_szTitle, name);

	//NOTO:仅当加载 WIN 预设图标时 Instance 为NULL
	m_hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_hSmallIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_hCursor = LoadCursor(NULL, IDC_ARROW);

	m_bFullScreen = FALSE;
	m_nColorbit = 32;

	m_pInputEvent = (SWindowInputEvent *) this;
	m_pActivityEvent = (SWindowActivityEvent *) this;
	
	SApplication::GetApp()->RegisterWidget(this);

}

/* 窗口析构函数 */
SWindow::~SWindow()
{

	SApplication::GetApp()->DestroyWidget(this);
}

void SWindow::SetAttribute(LPTSTR szTitle, HICON hIcon, HICON hSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	//将标题赋给m_szTitle
	SetTitle(szTitle);					

	/* 设置屏幕模式和大小 */
	SetFullScreen(bFullScreen);
	SetWidth(nWidth);
	SetHeight(nHeight);

	/*设置图标和光标*/
	SetBigIcon(hIcon);
	SetSmallIcon(hSmallIcon);

}

void SWindow::SetAttribute(LPTSTR szTitle, int nWidth, int nHeight)
{
	SetAttribute(
		szTitle,
		m_hIcon,
		m_hSmallIcon,
		m_bFullScreen,
		m_nColorbit,
		nWidth,
		nHeight);

}


long SWindow::SetCursorIcon(HCURSOR hIcon){
	
	long lCur = (long)hIcon;
	if (m_Wnd.GetWnd()){
		m_Wnd.SetClassLong(GCL_HCURSOR, lCur);
		return lCur;
	}
	else m_hCursor = hIcon;
	return 0;
}


void SWindow::SetBigIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}


void SWindow::SetSmallIcon(HICON hIcon)
{
	m_hSmallIcon = hIcon;
}


void SWindow::SetFullScreen(BOOL bFullScreen)
{
	m_bFullScreen = bFullScreen;
}


void SWindow::SetColorbit(int nColorbit)
{
	m_nColorbit = nColorbit;
}
////////////////
/* 显示鼠标 */
int SWindow::ShowCursor(BOOL bShow)
{
	return ::ShowCursor(bShow);
}
void SWindow::RePaint()
{
	SWidget::UpdateWindow();
}

//////////////
//设置窗口活动
void SWindow::SetWindowInputEvent(SWindowInputEvent *pEvent)
{
	m_pInputEvent = pEvent;
}

//设置窗口输入事件
void SWindow::SetWindowActivityEvent(SWindowActivityEvent *pEvent)
{
	m_pActivityEvent = pEvent;
}

//取得窗口活动
SWindowInputEvent *SWindow::GetWindowInputEvent()
{
	return m_pInputEvent;
}

//取得窗口输入事件
SWindowActivityEvent *SWindow::GetWindowActivityEvent()
{
	return m_pActivityEvent;
}



LRESULT CALLBACK SWindow::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;					//定义，无初始化,由BeginPaint初始化
	SDc dc;
	SWindowActivityEvent::ActivityParam acParam(hWnd, message, wParam, lParam);
	SWindowInputEvent::InputParam inParam(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_CREATE:					//窗口建立消息:CreateWindow函数请求创建窗口时发送此消息
		m_pActivityEvent->OnCreate(acParam);
		break;

	case WM_PAINT:					//窗口重绘消息
		//NOTE:不写BeginPaint程序将会进入死循环,一直处理一个接一个的WM_PAINT消息
		dc.SetDC(m_Wnd.BeginPaint(&ps));

		//TODO:负责窗口绘制工作,并且绘制其下子控件
		m_pActivityEvent->OnPaint(dc);

		m_Wnd.EndPaint(&ps);

		break;
	case WM_COMMAND:
		m_pActivityEvent->OnCommand(hWnd, message, wParam, lParam);
		break;

	case WM_KEYDOWN:				//按键消息  
		m_pInputEvent->OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:					//按键消息  
		m_pInputEvent->OnKeyUp(hWnd, wParam);
		break;

	case WM_LBUTTONDOWN:			//鼠标左键按下消息
		m_pInputEvent->OnMouseLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_LBUTTONUP:				//鼠标左键弹起消息
		m_pInputEvent->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEWHEEL:				//鼠标滚轮事件
		m_pInputEvent->OnMouseWheel(hWnd, wParam);
		break;

	case WM_LBUTTONDBLCLK:			//鼠标左键双击消息
		m_pInputEvent->OnMouseDoubleClick(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_RBUTTONDOWN:			//鼠标右键按下消息
		m_pInputEvent->OnMouseRButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;
	case WM_RBUTTONUP:				//鼠标右键弹起消息
		m_pInputEvent->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEMOVE:				//鼠标移动消息
		m_pInputEvent->OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_SETFOCUS:				//游戏窗口得到焦点消息
		m_pActivityEvent->OnGetFocus(acParam);
		break;

	case WM_KILLFOCUS:				//游戏窗口失去焦点消息
		m_pActivityEvent->OnLostFocus(acParam);
		break;

	case WM_CLOSE:					//窗口关闭消息
		if (m_pActivityEvent->OnClose(acParam))				//窗口关闭前的处理
			DestroyWindow(hWnd);	//发出销毁窗口消息
		break;

	case WM_DESTROY:				//程序销毁消息
		m_pActivityEvent->OnDestory(acParam);
		PostQuitMessage(0);			//DOUBT:不靠谱,并不是退出自身的,会造成接收不到WM_QUIT消息
		break;
		//case	WM_SYSCOMMAND //系统菜单命令：最大化按钮，最小化按，复原按钮，关闭按钮;与用户菜单命令WM_COMMAND有区别哦

	default:
		//调用父类的函数处理
		return SWidget::OnProc(hWnd, message, wParam, lParam);
	
	}
	return 0;
}
BOOL SWindow::OnPreCreate()
{
	WNDCLASSEX wcApp;											//声明窗口类
	//给窗口属性赋值
	wcApp.cbSize = sizeof(wcApp);
	wcApp.style = CS_HREDRAW;									//定义窗口风格
	wcApp.lpfnWndProc = m_pWndProc;								//指定消息处理函数
	wcApp.hInstance = m_hInstance;								//指定义窗口应用程序的句柄
	wcApp.cbWndExtra = 0;										//指向窗口过程函数的指针. 可以使用 CallWindowProc函数调用窗口过程.
	wcApp.cbClsExtra = 0;										//指定紧跟在类之后的附加内存空间的字节数. 系统初始化为0.
	wcApp.hIconSm = m_hIcon;									//加载程序图标（大）
	wcApp.hIcon = m_hSmallIcon;									//加载程序图标（小）
	wcApp.hCursor = m_hCursor;									//加载鼠标样式
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW);				//设置窗口背景色
	wcApp.lpszMenuName = NULL;									//设置窗口没有菜单

	//注册窗口类
	return SWidget::Register(TEXT("swindow"), &wcApp);
}

void SWindow::OnRunning()
{
	m_pActivityEvent->OnEvent();
	SWidget::OnRunning();
}

void SWindow::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//TODO:处理子控件消息
	//事件交由子控件自身处理

		
}

////////////////////////

//创建控件
BOOL SWindow::Create()
{
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

	return SWidget::Create();
	
}

