#include "SWidget.h"

SWidget::SWidget(SWidget *parent)
{
	m_pParent = parent;

	m_hInstance = (HINSTANCE)GetWindowLong(NULL, GWL_HINSTANCE);//GetModuleHandle(NULL);  
	//m_hInstance = SApplication::GetApp()->GetInstance();

	m_hMenu = NULL;
	m_lpParam = NULL;

	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 480;
	m_nHeight = 480;
	m_bEnabled = TRUE;
	m_bVisible = TRUE;

	lstrcpy(m_szClassName, TEXT("Widget"));
	lstrcpy(m_szTitle, TEXT("Widget"));
	lstrcpy(m_szTip, TEXT(""));

}
SWidget::~SWidget()
{
	
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
		dc.SetDc(m_Wnd.GetDC());
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
////////////////////////
//显示控件
void SWidget::Show()
{
	Show(SW_SHOWNORMAL);
}
void SWidget::Show(int nCmdShow)
{
	m_Wnd.ShowWindow( nCmdShow);	//显示控件
}

//隐藏控件
void SWidget::Hide()
{
	Show(SW_HIDE);
}

//更新控件
void SWidget::Update()
{
	if (m_Wnd.GetWnd())
	{
		m_Wnd.InvalidateRect( NULL, FALSE);	//更新区域添加一个矩形为整个窗体,不要擦掉背景
		m_Wnd.UpdateWindow();					//强制刷新窗口
	}
}
void SWidget::Update(int left, int top, int right, int bottom)
{
	if (m_Wnd.GetWnd())
	{
		RECT temp;
		temp.left = left;
		temp.top = top;
		temp.right = right;
		temp.bottom = bottom;
		m_Wnd.InvalidateRect(&temp, FALSE);	//更新区域添加一个矩形,不要擦掉背景
		m_Wnd.UpdateWindow();					//强制刷新窗口,
	}
}

//重绘控件
void SWidget::RePaint()
{

	if (m_Wnd.GetWnd())
	{
		m_Wnd.InvalidateRect(NULL, FALSE);	//强制刷新窗口,不要擦掉背景
		m_Wnd.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:关于这个函数理解不是很好
	}
	
}


//创建控件
BOOL SWidget::Create()
{
	//IMPORTMENT:如果回调函数中没有对WM_NCCREATE消息进行处理会导致返回 NULL
	//TODO:m_szClassName与m_szTitle如果与其他控件重名会产生冲突
	//调用函数CreateWindow建立窗口
	HWND hWnd = ::CreateWindow(
		m_szClassName,								//窗口类注册名
		m_szTitle,									//设置窗口标题-必须唯一
		m_dwStyle,									//设置窗口风格
		m_nPosX,									//设置窗口左上角X坐标		
		m_nPosY,									//设置窗口左上角Y坐标	
		m_nWidth,									//设置窗口宽度 + 10是为了与实际大小一致
		m_nHeight,									//设置窗口高度 + 8原因同上
		m_pParent ? m_pParent->GetWnd().GetWnd() : NULL,		//父窗口句柄
		m_hMenu,									//菜单的句柄
		m_hInstance,								//程序实例句柄
		m_lpParam);									//传递给消息函数的指针

	if (!hWnd){									//如果窗口建立失败则返回FALSE
		return FALSE;
	}

	m_Wnd.SetWnd(hWnd);


	Update();										//发送重绘消息

	return TRUE;
}

//销毁控件
void SWidget::Destroy(){
	//TODO:容我想想该写写什么...
}