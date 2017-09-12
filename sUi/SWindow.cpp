/*************************************
游戏引擎源文件 SWindow.cpp
*************************************/
#include "SWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 窗口空构造函数 */
SWindow::SWindow(SWidget *parent, LPTSTR name) :
	SWidget(parent)
{
	GetWndClassEx()->lpszClassName = TEXT("swindow");						//所注册的类
	GetWndClassEx()->style =CS_HREDRAW | CS_VREDRAW				;			//定义窗口风格(游戏中不应该采用CS_DBLCLKS样式)
	GetWndClassEx()->hIcon = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（大）
	GetWndClassEx()->hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//加载程序图标（小）
	GetWndClassEx()->hCursor = LoadCursor(NULL, IDC_ARROW);					//加载鼠标样式
	GetWndClassEx()->hbrBackground = (HBRUSH)(COLOR_WINDOW);				//设置窗口背景色
	GetWndClassEx()->lpszMenuName = NULL;									//设置窗口没有菜单


	//NOTE:这里的m_szTitle不允许出现重复,因为按标题查找可能会查到多个窗口
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;		//所用窗口类
	GetWindowAttribute()->lpWindowName = name;								//窗口标题
	GetWindowAttribute()->dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;//窗口风格
	GetWindowAttribute()->nWidth = 800;										//窗口宽度
	GetWindowAttribute()->nHeight = 600;									//窗口高度

	/*非全屏状态下，窗口显示在屏幕中心*/
	//计算加上边框后的窗口大小
	int nWidth = GetWindowAttribute()->nWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int nHeight = GetWindowAttribute()->nHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//计算在窗口居中时，窗口左上角的位置
	GetWindowAttribute()->nPosX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
	GetWindowAttribute()->nPosY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;

	m_bFullScreen = FALSE;
	m_nColorbit = 32;
	m_pInputEvent = (SWindowInputEvent *) this;
	m_pActivityEvent = (SWindowActivityEvent *) this;

}

/* 窗口析构函数 */
SWindow::~SWindow()
{
	SApplication::GetApp()->DestroyWidget(this);
}

void SWindow::SetAttribute(LPTSTR szTitle, HICON hIcon, HICON hSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	//将标题赋给m_szTitle
	GetWindowAttribute()->lpWindowName = szTitle;

	/* 设置屏幕模式和大小 */
	SetFullScreen(bFullScreen);
	SetColorbit(nColorbit);
	GetWindowAttribute()->nWidth = nWidth;
	GetWindowAttribute()->nHeight = nHeight;

	/*设置图标和光标*/
	GetWndClassEx()->hIcon = hIcon;
	GetWndClassEx()->hIconSm = hSmallIcon;

}

void SWindow::SetAttribute(LPTSTR szTitle, int nWidth, int nHeight)
{
	SetAttribute(
		szTitle,
		GetWndClassEx()->hIcon,
		GetWndClassEx()->hIconSm,
		m_bFullScreen,
		m_nColorbit,
		nWidth,
		nHeight);

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

int SWindow::HideCursor()
{
	return ::ShowCursor(FALSE);
}

/* 限制释放鼠标移动范围 */
RECT SWindow::GetClipCursor()
{
	RECT rt;
	::GetClipCursor(&rt);
	return rt;
}
void SWindow::ClipCursor(const RECT *rt)
{
	::ClipCursor(rt);
}
void SWindow::FreeCursor()
{
	::ClipCursor(NULL);
}

/* 取得鼠标绝对位置 */
POINT SWindow::GetCursorPos()
{
	POINT pt;
	::GetCursorPos(&pt);
	return pt;
}
void SWindow::SetCursorPos(POINT pt)
{
	::SetCursorPos(pt.x,pt.y);
}

void SWindow::RePaint()
{
	SWidget::UpdateWindow();
}

//////////////
//设置窗口活动
void SWindow::SetWindowInputEvent(SWindowInputEvent *pEvent)
{
	/* TODO:会造成内存泄漏,由用户自己判断释放 */
	m_pInputEvent = pEvent;
}

//设置窗口输入事件
void SWindow::SetWindowActivityEvent(SWindowActivityEvent *pEvent)
{
	/* TODO:会造成内存泄漏,由用户自己判断释放 */
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



LRESULT CALLBACK SWindow::OnProc(MessageParam param)
{
	SWindowActivityEvent::ActivityParam acParam(param.hWnd, param.uMsg, param.wParam, param.lParam);
	SWindowInputEvent::InputParam inParam(param.hWnd, param.uMsg, param.wParam, param.lParam);

	//TODO:相同参数的临时变量数量过多,会影响速度-最好采用指针或者引用

	switch (param.uMsg)
	{
	case WM_PAINT:					//窗口重绘消息
		m_pActivityEvent->OnPaint(acParam);
		break;

	case WM_TIMER:
		m_pActivityEvent->OnTimer(acParam);
		break;

	case WM_COMMAND:
		m_pActivityEvent->OnCommand(acParam);
		break;

	case WM_SIZE:
		m_pActivityEvent->OnSize(acParam);
		break;
////////////////
	case WM_KEYDOWN:				//按键消息  
		m_pInputEvent->OnKeyDown(inParam);
		break;
	case WM_KEYUP:					//按键消息  
		m_pInputEvent->OnKeyUp(inParam);
		break;

	case WM_LBUTTONDOWN:			//鼠标左键按下消息
		m_pInputEvent->OnMouseLButtonDown(inParam);
		break;

	case WM_LBUTTONUP:				//鼠标左键弹起消息
		m_pInputEvent->OnMouseLButtonUp(inParam);
		break;

	case WM_MOUSEWHEEL:				//鼠标滚轮事件
		m_pInputEvent->OnMouseWheel(inParam);
		break;

	case WM_LBUTTONDBLCLK:			//鼠标左键双击消息
		m_pInputEvent->OnMouseDoubleClick(inParam);
		break;

	case WM_RBUTTONDOWN:			//鼠标右键按下消息
		m_pInputEvent->OnMouseRButtonDown(inParam);
		break;
	case WM_RBUTTONUP:				//鼠标右键弹起消息
		m_pInputEvent->OnMouseLButtonUp(inParam);
		break;

	case WM_MOUSEMOVE:				//鼠标移动消息
		m_pInputEvent->OnMouseMove(inParam);
		break;

	case WM_SETFOCUS:				//游戏窗口得到焦点消息
		m_pActivityEvent->OnGetFocus(acParam);
		break;

	case WM_KILLFOCUS:				//游戏窗口失去焦点消息
		m_pActivityEvent->OnLostFocus(acParam);
		break;

	case WM_CLOSE:					//窗口关闭消息
		if (m_pActivityEvent->OnClose(acParam))				//窗口关闭前的处理
			::DestroyWindow(param.hWnd);	//发出销毁窗口消息
		break;

	case WM_DESTROY:				//程序销毁消息
		m_pActivityEvent->OnDestory(acParam);
		//TODO:此消息发送时,要求只退出子窗口而不影响父窗口
		::PostQuitMessage(0);			//DOUBT:不靠谱,并不是退出自身的,会造成接收不到WM_QUIT消息
		break;
		//case	WM_SYSCOMMAND //系统菜单命令：最大化按钮，最小化按，复原按钮，关闭按钮;与用户菜单命令WM_COMMAND有区别哦

	default:
		//调用父类的函数处理
		return SWidget::OnProc(param);
	
	}
	return 0;
}
BOOL SWindow::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	int &nPosX = lpWinAttribute->nPosX;
	int &nPosY = lpWinAttribute->nPosY;
	int &nWidth = lpWinAttribute->nWidth;
	int &nHeight = lpWinAttribute->nHeight;
	DWORD &dwStyle = lpWinAttribute->dwStyle;

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
	if ((m_bFullScreen && nWidth != ::GetSystemMetrics(SM_CXSCREEN))
		|| nWidth>GetSystemMetrics(SM_CXSCREEN))
	{
		DevMode.dmPelsWidth = nWidth;						//屏幕宽度
		DevMode.dmPelsHeight = nHeight;					//屏幕高度	
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
			::ChangeDisplaySettings(NULL, 0);	//恢复原来的屏幕属性
			return FALSE;						//返回FALSE
		}
	}

	/* 判断窗口显示方式，并设置相应的窗口属性 */
	if (m_bFullScreen)
	{
		/* 全屏状态下 */
		//设置窗口左上角位置
		nPosX = 0;
		nPosY = 0;
		dwStyle = WS_POPUP;			//设置游戏窗口风格为无边框的弹出式窗口

	}
	
	return TRUE;
}

BOOL SWindow::OnCreate(MessageParam param)
{
	return m_pActivityEvent->OnCreate(SWindowActivityEvent::ActivityParam(param.hWnd, param.uMsg, param.wParam, param.lParam));
}


BOOL SWindow::OnAftCreate(SWnd sWnd)
{
	if (!sWnd.GetHandle()){
		::MessageBox(NULL, TEXT("注册窗口失败"), TEXT("error"), 0);
		return FALSE;
	}
	return TRUE;

}

//
void SWindow::OnRunning()
{
	m_pActivityEvent->OnEvent();
	SWidget::OnRunning();
}

