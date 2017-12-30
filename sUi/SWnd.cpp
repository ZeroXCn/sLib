#include "SWnd.h"


SWnd::SWnd(HWND hWnd) :
SHandle(hWnd)
{

}

SWnd::~SWnd()
{

}

/////////////////
//获取设备上下文
HDC SWnd::GetDC()
{
	return ::GetDC(GetHandle());

}

//返回hWnd参数所指定的窗口的设备环境--覆盖了整个窗口
HDC SWnd::GetWindowDC()
{
	return ::GetWindowDC(GetHandle());
}

//释放设备上下文环境（DC）供其他应用程序使用
int SWnd::ReleaseDC(HDC hdc)
{
	return ::ReleaseDC(GetHandle(), hdc);
}
//////

DWORD SWnd::SetClassLong(int nlndex, LONG dwNewLong)
{
	return ::SetClassLong(GetHandle(), nlndex, dwNewLong);
}

DWORD SWnd::GetClassLong(int nlndex)
{
	return ::GetClassLong(GetHandle(), nlndex);
}

BOOL SWnd::SetWindowText(LPCTSTR lpString)
{
	return ::SetWindowText(GetHandle(), lpString);
}

int SWnd::GetWindowText(LPTSTR lpString, int nMaxCount)
{
	return ::GetWindowText(GetHandle(), lpString, nMaxCount);
}

LONG SWnd::SetWindowLong(int nIndex, LONG dwNewLong)
{
	return ::SetWindowLong(GetHandle(), nIndex, dwNewLong);
}

LONG SWnd::GetWindowLong(int nIndex)
{
	return ::GetWindowLong(GetHandle(), nIndex);
}


BOOL SWnd::GetWindowRect(LPRECT lpRect)
{
	return ::GetWindowRect(GetHandle(), lpRect);
}
RECT SWnd::GetWindowRect()
{
	RECT rt = { 0, 0, 0, 0 };
	GetWindowRect(&rt);
	return rt;
}

BOOL SWnd::GetClientRect(LPRECT lpRect)
{
	return ::GetClientRect(GetHandle(), lpRect);
}

BOOL SWnd::ScreenToClient(LPPOINT lpPoint)
{
	return ::ScreenToClient(GetHandle(), lpPoint);
}

//矩形的用户坐标转换成屏幕坐标
BOOL SWnd::ClientToScreen(LPPOINT lpPoint)
{
	return ::ScreenToClient(GetHandle(), lpPoint);
}

BOOL SWnd::SetWindowPos(HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	return ::SetWindowPos(GetHandle(), hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL SWnd::MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
	return ::MoveWindow(GetHandle(), X, Y, nWidth, nHeight, bRepaint);
}


BOOL SWnd::SetForegroundWindow()
{
	return ::SetForegroundWindow(GetHandle());
}

HWND SWnd::SetFocus()
{
	return ::SetFocus(GetHandle());
}

BOOL SWnd::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(GetHandle(), nCmdShow);
}

BOOL SWnd::InvalidateRect(CONST RECT *lpRect, BOOL bErase)
{
	return ::InvalidateRect(GetHandle(), lpRect, bErase);
}

BOOL SWnd::ValidateRect(CONST RECT *lpRect)
{
	return ::ValidateRect(GetHandle(), lpRect);
}

BOOL SWnd::UpdateWindow()
{
	return ::UpdateWindow(GetHandle());
}

BOOL SWnd::UpdateLayeredWindow(HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	return ::UpdateLayeredWindow(GetHandle(), hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
}

BOOL SWnd::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	return ::SetLayeredWindowAttributes(GetHandle(), crKey, bAlpha, dwFlags);
}

BOOL SWnd::RedrawWindow(CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT fuRedraw)
{
	return ::RedrawWindow(GetHandle(), lprcUpdate, hrgnUpdate, fuRedraw);
}


HDC SWnd::BeginPaint(LPPAINTSTRUCT lpPaint)
{
	return ::BeginPaint(GetHandle(), lpPaint);
}


BOOL SWnd::EndPaint(CONST PAINTSTRUCT *lpPaint)
{
	return ::EndPaint(GetHandle(), lpPaint);
}

HWND SWnd::SetParent(HWND parent)
{
	return ::SetParent(GetHandle(), parent);
}

HWND SWnd::GetParent()
{
	return ::GetParent(GetHandle());
}

//遍历子控件
HWND SWnd::GetDlgItem(int nIDDDlgItem)
{
	return ::GetDlgItem(GetHandle(), nIDDDlgItem);
}

BOOL SWnd::SetDlgItemInt(int nIDDDlgItem, UINT uValue, BOOL bSigned)
{
	return ::SetDlgItemInt(GetHandle(), nIDDDlgItem, uValue, bSigned);
}

BOOL SWnd::SetDlgItemText(int nIDDDlgItem, LPCTSTR IpString)
{
	return ::SetDlgItemText(GetHandle(), nIDDDlgItem, IpString);
}

HWND SWnd::GetAncestor(UINT gaFlags)
{
	return ::GetAncestor(GetHandle(), gaFlags);
}

BOOL SWnd::EnableWindow(BOOL bEnable)
{
	return ::EnableWindow(GetHandle(), bEnable);
}

LRESULT SWnd::SendMessage( UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(GetHandle(), Msg, wParam, lParam);
}

BOOL SWnd::PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::PostMessage(GetHandle(), Msg, wParam, lParam);
}

BOOL SWnd::EnumChildWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	return ::EnumChildWindows(GetHandle(), lpEnumFunc, lParam);
}
BOOL SWnd::IsWindowVisible()
{
	return ::IsWindowVisible(GetHandle());
}

//设置新菜单
BOOL SWnd::SetMenu(HMENU hMenu)
{
	return ::SetMenu(GetHandle(), hMenu);
}

//取得菜单
HMENU SWnd::GetMenu()
{
	return ::GetMenu(GetHandle());
}

HMENU SWnd::GetSystemMenu(BOOL bRevert)
{
	return ::GetSystemMenu(GetHandle(), bRevert);
}

BOOL SWnd::GetMenuItemRect(HMENU hMenu, UINT uItem, LPRECT lprcItem)
{
	return ::GetMenuItemRect(GetHandle(), hMenu, uItem, lprcItem);
}
BOOL SWnd::GetMenuItemRect(UINT uItem, LPRECT lprcItem)
{
	return ::GetMenuItemRect(GetHandle(), GetMenu(), uItem, lprcItem);
}

BOOL SWnd::HiliteMenuItem(HMENU hmenu, UINT  uItemHilite, UINT  uHilite)
{
	return ::HiliteMenuItem(GetHandle(), hmenu, uItemHilite, uHilite);
}
BOOL SWnd::HiliteMenuItem(UINT  uItemHilite, UINT  uHilite)
{
	return ::HiliteMenuItem(GetHandle(), GetMenu(), uItemHilite, uHilite);
}

//获取某点除的菜单项
int SWnd::MenuItemFromPoint(HMENU hMenu, POINT ptScreen)
{
	return ::MenuItemFromPoint(GetHandle(), hMenu, ptScreen);
}
int SWnd::MenuItemFromPoint(POINT ptScreen)
{
	return ::MenuItemFromPoint(GetHandle(), GetMenu(), ptScreen);
}

UINT_PTR SWnd::SetTimer(UINT_PTR nIDEvent, UINT nElapse, TIMERPROC lpTimerFunc)
{
	return ::SetTimer(GetHandle(), nIDEvent, nElapse, lpTimerFunc);
}
BOOL SWnd::KillTimer(UINT_PTR nIDEvent)
{
	return ::KillTimer(GetHandle(), nIDEvent);
}


//是否是最大化/最下化的窗口
BOOL SWnd::IsZoomed()
{
	return ::IsZoomed(GetHandle());

}
BOOL SWnd::IsIconic()
{
	return ::IsIconic(GetHandle());
}