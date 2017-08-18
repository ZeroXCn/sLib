/**
* SInstance类
* HINSTANCE的封装类
* @author ZeroX
* @version v1.0 16/08/2017
*/
#include "SHandle.h"

#ifndef _SINSTANCE_H_
#define _SINSTANCE_H_
#include <Windows.h>

class SInstance :public SHandle<HINSTANCE>
{
public:
	SInstance(HINSTANCE hInstance=NULL);
	virtual ~SInstance();
public:
	//加载光标
	HCURSOR LoadCursor(LPTSTR lpCursorName);
	HCURSOR LoadCursor(UINT uRcid);

	//加载图标
	HICON LoadIcon(LPTSTR lpIconName);
	HICON LoadIcon(UINT uRcid);

	//加载图片
	HANDLE LoadImage(LPTSTR lpszName,UINT uType,int cxDesired,int cyDesired,UINT fuLoad);
	HANDLE LoadImage(UINT uRcid,UINT uType,int cxDesired,int cyDesired,UINT fuLoad);

	//加载菜单
	HMENU LoadMenu(LPCTSTR lpMenuName);
	HMENU LoadMenu(UINT uRcid);
};

#endif