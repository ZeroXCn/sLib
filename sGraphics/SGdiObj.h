/**
* SGdiObject��
* GDI���������
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
	HGDIOBJ m_hGdiObj;		//GDI�������
public:
	SGdiObj(HGDIOBJ hGdiObj = NULL);
	virtual ~SGdiObj();

public:
	//ȡ�ķ�װ����
	HGDIOBJ GetHandle();
	void SetHandle(HGDIOBJ hGdiObj);
public:
	//�ͷ�������ö����йص�ϵͳ��Դ
	BOOL Delete();
};

#endif