#include "SCursor.h"

SCursor::SCursor(HCURSOR hCursor) :
SHandle(hCursor)
{
	
}
SCursor::~SCursor()
{

}


//创建一个指定大小、位模式和热点的光标
BOOL SCursor::Create(HINSTANCE htnst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane)
{
	m_handle = ::CreateCursor(htnst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
	return m_handle ? TRUE : FALSE;
}

//从资源中加载位图
BOOL SCursor::Load(UINT uRcid, HINSTANCE hInstance)
{
	m_handle = ::LoadCursor(hInstance, MAKEINTRESOURCE(uRcid));
	return m_handle ? TRUE : FALSE;
}

//从文件中加载位图
BOOL SCursor::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	if (hInstance)
		m_handle = ::LoadCursor(hInstance, lpFileName);
	else
		m_handle = ::LoadCursorFromFile(lpFileName);
	return m_handle ? TRUE : FALSE;
}

BOOL SCursor::Destroy()
{
	return ::DestroyCursor(m_handle);
}
