/**
* SDc类
* HDC封装类
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#include "SGdiObject.h"
#include "SBitmap.h"
#include "SFont.h"
#include "SBrush.h"
#include "SPen.h"
#include "SRgn.h"
#include "SPalette.h"

#include "SBufferDC.h"

#ifndef _SDC_H_
#define _SDC_H_
#include <Windows.h>
#include <Mmsystem.h>
#include <wingdi.h>

#pragma	comment(lib,"winmm.lib" )
#pragma comment(lib,"gdi32.lib")

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
	void SetDC(HDC hDC);

	//取得当前绘图上下文
	HDC GetDC();

public:
	//创建设备上下文环境
	SDc &CreateDC(LPTSTR lpszDriver, LPTSTR lpszDevice = NULL, LPTSTR lpszPort = NULL, const DEVMODE *pdm = NULL);

	// 创建一个与指定设备兼容的内存设备上下文环境
	SDc &CreateCompatibleDC(SDc dc);

	// 删除指定的设备上下文环境（Dc）。
	BOOL DeleteDC();

	//把设备上下文环境中悬而未决的操作取消。
	BOOL CancelDC();

	//保存DC当前状态
	int SavaDC();

	//恢复由SavaDC()保存的DC
	BOOL RestoreDC(int nSavedDc);


public:
	//选择一对象到指定的设备上下文环境中
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj);
	SGdiObject SelectObject(SGdiObject pObj);

	//获取当前DC对象
	HGDIOBJ GetCurrentObject(UINT uObjectType);
	//获取对象属性
	UINT GetObjectType(HGDIOBJ hObject);

	//删除，释放系统资源
	BOOL DeleteObject(HGDIOBJ hObject);
	BOOL DeleteObject(SGdiObject pObj);
	
	//选择字体
	SFont SetFont(SFont ofont);
	SFont GetFont();
	//选择位图
	SBitmap SetBitmap(SBitmap bitmap);
	SBitmap GetBitmap();
	//选择画刷
	SBrush SetBrush(SBrush brush);
	SBrush GetBrush();
	//选择画笔
	SPen SetPen(SPen pen);
	SPen GetPen();
	//选择区域
	SRgn SetRgn(SRgn rgn);
	//调色板
	SPalette GetPalette();
public:
	/* DC属性操作 */
	//取得DC起始点坐标
	POINT GetDCOrgEx();

public:
	//指定设备环境设置文字对齐标志
	UINT SetTextAlign(UINT fMode); // 文本对齐选项
	UINT GetTextAlign(); // 文本对齐选项

	//设置文本颜色
	COLORREF SetTextColor(COLORREF crColor);
	COLORREF GetTextColor();

	//设置背景色
	COLORREF SetBkColor(COLORREF color);
	COLORREF SetBkColor(BOOL bTrans);
	COLORREF GetBkColor();

	//设置背景模式-OPAQUE不透明和TRANSPARENT透明
	int SetBkMode(int iBkMode);
	int GetBkMode();

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
	BOOL FillRect(int left, int top, int right, int bottom, COLORREF crColor=BLACK_COLOR);

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
	BOOL DrawString(SString str, int x, int y, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	int DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);
	//输出带边框文字
	int DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat = DT_LEFT, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//输出位图
	BOOL DrawImage(HBITMAP hbm, int x, int y, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, UINT crTransparent);	//两者不可区分,参数需要强制转换
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent );

	//输出画布
	BOOL DrawDC(HDC hdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);
	BOOL DrawDC(HDC hdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc = 0, int nYOriginSrc = 0, DWORD dwRop = SRCCOPY);
public:
	/* DC操作 */
	//二维的线性转变，此转换可用于输出缩放、旋转、倾斜变换或平移变换的图形。
	int SetTransform(CONST XFORM *lpXform);
	XFORM GetTransform();
	int RestoreTransform(int nGraphicsMode = GM_COMPATIBLE);	//恢复正常DC

	//旋转和恢复旋转
	int Rotate(int iAngle, int cx = 0, int cy = 0);
	int Rotate(double dTheta, int cx = 0, int cy = 0);
	int RotateFrom(int iAngle, int cx = 0, int cy = 0);
	int RotateFrom(double dTheta, int cx = 0, int cy = 0);
	
	//缩放
	int Scale(float sx, float sy);
	int ScaleFrom(float sx, float sy);

	//平移
	int Offset(int cx, int cy);
	int OffsetFrom(int cx, int cy);

	//错切
	int Shear(int sx, int sy);

	//反射
	int Reflect(int cx, int cy );

	//镜像-关于某中轴线
	int Mirror(int dX);

	//关于某点对称
	int Symmetry(int cx, int cy);

public:
	/* 以下是位图操作 */
	//对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。
	BOOL BitBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop = SRCCOPY);

	//选入指定设备环境中的刷子绘制给定的矩形区域
	BOOL PatBlt(int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop = PATCOPY);

	//对源设备环境中指定的矩形区域中的颜色数据位进行位块转换，并转换到目标设备环境中指定的平行四边形里。
	BOOL PlgBlt(CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask);

	//从源矩形中复制一个位图到目标矩形，必要时按目标设备设置的模式进行图像的拉伸或压缩
	BOOL StretchBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);

	//使用特定的掩码和光栅操作来对源和目标位图的颜色数据进行组合
	BOOL MaskBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop);

	//对指定的源设备环境中的矩形区域像素的颜色数据进行位块（bit_block）转换，并将结果置于目标设备环境
	BOOL TransparentBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);

	//用来显示具有指定透明度的图像
	BOOL AlphaBlend(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);

};

#endif