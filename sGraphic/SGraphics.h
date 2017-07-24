/**
* SGraphic类
* 图形渲染类
* @author ZeroX
* @version v1.0 21/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#ifndef _SGRAPHIC_H_
#define _SGRAPHIC_H_
#include <Windows.h>

#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(255,0,0)
#define BLUE_COLOR RGB(255,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)

class SGraphics:public SObject
{
protected:
	HWND m_hWnd;		//窗体句柄
	HDC m_hDC;			//绘图设备
public:
	SGraphics();
	SGraphics(HDC hDC);

	virtual ~SGraphics();
public:
	//开始绘制
	HDC BeginPaint(LPPAINTSTRUCT lpPaint);

	//结束绘制
	BOOL EndPaint(PAINTSTRUCT *lpPaint);

	//创建画刷
	HBRUSH CreateHatchBrush(
		_In_  int fnStyle,        // 影线样式
		_In_  COLORREF clrref     // 画刷颜色
		);
	/*	CreateSolidBrush 创建一个实心颜色（Solid color）画刷
		CreateHatchBrush 创建一个影线模式（Hatch pattern）的画刷
		CreatePatternBrush 创建一个位图模式（Bitmap pattern）的画刷
		CreateBrushIndirect 根据指定的样式、颜色、模式（pattern）来创建一个画刷
		CreateDIBPatternBrushPt 根据 DIB 模式（pattern from DIB）创建一个画刷*/

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
	BOOL FillRect(int left, int top, int right, int bottom, HBRUSH hbr = NULL);

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

	BOOL DrawImage();

	BOOL(DrawText)(LPTSTR lpchText, int cchText, RECT rt, UINT format);

	BOOL DrawString(SString str, RECT rt, UINT format);
};
#endif