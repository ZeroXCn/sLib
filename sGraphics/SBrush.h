/**
* SBrush类
* GDI对象-画刷类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"
#ifndef _SBRUSH_H_
#define _SBRUSH_H_
class SBrush :public SGdiHandle<HBRUSH, LOGBRUSH>
{
public:
	SBrush(SGdiObj Obj);
	SBrush(HBRUSH hBrush=NULL);
	virtual ~SBrush();

public:
	//创建具有指定风格、颜色和模式的逻辑刷子
	BOOL CreateIndirect(LOGBRUSH lBrush);

	//指定阴影模式和颜色的逻辑刷子
	BOOL CreateHatch(int fnStyle, COLORREF clrref);

	//用一幅与设备无关的位图创建一个刷子，以便指定刷子样式（图案）
	BOOL CreateDIBPattern(HGLOBAL hglbDIBPacked,UINT fuColorSpec);

	//创建具有指定位图模式的逻辑刷子
	BOOL CreatePattern(HBITMAP hbmp);

	//创建一个具有指定颜色的逻辑刷子。
	BOOL CreateSolid(COLORREF clrref);

	//该刷子对应指定的颜色索引值。
	BOOL CreateSysColor(int nIndex);

public:

};

#endif;