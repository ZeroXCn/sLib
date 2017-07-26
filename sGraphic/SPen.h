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
protected:
	LOGPEN m_sPen;
};
#endif