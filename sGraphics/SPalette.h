/**
* SPalette类
* GDI对象-调色板类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"

#ifndef _SPALETTE_H_
#define _SPALETTE_H_
class SPalette :public SGdiHandle<HPALETTE, LOGPALETTE>
{
public:
	SPalette(SGdiObj Obj);
	SPalette(HPALETTE hPalette=NULL);
	virtual ~SPalette();
public:
	BOOL Create(LOGPALETTE lplgpl);
};

#endif