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

//�����豸�����Ļ���
SDc &SDc::CreateDC(LPTSTR lpszDriver, LPTSTR lpszDevice , LPTSTR lpszPort , const DEVMODE *pdm)
{
	m_hDC = ::CreateDC(lpszDriver, lpszDevice, lpszPort, pdm);
	
	return *this;
}

// ����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
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

//����DC��ǰ״̬
int SDc::SavaDC()
{
	return ::SaveDC(m_hDC);
}

//�ָ���SavaDC()�����DC
BOOL SDc::RestoreDC(int nSavedDc)
{
	return ::RestoreDC(m_hDC, nSavedDc);
}

///////////////////
//���û�ͼ������
void SDc::SetHandle(HDC hDC)
{
	m_hDC = hDC;
}

//ȡ�õ�ǰ��ͼ������
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

//��ȡ��ǰDC����
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


//ѡ������
SFont SDc::SetFont(SFont ofont)
{
	return SFont((HFONT)::SelectObject(m_hDC, ofont.GetHandle()));
}
SFont SDc::GetFont()
{
	return SFont((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
}

//ѡ��λͼ
SBitmap SDc::SetBitmap(SBitmap bitmap)
{
	return SBitmap((HBITMAP)::SelectObject(m_hDC, bitmap.GetHandle()));
}

SBitmap SDc::GetBitmap()
{
	return SBitmap((HBITMAP)::GetCurrentObject(m_hDC, OBJ_BITMAP));
}

//ѡ��ˢ
SBrush SDc::SetBrush(SBrush brush)
{
	return SBrush((HBRUSH)::SelectObject(m_hDC, brush.GetHandle()));
}
SBrush SDc::GetBrush()
{
	return SBrush((HBRUSH)::GetCurrentObject(m_hDC, OBJ_BRUSH));
}


//ѡ�񻭱�
SPen SDc::SetPen(SPen pen)
{
	return SPen((HPEN)::SelectObject(m_hDC, pen.GetHandle()));
}

SPen SDc::GetPen()
{
	return SPen((HPEN)::GetCurrentObject(m_hDC, OBJ_PEN));
}


//ѡ������
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
//ָ���豸�����������ֶ����־
UINT SDc::SetTextAlign(UINT fMode)
{
	return ::SetTextAlign(m_hDC, fMode);
}
UINT SDc::GetTextAlign()
{
	return ::GetTextAlign(m_hDC);
}

//�����ı���ɫ
COLORREF SDc::SetTextColor(COLORREF crColor)
{
	return ::SetTextColor(m_hDC, crColor);

}

COLORREF SDc::GetTextColor()
{
	return ::GetTextColor(m_hDC);
}

//���ñ���ɫ
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

	//���һ�������Ǵ�������,�����һ�����λ��
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

//������
BOOL SDc::FillRect(int left, int top, int right, int bottom, HBRUSH hbr)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;

	return ::FillRect(m_hDC, &temp, hbr);
}
//������
BOOL SDc::FillRect(int left, int top, int right, int bottom, COLORREF crColor)
{
	HBRUSH hBrush = CreateSolidBrush(crColor);		//���嵥ɫ��ˢ
	RECT rc = { left, top, right, bottom };			//������δ�С
	BOOL result = ::FillRect(m_hDC, &rc, hBrush);					//����������
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


//��Բ������
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

//����ͬʱ���ƶ����յĶ���Ρ�
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
	//��仰������,���������ı����
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
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);					//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//��λͼѡ������豸������¼�¾ɵľ��
	//�����͸��λͼ
	BOOL result = ::BitBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, dwRop);
	// ������ʱ�����ͷ���Դ
	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//��λͼѡ������豸������¼�¾ɵľ��

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
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = ::TransparentBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, crTransparent);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight,int xSrc, int ySrc, SBitmap sMarkBitmap, int xMark, int yMark, DWORD dwRop)
{
	/* ���´����������,������������ */
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, sbm.GetHandle());	//��λͼѡ������豸������¼�¾ɵľ��
	
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
	//��λ����,��ȱ仯
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

// ��DC��תһ���ĽǶ�  
int SDc::Rotate(double dTheta, int cx, int cy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;

	//��ת����
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
	OldTheta = acos(xOldform.eM11);	//ȡ��֮ǰDC��ԭ�Ƕ�
	return Rotate(OldTheta+dTheta, cx, cy);
}


int SDc::Scale(float sx, float sy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//ƽ�ƾ���
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
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//ƽ�ƾ���
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

//����
int SDc::Shear(int sx, int sy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//���о���
	xform.eM11 = (float)1.f;
	xform.eM12 = (float)sx;
	xform.eM21 = (float)sy;
	xform.eM22 = (float)1.f;
	xform.eDx = (float)0;
	xform.eDy = (float)0;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

//����
int SDc::Reflect(int cx, int cy)
{
	return Scale((float)(cx >= 0 ? 1 : -1), (float)(cy >= 0 ? 1 : -1));
}

//����
int SDc::Mirror(int a,int b,int c)
{
	float nDen = (float)a*a + b*b;
	if (nDen == 0.f)
		return GetGraphicsMode();

	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//�������
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
	return Mirror(1, 0, -dX);		//��Ϊ��׼ʽ�� c=-dx
}

int SDc::MirrorY(int dY)
{
	return Mirror(0, 1, -dY);
}

int SDc::Symmetry(int cx, int cy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = SetGraphicsMode(GM_ADVANCED);
	XFORM xform;
	//�Գƾ���
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
//��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������
BOOL SDc::BitBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
	return ::BitBlt(m_hDC, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

//ѡ��ָ���豸�����е�ˢ�ӻ��Ƹ����ľ�������
BOOL SDc::PatBlt(int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop)
{
	return ::PatBlt(m_hDC, nXLeft, nYLeft, nWidth, nHeight, dwRop);

}

//��Դ�豸������ָ���ľ��������е���ɫ����λ����λ��ת������ת����Ŀ���豸������ָ����ƽ���ı����
BOOL SDc::PlgBlt(CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask)
{
	return ::PlgBlt(m_hDC, lpPoint, hdcSrc, nXSrc, nYSrc, nWidth, nHeight, hbmMask, xMask, yMask);

}

//��Դ�����и���һ��λͼ��Ŀ����Σ���Ҫʱ��Ŀ���豸���õ�ģʽ����ͼ��������ѹ��
BOOL SDc::StretchBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	return ::StretchBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);
}

//ʹ���ض�������͹�դ��������Դ��Ŀ��λͼ����ɫ���ݽ������
BOOL SDc::MaskBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	return ::MaskBlt(m_hDC, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, hbmMask, xMask, yMask, dwRop);

}

//��ָ����Դ�豸�����еľ����������ص���ɫ���ݽ���λ�飨bit_block��ת���������������Ŀ���豸����
BOOL SDc::TransparentBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	return ::TransparentBlt(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent);

}

//������ʾ����ָ��͸���ȵ�ͼ��
BOOL SDc::AlphaBlend(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction)
{
	return ::AlphaBlend(m_hDC, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, blendFunction);

}
