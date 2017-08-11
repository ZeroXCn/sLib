/**
* SPalette类
* GDI对象-调色板类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SPALETTE_H_
#define _SPALETTE_H_
class SPalette :public SGdiObject
{
public:
	SPalette();
	SPalette(SGdiObject Obj);
	SPalette(HPALETTE hPalette);
	virtual ~SPalette();
public:
	void SetHandle(HPALETTE hPalette);
	HPALETTE GetHandle();
	LOGPALETTE GetPaletteStruct();
public:
	BOOL Create(LOGPALETTE lplgpl);
};

#endif