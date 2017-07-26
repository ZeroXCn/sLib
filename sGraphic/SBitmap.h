/**
* SBitmap类
* GDI对象-位图类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SBITMAP_H_
#define _SBITMAP_H_
class SBitmap:public SGdiObject
{
protected:
	BITMAP m_sBitmap;		//位图结构体
public:
	//创建一个带有特定宽度、高度和颜色格式的位图。
	HBITMAP CreateBitmap(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPeral, CONST VOID *lpvBits);

	//创建与指定的设备环境相关的设备兼容的位图
	HBITMAP CreateCompatibleBitmap(HDC hdc, int nWidth, int nHeight);

	//创建一个具有特定宽度、高度和颜色格式的位图
	HBITMAP CreateBitmaplndirect(CONST BITMAP *lpbm);

public:
	//从模块的可执行文件中加载指定的位图资源-已被取代
	HBITMAP LoadBitmap(HINSTANCE hInstance, LPCTSTR lpBitmapName);

	//该函数装载图标，光标，或位图
	HANDLE LoadImage(
		HINSTANCE hinst,
		LPCTSTR lpszName,
		UINT uType,
		int cxDesired,
		int cyDesired,
		UINT fuLoad
		);
public:

	int GetWidth();

	int GetHeight();
public:


};

#endif