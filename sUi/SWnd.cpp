#include "SWnd.h"

SWnd::SWnd()
{
	m_hWnd = NULL;
}

SWnd::SWnd(HWND hWnd):
	m_hWnd(hWnd)
{

}

SWnd::~SWnd()
{

}

//获取控件句柄
HWND SWnd::GetHandle()
{
	return m_hWnd;
}
/* 设置控件句柄 */
void SWnd::SetHandle(HWND hWnd)
{
	m_hWnd = hWnd;
}

/////////////////
//获取设备上下文
HDC SWnd::GetDC()
{
	return ::GetDC(m_hWnd);

}

//返回hWnd参数所指定的窗口的设备环境--覆盖了整个窗口
HDC SWnd::GetWindowDC()
{
	return ::GetWindowDC(m_hWnd);
}

//释放设备上下文环境（DC）供其他应用程序使用
int SWnd::ReleaseDC(HDC hdc)
{
	return ::ReleaseDC(m_hWnd, hdc);
}
//////

DWORD SWnd::SetClassLong(int nlndex, LONG dwNewLong)
{
	return ::SetClassLong(m_hWnd, nlndex, dwNewLong);
}

DWORD SWnd::GetClassLong(int nlndex)
{
	return ::GetClassLong(m_hWnd, nlndex);
}

BOOL SWnd::SetWindowText(LPCTSTR lpString)
{
	return ::SetWindowText(m_hWnd, lpString);
}

int SWnd::GetWindowText(LPTSTR lpString, int nMaxCount)
{
	return ::GetWindowText(m_hWnd, lpString, nMaxCount);
}

LONG SWnd::SetWindowLong(int nIndex, LONG dwNewLong)
{
	return ::SetWindowLong(m_hWnd, nIndex, dwNewLong);
}

LONG SWnd::GetWindowLong(int nIndex)
{
	return ::GetWindowLong(m_hWnd, nIndex);
}


BOOL SWnd::GetWindowRect(LPRECT lpRect)
{
	return ::GetWindowRect(m_hWnd, lpRect);
}
RECT SWnd::GetWindowRect()
{
	RECT rt = { 0, 0, 0, 0 };
	GetWindowRect(&rt);
	return rt;
}

BOOL SWnd::GetClientRect(LPRECT lpRect)
{
	return ::GetClientRect(m_hWnd, lpRect);
}

BOOL SWnd::ScreenToClient(LPPOINT lpPoint)
{
	return ::ScreenToClient(m_hWnd, lpPoint);
}

//矩形的用户坐标转换成屏幕坐标
BOOL SWnd::ClientToScreen(LPPOINT lpPoint)
{
	return ::ScreenToClient(m_hWnd, lpPoint);
}

BOOL SWnd::SetWindowPos(HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	return ::SetWindowPos(m_hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL SWnd::MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
	return ::MoveWindow(m_hWnd, X, Y, nWidth, nHeight, bRepaint);
}


BOOL SWnd::SetForegroundWindow()
{
	return ::SetForegroundWindow(m_hWnd);
}

HWND SWnd::SetFocus()
{
	return ::SetFocus(m_hWnd);
}

BOOL SWnd::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(m_hWnd, nCmdShow);
}

BOOL SWnd::InvalidateRect(CONST RECT *lpRect, BOOL bErase)
{
	return ::InvalidateRect(m_hWnd, lpRect, bErase);
}

BOOL SWnd::UpdateWindow()
{
	return ::UpdateWindow(m_hWnd);
}

BOOL SWnd::RedrawWindow(CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT fuRedraw)
{
	return ::RedrawWindow(m_hWnd, lprcUpdate, hrgnUpdate, fuRedraw);
}


HDC SWnd::BeginPaint(LPPAINTSTRUCT lpPaint)
{
	return ::BeginPaint(m_hWnd, lpPaint);
}


BOOL SWnd::EndPaint(CONST PAINTSTRUCT *lpPaint)
{
	return ::EndPaint(m_hWnd, lpPaint);
}

HWND SWnd::SetParent(HWND parent)
{
	return ::SetParent(m_hWnd, parent);
}

HWND SWnd::GetParent()
{
	return ::GetParent(m_hWnd);
}

//遍历子控件
HWND SWnd::GetDlgItem(int nIDDDlgItem)
{
	return ::GetDlgItem(m_hWnd, nIDDDlgItem);
}

BOOL SWnd::SetDlgItemInt(int nIDDDlgItem, UINT uValue, BOOL bSigned)
{
	return ::SetDlgItemInt(m_hWnd, nIDDDlgItem, uValue, bSigned);
}

BOOL SWnd::SetDlgItemText(int nIDDDlgItem, LPCTSTR IpString)
{
	return ::SetDlgItemText(m_hWnd, nIDDDlgItem, IpString);
}

HWND SWnd::GetAncestor(UINT gaFlags)
{
	return ::GetAncestor(m_hWnd, gaFlags);
}

BOOL SWnd::EnableWindow(BOOL bEnable)
{
	return ::EnableWindow(m_hWnd, bEnable);
}

LRESULT SWnd::SendMessage( UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(m_hWnd, Msg, wParam, lParam);
}

BOOL SWnd::PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::PostMessage(m_hWnd, Msg, wParam, lParam);
}

BOOL SWnd::EnumChildWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	return ::EnumChildWindows(m_hWnd, lpEnumFunc, lParam);
}
BOOL SWnd::IsWindowVisible()
{
	return ::IsWindowVisible(m_hWnd);
}
