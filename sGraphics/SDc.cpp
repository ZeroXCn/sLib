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

//////////////////

//创建设备上下文环境
SDc &SDc::CreateDC(LPTSTR lpszDriver, LPTSTR lpszDevice , LPTSTR lpszPort , const DEVMODE *pdm)
{
	m_hDC = ::CreateDC(lpszDriver, lpszDevice, lpszPort, pdm);
	
	return *this;
}

// 创建一个与指定设备兼容的内存设备上下文环境
SDc &SDc::CreateCompatibleDC(SDc dc)
{

	m_hDC = ::CreateCompatibleDC(dc.GetHandle());

	return *this;
}


BOOL SDc::DeleteDC()
{
	return ::DeleteDC(m_hDC);
}

BOOL SDc::CancelDC()
{
	return ::CancelDC(m_hDC);
}

//保存DC当前状态
int SDc::SavaDC()
{
	return ::SaveDC(m_hDC);
}

//恢复由SavaDC()保存的DC
BOOL SDc::RestoreDC(int nSavedDc)
{
	return ::RestoreDC(m_hDC, nSavedDc);
}

///////////////////
//设置绘图上下文
void SDc::SetHandle(HDC hDC)
{
	m_hDC = hDC;
}

//取得当前绘图上下文
HDC SDc::GetHandle()
{
	return m_hDC;
}
///////////////////
HGDIOBJ SDc::SelectObject(HGDIOBJ hgdiobj)
{
	return ::SelectObject(m_hDC, hgdiobj);
}

SGdiObj SDc::SelectObject(SGdiObj Obj)
{
	return SGdiObj(::SelectObject(m_hDC, Obj.GetHandle()));
}

//获取当前DC对象
HGDIOBJ SDc::GetCurrentObject(UINT uObjectType)
{
	return ::GetCurrentObject(m_hDC, uObjectType);
}


UINT SDc::GetObjectType(HGDIOBJ hObject)
{
	return ::GetObjectType(hObject);
}

BOOL SDc::DeleteObject(HGDIOBJ hObject)
{
	return ::DeleteObject(hObject);
}

BOOL SDc::DeleteObject(SGdiObj Obj)
{
	return ::DeleteObject(Obj.GetHandle());
}


//选择字体
SFont SDc::SetFont(SFont ofont)
{
	return SFont((HFONT)::SelectObject(m_hDC, ofont.GetHandle()));
}
SFont SDc::GetFont()
{
	return SFont((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
}

//选择位图
SBitmap SDc::SetBitmap(SBitmap bitmap)
{
	return SBitmap((HBITMAP)::SelectObject(m_hDC, bitmap.GetHandle()));
}

SBitmap SDc::GetBitmap()
{
	return SBitmap((HBITMAP)::GetCurrentObject(m_hDC, OBJ_BITMAP));
}

//选择画刷
SBrush SDc::SetBrush(SBrush brush)
{
	return SBrush((HBRUSH)::SelectObject(m_hDC, brush.GetHandle()));
}
SBrush SDc::GetBrush()
{
	return SBrush((HBRUSH)::GetCurrentObject(m_hDC, OBJ_BRUSH));
}


//选择画笔
SPen SDc::SetPen(SPen pen)
{
	return SPen((HPEN)::SelectObject(m_hDC, pen.GetHandle()));
}

SPen SDc::GetPen()
{
	return SPen((HPEN)::GetCurrentObject(m_hDC, OBJ_PEN));
}


//选择区域
SRgn SDc::SetRgn(SRgn rgn)
{
	return SRgn((HRGN)::SelectObject(m_hDC, rgn.GetHandle()));
}


SPalette SDc::GetPalette()
{
	return SPalette((HPALETTE)::GetCurrentObject(m_hDC, OBJ_PAL));
}
///////
POINT SDc::GetDCOrgEx()
{
	POINT pt{ 0, 0 };
	::GetDCOrgEx(m_hDC, &pt);
	return pt;
}

/////////////////
//指定设备环境设置文字对齐标志
UINT SDc::SetTextAlign(UINT fMode)
{
	return ::SetTextAlign(m_hDC, fMode);
}
UINT SDc::GetTextAlign()
{
	return ::GetTextAlign(m_hDC);
}

//设置文本颜色
COLORREF SDc::SetTextColor(COLORREF crColor)
{
	return ::SetTextColor(m_hDC, crColor);

}

COLORREF SDc::GetTextColor()
{
	return ::GetTextColor(m_hDC);
}

//设置背景色
COLORREF SDc::SetBkColor(COLORREF color)
{
	return ::SetBkColor(m_hDC, color);
}
COLORREF SDc::SetBkColor(BOOL bTrans)
{
	return ::SetBkMode(m_hDC, bTrans);
}
COLORREF SDc::GetBkColor()
{
	return ::GetBkMode(m_hDC);
}

int SDc::SetBkMode(int iBkMode)
{
	return ::SetBkMode(m_hDC, iBkMode);
}
int SDc::GetBkMode()
{
	return ::GetBkMode(m_hDC);
}

SIZE SDc::GetTextExtentPoint(LPTSTR lpString, int clen)
{
	SIZE size;
	::GetTextExtentPoint(m_hDC, lpString, clen, &size);
	return size;
}

int SDc::SetGraphicsMode(int iMode)
{
	return ::SetGraphicsMode(m_hDC, iMode);
}
int SDc::GetGraphicsMode()
{
	return ::GetGraphicsMode(m_hDC);
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

	return ::FillRect(m_hDC, &temp, hbr);
}
//填充矩形
BOOL SDc::FillRect(int left, int top, int right, int bottom, COLORREF crColor)
{
	HBRUSH hBrush = CreateSolidBrush(crColor);		//定义单色画刷
	RECT rc = { left, top, right, bottom };			//定义矩形大小
	BOOL result = ::FillRect(m_hDC, &rc, hBrush);					//绘制填充矩形
	::DeleteObject(hBrush);
	return result;
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

BOOL SDc::GradientFill(CONST PTRIVERTEX pVertex, ULONG uVertex, CONST PVOID pMesh, ULONG nMesh, ULONG ulMode)
{
	return ::GradientFill(m_hDC, pVertex, uVertex, pMesh, nMesh, ulMode);
}

BOOL SDc::DrawString(SString str, int x, int y, COLORREF crColor, BOOL bTrans, UINT format)
{
	int bkModeOld;
	if (bTrans) bkModeOld=this->SetBkMode(TRANSPARENT);
	COLORREF colorOld = this->SetTextColor(crColor);

	RECT rt{ x, y, 0, 0 };
	//这句话不绘制,用来计算文本宽高
	::DrawText(m_hDC, str.c_str(), str.length(), &rt, DT_CALCRECT);
	BOOL result = ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);

	this->SetTextColor(colorOld);
	if (bTrans)this->SetBkMode(bkModeOld);

	return result;
}
BOOL SDc::DrawString(SString str, int x, int y, SFont sFont, COLORREF crColor , BOOL bTrans , UINT format )
{
	SFont old = SetFont(sFont);
	BOOL ret = DrawString(str, x, y, crColor, bTrans, format);
	SetFont(old);
	return ret;
}

int SDc::DrawString(SString str, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);
}

int SDc::DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat, LPDRAWTEXTPARAMS lpDTParams)
{
	return ::DrawTextEx(m_hDC, (LPTSTR)str.c_str(), str.length(), lprc, dwDTFormat, lpDTParams);
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, DWORD dwRop)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, size.cx, size.cy, 0, 0, size.cx, size.cy, dwRop);
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, size.cx, size.cy, 0, 0, crTransparent);
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop)
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

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄

	BOOL result = ::StretchBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(sbm.GetHandle(), sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(sbm.GetHandle(), x, y, nWidth, nHeight, xSrc, ySrc, size.cx, size.cy, crTransparent);
}
BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//将位图选入兼容设备，并记录下旧的句柄

	BOOL result = ::TransparentBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, crTransparent);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight,int xSrc, int ySrc, SBitmap sMarkBitmap, int xMark, int yMark, DWORD dwRop)
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
BOOL SDc::DrawImage(SBitmap sbm, int x, int y, SBitmap sMarkBitmap, int xSrc, int ySrc, DWORD dwRop)
{
	SIZE size = sbm.GetSize();
	return DrawImage(sbm, x, y, size.cx, size.cy, xSrc, ySrc, sMarkBitmap, xSrc, ySrc, dwRop);
}

BOOL SDc::DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	return ::StretchBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, sdcSrc.GetHandle(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);

}
BOOL SDc::DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, DWORD dwRop)
{
	return ::BitBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, sdcSrc.GetHandle(), nXOriginSrc, nYOriginSrc, dwRop);
}
///////////////
int SDc::SetWorldTransform(CONST XFORM *lpXform)
{
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	::SetWorldTransform(m_hDC, lpXform);
	return nGraphicsMode;
}

XFORM SDc::GetWorldTransform()
{
	XFORM Xform;
	::GetWorldTransform(m_hDC,&Xform);
	return Xform;
}

BOOL SDc::GetWorldTransform(LPXFORM lpXform)
{
	return ::GetWorldTransform(m_hDC, lpXform);
}

int SDc::RestoreWorldTransform(int nGraphicsMode)
{
	//单位矩阵,恒等变化
	XFORM xform;
	xform.eM11 = (float)1.0;
	xform.eM12 = (float)0;
	xform.eM21 = (float)0;
	xform.eM22 = (float)1.0;
	xform.eDx = (float)0;
	xform.eDy = (float)0;

	SetWorldTransform(&xform);
	return SetGraphicsMode(nGraphicsMode);
}

// 将DC旋转一定的角度  
int SDc::Rotate(double dTheta, int cx, int cy)
{
	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;

	//旋转矩阵
	double fangle = dTheta; //(double)iAngle / 180. * 3.1415926;

	xform.eM11 = (float)cos(fangle);
	xform.eM12 = (float)sin(fangle);
	xform.eM21 = (float)-sin(fangle);
	xform.eM22 = (float)cos(fangle);
	xform.eDx = (float)(cx - cos(fangle)*cx + sin(fangle)*cy);
	xform.eDy = (float)(cy - cos(fangle)*cy - sin(fangle)*cx);

	SetWorldTransform(&xform);
	
	return nGraphicsMode;
}
int SDc::Rotate(int iAngle, int cx , int cy)
{
	return Rotate((double)((double)iAngle / 180.f * 3.1415926), cx, cy);
}

int SDc::RotateFrom(int iAngle, int cx , int cy)
{
	return RotateFrom((double)((double)iAngle / 180.f * 3.1415926), cx, cy);
}
int SDc::RotateFrom(double dTheta, int cx , int cy )
{
	
	XFORM xOldform;
	double OldTheta;
	GetWorldTransform(&xOldform);
	OldTheta = acos(xOldform.eM11);	//取得之前DC的原角度
	return Rotate(OldTheta+dTheta, cx, cy);
}


int SDc::Scale(float sx, float sy)
{
	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//平移矩阵
	xform.eM11 = (float)sx;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)sy;
	xform.eDx = (float)0.f;
	xform.eDy = (float)0.f;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}
int SDc::ScaleFrom(float sx, float sy)
{
	XFORM xOldform;
	GetWorldTransform(&xOldform);
	sx *= xOldform.eM11; sy *= xOldform.eM22;
	return Scale(sx, sy);
}


int SDc::Offset(int cx, int cy)
{
	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//平移矩阵
	xform.eM11 = (float)1.f;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)1.f;
	xform.eDx = (float)cx;
	xform.eDy = (float)cy;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

int SDc::OffsetFrom(int cx, int cy)
{
	XFORM xOldform;
	GetWorldTransform(&xOldform);
	cx += (int)xOldform.eDx; cy += (int)xOldform.eDy;
	return Offset(cx,cy);
}

//错切
int SDc::Shear(int sx, int sy)
{
	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//错切矩阵
	xform.eM11 = (float)1.f;
	xform.eM12 = (float)sx;
	xform.eM21 = (float)sy;
	xform.eM22 = (float)1.f;
	xform.eDx = (float)0;
	xform.eDy = (float)0;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

//反射
int SDc::Reflect(int cx, int cy)
{
	return Scale((float)(cx >= 0 ? 1 : -1), (float)(cy >= 0 ? 1 : -1));
}

//镜像
int SDc::Mirror(int a,int b,int c)
{
	float nDen = (float)a*a + b*b;
	if (nDen == 0.f)
		return GetGraphicsMode();

	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//镜像矩阵
	xform.eM11 = (float)(nDen - 2 * a*a) / nDen;
	xform.eM12 = (float)(-2 * a * b) / nDen;
	xform.eM21 = (float)(-2 * a * b) / nDen;
	xform.eM22 = (float)(nDen - 2 * b*b) / nDen;
	xform.eDx = (float)(-2 * a * c) / nDen;
	xform.eDy = (float)(-2 * b * c) / nDen;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}


int SDc::MirrorX(int dX)
{
	return Mirror(1, 0, -dX);		//化为标准式后 c=-dx
}

int SDc::MirrorY(int dY)
{
	return Mirror(0, 1, -dY);
}

int SDc::Symmetry(int cx, int cy)
{
	//为指定的设备环境设置图形模式
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//对称矩阵
	xform.eM11 = (float)-1.f;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)-1.f;
	xform.eDx = (float)2 * cx;
	xform.eDy = (float)2 * cy;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

/////////////////
//对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。
BOOL SDc::BitBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
	return ::BitBlt(m_hDC, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

//选入指定设备环境中的刷子绘制给定的矩形区域
BOOL SDc::PatBlt(int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop)
{
	return ::PatBlt(m_hDC, nXLeft, nYLeft, nWidth, nHeight, dwRop);

}

//对源设备环境中指定的矩形区域中的颜色数据位进行位块转换，并转换到目标设备环境中指定的平行四边形里。
BOOL SDc::PlgBlt(CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask)
{
	return ::PlgBlt(m_hDC, lpPoint, hdcSrc, nXSrc, nYSrc, nWidth, nHeight, hbmMask, xMask, yMask);

}

//从源矩形中复制一个位图到目标矩形，必要时按目标设备设置的模式进行图像的拉伸或压缩
BOOL SDc::StretchBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	return ::StretchBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);
}

//使用特定的掩码和光栅操作来对源和目标位图的颜色数据进行组合
BOOL SDc::MaskBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	return ::MaskBlt(m_hDC, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, hbmMask, xMask, yMask, dwRop);

}

//对指定的源设备环境中的矩形区域像素的颜色数据进行位块（bit_block）转换，并将结果置于目标设备环境
BOOL SDc::TransparentBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	return ::TransparentBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent);

}

//用来显示具有指定透明度的图像
BOOL SDc::AlphaBlend(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction)
{
	return ::AlphaBlend(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, blendFunction);

}
