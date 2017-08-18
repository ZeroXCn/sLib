#include "SInstance.h"

SInstance::SInstance(HINSTANCE hInstance) :
SHandle(hInstance)
{
	
}
SInstance::~SInstance()
{

}

///
//���ع��
HCURSOR SInstance::LoadCursor(LPTSTR lpCursorName)
{
	return ::LoadCursor(GetHandle(), lpCursorName);
}

HCURSOR SInstance::LoadCursor(UINT uRcid)
{
	return ::LoadCursor(GetHandle(), MAKEINTRESOURCE(uRcid));
}
//����ͼ��
HICON SInstance::LoadIcon(LPTSTR lpIconName)
{
	return ::LoadIcon(GetHandle(), lpIconName);
}
HICON SInstance::LoadIcon(UINT uRcid)
{
	return ::LoadIcon(GetHandle(), MAKEINTRESOURCE(uRcid));
}

//����ͼƬ
HANDLE SInstance::LoadImage(LPTSTR lpszName,UINT uType,int cxDesired,int cyDesired,UINT fuLoad)
{
	return ::LoadImage(GetHandle(), lpszName, uType, cxDesired, cyDesired, fuLoad);
}

HANDLE SInstance::LoadImage(UINT uRcid, UINT uType, int cxDesired, int cyDesired, UINT fuLoad)
{
	return ::LoadImage(GetHandle(), MAKEINTRESOURCE(uRcid), uType, cxDesired, cyDesired, fuLoad);
}

HMENU SInstance::LoadMenu(LPCTSTR lpMenuName)
{
	return ::LoadMenu(GetHandle(), lpMenuName);
}
HMENU SInstance::LoadMenu(UINT uRcid)
{
	return ::LoadMenu(GetHandle(), MAKEINTRESOURCE(uRcid));
}