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

/* 设置控件句柄 */
void SWnd::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

//获取控件句柄
HWND SWnd::GetWnd()
{
	return m_hWnd;
}

//获取设备上下文
HDC SWnd::GetDC()
{
	return ::GetDC(m_hWnd);

}
//////

DWORD SWnd::SetClassLong(int nlndex, LONG dwNewLong)
{
	return ::SetClassLong(m_hWnd, nlndex, dwNewLong);
}

BOOL SWnd::SetWindowText(LPCTSTR lpString)
{
	return ::SetWindowText(m_hWnd, lpString);
}

int SWnd::GetWindowText(LPTSTR lpString, int nMaxCount)
{
	return ::GetWindowText(m_hWnd, lpString, nMaxCount);
}

LONG SWnd::SetWindowLong(int nlndex, LONG dwNewLong)
{
	return ::SetWindowLong(m_hWnd, nlndex, dwNewLong);
}

BOOL SWnd::GetWindowRect(LPRECT lpRect)
{
	return ::GetWindowRect(m_hWnd, lpRect);
}

BOOL SWnd::ScreenToClient(LPPOINT lpPoint)
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