/**
* SFont类
* GDI对象-字体类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SFONT_H_
#define _SFONT_H_

#include <Windows.h>

class SFont :public SGdiObject
{
protected:
	LOGFONT m_sFont;			//字体结构体
public:
	SFont();
	SFont(LOGFONT lFont);
	virtual ~SFont();
public:
	
};

#endif;