/**
* SGdiObject��
* GDI���������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "../sCore/SObject.h"

#ifndef _SGDIOBJECT_H_
#define _SGDIOBJECT_H_
#include <Windows.h>

class SGdiObject :public SObject
{
protected:
	HGDIOBJ m_hGdiObj;		//GDI�������
public:
	SGdiObject();
	SGdiObject(HGDIOBJ hGdiObj);
public:
	virtual HGDIOBJ GetObject();
};
#endif