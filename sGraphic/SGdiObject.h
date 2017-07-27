/**
* SGdiObject类
* GDI物件抽象类
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
	HGDIOBJ m_hGdiObj;		//GDI抽象物件
public:
	SGdiObject();
	SGdiObject(HGDIOBJ hGdiObj);
public:
	//取的封装内容
	HGDIOBJ Get();

	//到指定图形对象的信息
	int GetObject(int cbBuffer, LPVOID lpvObject);

	//释放所有与该对象有关的系统资源
	BOOL Delete();
};
#endif