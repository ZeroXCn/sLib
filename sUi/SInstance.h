/**
* SInstance类
* HINSTANCE的封装类
* @author ZeroX
* @version v1.0 16/08/2017
*/
#ifndef _SINSTANCE_H_
#define _SINSTANCE_H_

#include <Windows.h>
class SInstance
{
protected:
	HINSTANCE m_hInstance;
public:
	SInstance();
	SInstance(HINSTANCE hInstance);
	virtual ~SInstance();
public:
	HINSTANCE GetHandle();
	void SetHandle(HINSTANCE hInstance);
};

#endif