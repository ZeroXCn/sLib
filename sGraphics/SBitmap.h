/**
* SBitmap类
* GDI对象-位图类(只支持BMP格式)
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"
#ifndef _SBITMAP_H_
#define _SBITMAP_H_
#include <Windows.h>
#include <Mmsystem.h>
#include <wingdi.h>

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"gdi32.lib")

class SBitmap :public SGdiHandle<HBITMAP, BITMAP>
{
public:
	SBitmap(SGdiObj Obj);
	SBitmap(HBITMAP hBitmap=NULL);
	virtual ~SBitmap();
public:
	//创建一个带有特定宽度、高度和颜色格式的位图。
	BOOL Create(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPeral, CONST VOID *lpvBits);

	//创建与指定的设备环境相关的设备兼容的位图
	BOOL CreateCompatible(HDC hdc, int nWidth, int nHeight);

	//创建一个具有特定宽度、高度和颜色格式的位图
	BOOL CreateIndirect(CONST BITMAP *lpbm);

	//创建应用程序可以直接写入的、与设备无关的位图（DIB）的函数。
	BOOL CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT iUsage, VOID** ppvBits, HANDLE hSection, DWORD dwOffset);

	//从资源中加载位图
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//从文件中加载位图
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//从内存中加载
	BOOL Load(void *pMemory, int nLength);

	//从位图中保存文件
	BOOL Save(LPTSTR lpFileName);

public:
	//取得,设置位宽
	int GetWidth();

	//取得,设置位高
	int GetHeight();

	//取得,设置位图宽高
	SIZE GetSize();
	void SetSize(int nWidth,int nHeight);



public:
	/* 位图操作 */
	//对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。
	BOOL BitBlt(HDC hdcDest,  int nXDest,  int nYDest,  int nWidth,  int nHeight,  HDC hdcSrc,  int nXSrc,  int nYSrc,  DWORD dwRop);
	BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc = 0, int nYSrc = 0, DWORD dwRop = SRCCOPY);
	BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, DWORD dwRop = SRCCOPY);

	//选入指定设备环境中的刷子绘制给定的矩形区域
	BOOL PatBlt(HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop = PATCOPY);

	//对源设备环境中指定的矩形区域中的颜色数据位进行位块转换，并转换到目标设备环境中指定的平行四边形里。
	BOOL PlgBlt(HDC hdcDest, CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask);

	//从源矩形中复制一个位图到目标矩形，必要时按目标设备设置的模式进行图像的拉伸或压缩
	BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);
	BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);


	//使用特定的掩码和光栅操作来对源和目标位图的颜色数据进行组合
	//遮罩法-要求为色黑白图(人物轮廓为黑,背景为白)-最后一个参数为两者光栅操作码-高位为前景(MARK)与背景的,低位为最终与输出的DC
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));

	//对指定的源设备环境中的矩形区域像素的颜色数据进行位块（bit_block）转换，并将结果置于目标设备环境
	//透明色彩法
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,UINT crTransparent = RGB(255, 255, 255));
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,UINT crTransparent = RGB(255, 255, 255));

	//用来显示具有指定透明度的图像
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, BLENDFUNCTION blendFunction);
public:
	/* 以下为扩展操作 */

	//绘制半透明位图,不透明度nApha取值为0~255
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nAlpha);

	//绘制灰度位图，可设置为镂空
	void DrawGray(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransparent = RGB(0, 0, 0));

	//绘制半透明镂空位图
	void DrawTransAlpha(HDC hdcBack,		// 背景DC
		int nXBack,							// 背景图左上角X坐标
		int nYBack,							// 背景图左上角Y坐标
		int nWidthBack,						// 背景图宽度
		int nHeightBack,					// 背景图高度
		HDC hdcSrc,							// 源DC
		int nXFore,							// 前景图左上角X坐标
		int nYFore,							// 前景图左上角Y坐标
		int nWidthFore,						// 前景图宽度
		int nHeightFore,					// 前景图高度
		int nAlpha = 100,					// 不透明度
		COLORREF crTrans = RGB(0, 0, 0));	//镂空色
	void DrawTransAlpha(HDC hdcBack,int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nWidthFore,int nHeightFore,int nAlpha = 100,COLORREF crTrans = RGB(0, 0, 0));
	void DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack,int nAlpha = 100, COLORREF crTrans = RGB(0, 0, 0));
	void DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nAlpha = 100, COLORREF crTrans = RGB(0, 0, 0));

	//自定义的绘制镂空图的方法
	void DrawTransBitmap(
		HDC hdcDest,						// 目标DC
		int nXDest,							// 目标左上角X坐标
		int nYDest,							// 目标左上角Y坐标
		int nWidthDest,						// 目标宽度
		int nHeightDest,					// 目标高度
		HDC hdcSrc,							// 源DC
		int nXSrc,							// 源X起点
		int nYSrc,							// 源Y起点
		int nWidthSrc,						// 源宽度
		int nHeightSrc,						// 源高度
		COLORREF crTrans = RGB(255, 255, 255)  // 透明色
		);
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans = RGB(255, 255, 255));
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest,COLORREF crTrans = RGB(255, 255, 255));
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, COLORREF crTrans = RGB(255, 255, 255));

	//自定义的绘制
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc,HBITMAP hMark, int nMarkX, int nMarkY);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, HBITMAP hMark);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, HBITMAP hMark);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hMark);
};

#endif