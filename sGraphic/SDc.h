/**
* SDc类
* HDC封装类
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"
#include "SGdiObject.h"
#ifndef _SDC_H_
#define _SDC_H_
#include <Windows.h>
#include <wingdi.h>
#pragma comment(lib,"gdi32.lib")		//引用库

#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(255,0,0)
#define BLUE_COLOR RGB(255,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)

class SDc:public SObject
{
protected:
	HDC m_hDC;			//设备上下文
public:
	SDc();
	SDc(HDC hDC);

	virtual ~SDc();
public:
	//设置绘图上下文
	void SetDc(HDC hDC);

	//取得当前绘图上下文
	HDC GetDc();
public:
	//选择一对象到指定的设备上下文环境中
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj);
	SGdiObject SelectObject(SGdiObject pObj);

	//删除，释放系统资源
	BOOL DeleteObject(HGDIOBJ hObject);
	BOOL DeleteObject(SGdiObject pObj);

public:
	//设置文本颜色
	COLORREF SetTextColor(COLORREF crColor);

	//设置背景色
	COLORREF SetBkColor(COLORREF color);

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
	//BOOL GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode);

	//输出文字
	BOOL DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);

	//输出位图
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);


};

#endif