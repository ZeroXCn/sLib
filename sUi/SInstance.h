/**
* SInstance��
* HINSTANCE�ķ�װ��
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
	//���ع��
	HCURSOR LoadCursor(LPTSTR lpCursorName);
	HCURSOR LoadCursor(UINT uRcid);

	//����ͼ��
	HICON LoadIcon(LPTSTR lpIconName);
	HICON LoadIcon(UINT uRcid);

	//����ͼƬ
	HANDLE LoadImage(LPTSTR lpszName,UINT uType,int cxDesired,int cyDesired,UINT fuLoad);
	HANDLE LoadImage(UINT uRcid,UINT uType,int cxDesired,int cyDesired,UINT fuLoad);

	//���ز˵�
	HMENU LoadMenu(LPCTSTR lpMenuName);
	HMENU LoadMenu(UINT uRcid);
};

#endif