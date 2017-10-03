#include "SGraphics.h"
SGraphics::SGraphics()
{

}

SGraphics::SGraphics(HWND hWnd,HDC hDC)
{
	m_hWnd = hWnd;
	RECT rt;
	::GetWindowRect(hWnd, &rt);
	SetWidth(rt.right - rt.left);
	SetHeight(rt.bottom - rt.top);

	m_hDC = hDC;
}
SGraphics::~SGraphics()
{

}

//窗口句柄
HWND SGraphics::GetWnd()
{
	return m_hWnd;
}
void SGraphics::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

//获取设置DC设备
HDC SGraphics::GetDC()
{
	return m_hDC;
}
void SGraphics::SetDC(HDC hDC)
{
	m_hDC = hDC;
}

//设置宽高
void SGraphics::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}
void SGraphics::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}
//设置宽高
int SGraphics::GetWidth()
{
	return m_nWidth;
}
int SGraphics::GetHeight()
{
	return m_nHeight;
}

///////////
//选择字体
SFont SGraphics::SetFont(SFont ofont)
{
	return SFont((HFONT)::SelectObject(m_hDC, ofont.GetHandle()));
}
SFont SGraphics::GetFont()
{
	return SFont((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
}
///////////////
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

	return ::FillRect(m_hDC, &temp, hbr);
}
//填充矩形
BOOL SGraphics::FillRect(int left, int top, int right, int bottom, COLORREF crColor)
{
	HBRUSH hBrush = CreateSolidBrush(crColor);		//定义单色画刷
	RECT rc = { left, top, right, bottom };			//定义矩形大小
	BOOL result = ::FillRect(m_hDC, &rc, hBrush);					//绘制填充矩形
	::DeleteObject(hBrush);
	return result;
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

BOOL SGraphics::GradientFill(CONST PTRIVERTEX pVertex, ULONG uVertex, CONST PVOID pMesh, ULONG nMesh, ULONG ulMode)
{
	return ::GradientFill(m_hDC, pVertex, uVertex, pMesh, nMesh, ulMode);
}

BOOL SGraphics::DrawString(SString str, int x, int y, COLORREF crColor, BOOL bTrans, UINT format)
{
	int bkModeOld;
	if (bTrans) bkModeOld = ::SetBkMode(m_hDC,TRANSPARENT);
	COLORREF colorOld = ::SetTextColor(m_hDC, crColor);

	RECT rt{ x, y, 0, 0 };
	//这句话不绘制,用来计算文本宽高
	::DrawText(m_hDC, str.c_str(), str.length(), &rt, DT_CALCRECT);
	BOOL result = ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);

	::SetTextColor(m_hDC, colorOld);
	if (bTrans)::SetBkMode(m_hDC, bkModeOld);

	return result;
}
BOOL SGraphics::DrawString(SString str, int x, int y, SFont sFont, COLORREF crColor, BOOL bTrans, UINT format)
{
	SFont old = SetFont(sFont);
	BOOL ret = DrawString(str, x, y, crColor, bTrans, format);
	SetFont(old);
	return ret;
}

int SGraphics::DrawString(SString str, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);
}

int SGraphics::DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat, LPDRAWTEXTPARAMS lpDTParams)
{
	return ::DrawTextEx(m_hDC, (LPTSTR)str.c_str(), str.length(), lprc, dwDTFormat, lpDTParams);
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, DWORD dwRop)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, size.cx, size.cy, 0, 0, size.cx, size.cy, dwRop);
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, size.cx, size.cy, 0, 0, crTransparent);
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);					//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄
	//输出不透明位图
	BOOL result = ::BitBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, dwRop);
	// 清理临时对象，释放资源
	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄

	BOOL result = ::StretchBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, nWidth, nHeight, xSrc, ySrc, size.cx, size.cy, crTransparent);
}
BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄

	BOOL result = ::TransparentBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, crTransparent);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, SBitmap sMarkBitmap, int xMark, int yMark, DWORD dwRop)
{
	/* 以下代码存在问题,不能正常工作 */
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄

	BOOL result = ::MaskBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, sMarkBitmap.GetHandle(), xMark, yMark, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;

}
BOOL SGraphics::DrawImage(SBitmap sbm, int x, int y, SBitmap sMarkBitmap, int xSrc, int ySrc, DWORD dwRop)
{
	SIZE size = sbm.GetSize();
	return DrawImage(sbm, x, y, size.cx, size.cy, xSrc, ySrc, sMarkBitmap, xSrc, ySrc, dwRop);
}

BOOL SGraphics::DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	return ::StretchBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, sdcSrc.GetHandle(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);

}
BOOL SGraphics::DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, DWORD dwRop)
{
	return ::BitBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, sdcSrc.GetHandle(), nXOriginSrc, nYOriginSrc, dwRop);
}