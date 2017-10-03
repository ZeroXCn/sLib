/**
* SGraphics类
* 图像绘制类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SDc.h"
#ifndef _SGRAPHICS_H_
#define _SGRAPHICS_H_

class SGraphics:public SObject
{
protected:
	HWND m_hWnd;
	HDC m_hDC;
	int m_nWidth, m_nHeight;
public:
	SGraphics();
	SGraphics(HWND hWnd,HDC hDC=NULL);
	virtual ~SGraphics();

	//窗口句柄
	HWND GetWnd();
	void SetWnd(HWND hWnd);

	//获取设置DC设备
	HDC GetDC();
	void SetDC(HDC hDC);

	//设置宽高
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	//设置宽高
	int GetWidth();
	int GetHeight();
public:
	//选择字体
	SFont SetFont(SFont ofont);
	SFont GetFont();
public:
	//画点
	BOOL DrawPoint(int x, int y, COLORREF color = RGB(0, 0, 0));

	//画线
	void DrawLine(int x1, int y1, int x2, int y2);

	//画三角型
	void DrawTringle(POINT a, POINT b, POINT c);

	//画矩形-包括填充和画边框
	BOOL DrawRect(int left, int top, int right, int bottom);

	//画矩形边框
	BOOL FrameRect(int left, int top, int right, int bottom, HBRUSH hbr = NULL);

	//填充矩形
	BOOL FillRect(int left, int top, int right, int bottom, HBRUSH hbr);
	BOOL FillRect(int left, int top, int right, int bottom, COLORREF crColor = BLACK_COLOR);

	//绘制圆角矩形
	BOOL RoundRect(int left, int top, int right, int bottom, int width, int height);

	//将矩形内容反色
	BOOL InvertRect(int left, int top, int right, int bottom);

	//画圆
	BOOL DrawRadius(int x, int y, int radius);

	//画椭圆
	BOOL DrawEllipse(int left, int top, int right, int bottom);

	//画圆饼扇区
	BOOL DrawPie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2);

	//绘制切割椭圆
	BOOL DrawChord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//填充椭圆
	//void FillEllipse(int left, int top, int right, int bottom);

	//绘制多边形
	BOOL DrawPolygon(POINT *apt, int cpt);

	//绘制同时绘制多个封闭的多边形。
	BOOL DrawPolyPolygon(POINT *apt, int *asz, int csz);

	//渐变填充
	BOOL GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode);

	//输出文字
	BOOL DrawString(SString str, int x, int y, SFont sFont, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	BOOL DrawString(SString str, int x, int y, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	int DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);
	//输出带边框文字
	int DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat = DT_LEFT, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//输出位图
	BOOL DrawImage(SBitmap sbm, int x, int y, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, UINT crTransparent);	//两者不可区分,参数需要强制转换
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent);
	BOOL DrawImage(SBitmap sbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, SBitmap sMarkBitmap, int xMark, int yMark, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL DrawImage(SBitmap sbm, int x, int y, SBitmap sMarkBitmap, int xSrc = 0, int ySrc = 0, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	//输出画布
	BOOL DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);
	BOOL DrawDC(SDc sdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc = 0, int nYOriginSrc = 0, DWORD dwRop = SRCCOPY);

};

#endif