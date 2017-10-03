/**
* SGdiObject类
* GDI物件抽象类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SGDIOBJ_H_
#define _SGDIOBJ_H_

#include <Windows.h>

class SGdiObj :public SObject
{
protected:
	HGDIOBJ m_hGdiObj;		//GDI抽象物件
public:
	SGdiObj(HGDIOBJ hGdiObj = NULL);
	virtual ~SGdiObj();

public:
	//取的封装内容
	HGDIOBJ GetHandle();
	void SetHandle(HGDIOBJ hGdiObj);
public:
	//释放所有与该对象有关的系统资源
	BOOL Delete();
};

#endif