/**
* SRgn类
* GDI对象-区域类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SRGN_H_
#define _SRGN_H_
class SRgn :public SGdiObject
{
public:
	SRgn();
	SRgn(SGdiObject Obj);
	SRgn(HRGN hRgn);
	virtual ~SRgn();
public:
	void SetHandle(HRGN hRgn);
	HRGN GetHandle();
public:
	//创建椭圆区域
	BOOL CreateElliptic( int nLeft,  int nTop,  int nRight,  int nBottom);

	//创建一内切于特定矩形的椭圆区域
	BOOL CreateElliptieIndirect(RECT lRect);

	//创建一个由一系列点围成的区域。
	BOOL CreatePolygon(POINT lPoints, int nCount, int nMode);

	//创建一个矩形对象
	BOOL CreateRect(int nLeft, int nTop, int nRight, int nBottom);

	//创建一个矩形对象
	BOOL CreateRectIndirect(RECT lRect);

public:
	//将两个区域组合为一个新区域。
	int Combine(HRGN hrgnSrc1, HRGN hrgnSrc2, int nMode);

};

#endif