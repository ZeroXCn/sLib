/**
* SPen类
* GDI对象-画笔类
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "SGdiObject.h"
#ifndef _SPEN_H_
#define _SPEN_H_

class SPen :public SGdiObject
{
public:
	SPen();
	SPen(SGdiObject Obj);
	SPen(HPEN hPen);
	virtual ~SPen();

public:
	void SetHandle(HPEN hPen);

	HPEN GetHandle();

	LOGPEN GetPenStruct();
public:
	//指定的样式、宽度和颜色创建画笔
	BOOL Create(int nPenStyle, int nWidth, COLORREF crColor);

	//根据指定的LOGPEN结构创建
	BOOL CreateIndirect(LOGPEN lPen);

	//创建一个扩展画笔（装饰或几何）
	/*	iPenStyle是画笔的类型。
		cWidth是画笔的宽度，当创建装饰画笔时宽度一定要设置为1。
		plbrush是画笔的属性。
		cStyle是后面自定义样式数组的个数。
		pstyle是自定义样式数组。
	*/
	BOOL CreateEx(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle);
public:

};
#endif