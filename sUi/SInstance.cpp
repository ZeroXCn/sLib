#include "SInstance.h"

SInstance::SInstance(HINSTANCE hInstance) :
SHandle(hInstance)
{
	
}
SInstance::~SInstance()
{

}

///
//加载光标
HCURSOR SInstance::LoadCursor(LPTSTR lpCursorName)
{
	return ::LoadCursor(GetHandle(), lpCursorName);
}

HCURSOR SInstance::LoadCursor(UINT uRcid)
{
	return ::LoadCursor(GetHandle(), MAKEINTRESOURCE(uRcid));
}
//加载图标
HICON SInstance::LoadIcon(LPTSTR lpIconName)
{
	return ::LoadIcon(GetHandle(), lpIconName);
}
HICON SInstance::LoadIcon(UINT uRcid)
{
	return ::LoadIcon(GetHandle(), MAKEINTRESOURCE(uRcid));
}

//加载图片
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