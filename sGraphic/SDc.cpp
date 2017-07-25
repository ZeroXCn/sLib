#include "SDc.h"
#include "../sCore/SDebug.h"
SDc::SDc():
	m_hDC(NULL)
{

}
SDc::SDc(HDC hDC):
	m_hDC(hDC)
{

}


SDc::~SDc()
{

}
///////////////////
//设置绘图上下文
void SDc::SetDc(HDC hDC)
{
	m_hDC = hDC;
}

//取得当前绘图上下文
HDC SDc::GetDc()
{
	return m_hDC;
}
///////////////////
HGDIOBJ SDc::SelectObject(HGDIOBJ hgdiobj)
{
	return ::SelectObject(m_hDC, hgdiobj);
}

SGdiObject SDc::SelectObject(SGdiObject Obj)
{
	return SGdiObject(::SelectObject(m_hDC, Obj.GetObject()));
}


BOOL SDc::DeleteObject(HGDIOBJ hObject)
{
	return ::DeleteObject(hObject);
}

BOOL SDc::DeleteObject(SGdiObject Obj)
{
	return ::DeleteObject(Obj.GetObject());
}
/////////////////
//设置文本颜色
COLORREF SDc::SetTextColor(COLORREF crColor)
{
	return ::SetTextColor(m_hDC, crColor);

}


//设置背景色
COLORREF SDc::SetBkColor(COLORREF color)
{
	return ::SetBkColor(m_hDC, color);
}

///////////////
BOOL SDc::DrawPoint(int x, int y, COLORREF color)
{
	return ::SetPixel(m_hDC, x, y, color);
}

void SDc::DrawLine(int x1, int y1, int x2, int y2)
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

void SDc::DrawTringle(POINT a, POINT b, POINT c)
{
	::MoveToEx(m_hDC, a.x, a.y, (LPPOINT)NULL);
	::LineTo(m_hDC, b.x, b.y);
	::LineTo(m_hDC, c.x, c.y);
	::LineTo(m_hDC, a.x, a.y);
}

BOOL SDc::DrawRect(int left, int top, int right, int bottom)
{

	return ::Rectangle(m_hDC, left, top, right, bottom);
}

BOOL SDc::FrameRect(int left, int top, int right, int bottom, HBRUSH hbr)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;

	return ::FrameRect(m_hDC, &temp, (hbr ? hbr : ::CreateSolidBrush(BLACK_COLOR)));

}

//填充矩形
BOOL SDc::FillRect(int left, int top, int right, int bottom, HBRUSH hbr)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;

	return ::FillRect(m_hDC, &temp, (hbr ? hbr : ::CreateSolidBrush(BLACK_COLOR)));
}

BOOL SDc::RoundRect(int left, int top, int right, int bottom, int width, int height)
{
	return ::RoundRect(m_hDC, left, top, right, bottom, width, height);
}

BOOL SDc::InvertRect(int left, int top, int right, int bottom)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	return ::InvertRect(m_hDC, &temp);
}

BOOL SDc::DrawRadius(int x, int y, int radius)
{
	return Ellipse(m_hDC, x - radius, y - radius, x + radius, y + radius);
}

BOOL SDc::DrawEllipse(int left, int top, int right, int bottom)
{
	return Ellipse(m_hDC, left, top, right, bottom);
}


//画圆饼扇区
BOOL SDc::DrawPie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2)
{
	return ::Pie(m_hDC, left, top, right, bottom, xr1, yr1, xr2, yr2);
}

//
BOOL SDc::DrawChord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	return ::Chord(m_hDC, x1, y1, x2, y2, x3, y3, x4, y4);
}

BOOL SDc::DrawPolygon(POINT *apt, int cpt)
{
	return ::Polygon(m_hDC, apt, cpt);
}

//绘制同时绘制多个封闭的多边形。
BOOL SDc::DrawPolyPolygon(POINT *apt, int *asz, int csz)
{
	return ::PolyPolygon(m_hDC, apt, asz, csz);
}
/*
BOOL SDc::GradientFill(CONST PTRIVERTEX pVertex, ULONG uVertex, CONST PVOID pMesh, ULONG nMesh, ULONG ulMode)
{
	return ::GradientFill(m_hDC, pVertex, uVertex, pMesh, nMesh, ulMode);
}
*/

BOOL SDc::DrawString(SString str, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);					//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbm);	//将位图选入兼容设备，并记录下旧的句柄
	//输出不透明位图
	::BitBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, dwRop);
	// 清理临时对象，释放资源
	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return TRUE;
}