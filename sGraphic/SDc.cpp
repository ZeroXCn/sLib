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
SDc &SDc::CreateDc(LPTSTR lpszDriver, LPTSTR lpszDevice , LPTSTR lpszPort , const DEVMODE *pdm)
{
	m_hDC = ::CreateDCW(lpszDriver, lpszDevice, lpszPort, pdm);
	
	return *this;
}

// ����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
SDc &SDc::CreateCompatibleDc(SDc dc)
{

	m_hDC = ::CreateCompatibleDC(dc.GetDc());

	return *this;
}


BOOL SDc::DeleteDC()
{
	return ::DeleteDC(m_hDC);
}
///////////////////
//���û�ͼ������
void SDc::SetDc(HDC hDC)
{
	m_hDC = hDC;
}

//ȡ�õ�ǰ��ͼ������
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
	return SGdiObject(::SelectObject(m_hDC, Obj.Get()));
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

BOOL SDc::DeleteObject(SGdiObject Obj)
{
	return ::DeleteObject(Obj.Get());
}


//ѡ������
SFont SDc::SetFont(SFont ofont)
{
	return SFont((HFONT)::SelectObject(m_hDC, ofont.GetFont()));
}
SFont SDc::GetFont()
{
	return SFont((HFONT)::GetCurrentObject(m_hDC, OBJ_FONT));
}

//ѡ��λͼ
SBitmap SDc::SetBitmap(SBitmap bitmap)
{
	return SBitmap((HBITMAP)::SelectObject(m_hDC, bitmap.GetBitmap()));
}

SBitmap SDc::GetBitmap()
{
	return SBitmap((HBITMAP)::GetCurrentObject(m_hDC, OBJ_BITMAP));
}

//ѡ��ˢ
SBrush SDc::SetBrush(SBrush brush)
{
	return SBrush((HBRUSH)::SelectObject(m_hDC, brush.GetBrush()));
}
SBrush SDc::GetBrush()
{
	return SBrush((HBRUSH)::GetCurrentObject(m_hDC, OBJ_BRUSH));
}


//ѡ�񻭱�
SPen SDc::SetPen(SPen pen)
{
	return SPen((HPEN)::SelectObject(m_hDC, pen.GetPen()));
}

SPen SDc::GetPen()
{
	return SPen((HPEN)::GetCurrentObject(m_hDC, OBJ_PEN));
}


//ѡ������
SRgn SDc::SetRgn(SRgn rgn)
{
	return SRgn((HRGN)::SelectObject(m_hDC, rgn.GetRgn()));
}


SPalette SDc::GetPalette()
{
	return SPalette((HPALETTE)::GetCurrentObject(m_hDC, OBJ_PAL));
}

///////////////////
SBitmap SDc::CreateBitmap(int nWidth, int nHeight)
{
	SBitmap lbitmap(::CreateCompatibleBitmap(m_hDC, nWidth, nHeight));
	return lbitmap;
	
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


int SDc::DrawString(SString str, RECT rt, UINT format)
{
	return ::DrawText(m_hDC, str.c_str(), str.length(), &rt, format);
}

int SDc::DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat, LPDRAWTEXTPARAMS lpDTParams)
{
	return ::DrawTextEx(m_hDC, (LPTSTR)str.c_str(), str.length(), lprc, dwDTFormat, lpDTParams);
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, DWORD dwRop)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(hbm,sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(hbm, x, y, size.cx, size.cy, 0, 0, dwRop);
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(hbm, sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(hbm, x, y, size.cx, size.cy, 0, 0, crTransparent);
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);					//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbm);	//��λͼѡ������豸������¼�¾ɵľ��
	//�����͸��λͼ
	BOOL result = ::BitBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, dwRop);
	// ������ʱ�����ͷ���Դ
	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbm);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = StretchBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent)
{
	SIZE size{ 0, 0 };
	BITMAP  bm;
	::GetObject(hbm, sizeof(BITMAP), &bm);
	size.cx = bm.bmWidth; size.cy = bm.bmHeight;
	return DrawImage(hbm, x, y, nWidth, nHeight, xSrc, ySrc, size.cx, size.cy, crTransparent);
}
BOOL SDc::DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent)
{
	HDC hdcMem = ::CreateCompatibleDC(m_hDC);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbm);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = TransparentBlt(m_hDC, x, y, nWidth, nHeight, hdcMem, xSrc, ySrc, xSrcWidth, ySrcHeight, crTransparent);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}
