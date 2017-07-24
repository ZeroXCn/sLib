#include "SGraphics.h"
///////////////
HDC SGraphics::BeginPaint(LPPAINTSTRUCT lpPaint)
{
	return ::BeginPaint(m_hWnd, lpPaint);
}

BOOL SGraphics::EndPaint(PAINTSTRUCT *lpPaint)
{
	return ::EndPaint(m_hWnd, lpPaint);
}
/////////////////
BOOL SGraphics::DrawPoint(int x, int y, COLORREF color)
{
	return ::SetPixel(m_hDC, x, y, color);
}

void SGraphics::DrawLine(int x1, int y1, int x2, int y2)
{
	/*
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	HPEN hPenOld;
	hdc = BeginPaint(hWnd, &ps);
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, 20, 10, NULL);
	LineTo(hdc, 200, 100);
	SelectObject(hdc, hPenOld);
	DeleteObject(hdc);
	EndPaint(hWnd, &ps);
	*/

	//最后一个参数是传出参数,存放上一个点的位置
	::MoveToEx(m_hDC, x1, y1, (LPPOINT)NULL);
	::LineTo(m_hDC, x2, y2);

}

void SGraphics::DrawTringle(POINT a, POINT b, POINT c)
{
	::MoveToEx(m_hDC, a.x, a.y, (LPPOINT)NULL);
	::LineTo(m_hDC, b.x, b.y);
	::LineTo(m_hDC, c.x, c.y);
	::LineTo(m_hDC, a.x, a.y);
}

BOOL SGraphics::DrawRect(int left, int top, int right, int bottom)
{

	return ::Rectangle(m_hDC, left, top, right, bottom);
}

BOOL SGraphics::FrameRect(int left, int top, int right, int bottom, HBRUSH hbr)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;

	return ::FrameRect(m_hDC, &temp, (hbr ? hbr : ::CreateSolidBrush(BLACK_COLOR)));
	
}

//填充矩形
BOOL SGraphics::FillRect(int left, int top, int right, int bottom, HBRUSH hbr)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;

	return ::FillRect(m_hDC, &temp, (hbr ? hbr : ::CreateSolidBrush(BLACK_COLOR)));
}

BOOL SGraphics::RoundRect(int left, int top, int right, int bottom, int width, int height)
{
	return ::RoundRect(m_hDC, left, top, right, bottom, width, height);
}

BOOL SGraphics::InvertRect(int left, int top, int right, int bottom)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	return ::InvertRect(m_hDC, &temp);
}

BOOL SGraphics::DrawRadius(int x, int y, int radius)
{
	return Ellipse(m_hDC, x - radius, y - radius, x + radius, y + radius);
}

BOOL SGraphics::DrawEllipse(int left, int top, int right, int bottom)
{
	return Ellipse(m_hDC, left, top, right, bottom);
}


//画圆饼扇区
BOOL SGraphics::DrawPie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2)
{
	return ::Pie(m_hDC, left, top, right, bottom, xr1, yr1, xr2, yr2);
}

//
BOOL SGraphics::DrawChord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	return ::Chord(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
}

BOOL SGraphics::DrawPolygon(POINT *apt, int cpt)
{
	return ::Polygon(m_hDC, apt, cpt);
}

//绘制同时绘制多个封闭的多边形。
BOOL SGraphics::DrawPolyPolygon(POINT *apt, int *asz, int csz)
{
	return ::PolyPolygon(m_hDC, apt, asz, csz);
}
BOOL SGraphics::GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode)
{
	return ::GradientFill(m_hDC, pVertex, dwNumVertex, pMesh, dwNumMesh, dwMode);
}

BOOL(SGraphics::DrawText)(LPTSTR lpchText, int cchText, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, lpchText, cchText, &rt, format);
}

BOOL SGraphics::DrawString(SString str, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);
}

BOOL SGraphics::DrawImage()
{
	return TRUE;
}