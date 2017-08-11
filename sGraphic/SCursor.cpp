#include "SCursor.h"

SCursor::SCursor()
{
	m_hCursor = NULL;
}
SCursor::SCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}
SCursor::~SCursor()
{

}

void SCursor::SetHandle(HCURSOR hCursor)
{
	m_hCursor = hCursor;
}
HCURSOR SCursor::GetHandle()
{
	return m_hCursor;
}

	//创建一个指定大小、位模式和热点的光标
BOOL SCursor::Create(HINSTANCE htnst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane)
{
	m_hCursor = ::CreateCursor(htnst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
	return m_hCursor ? TRUE : FALSE;
}

	//从资源中加载位图
BOOL SCursor::Load(UINT uRcid, HINSTANCE hInstance)
{
	m_hCursor = ::LoadCursor(hInstance, MAKEINTRESOURCE(uRcid));
	return m_hCursor ? TRUE : FALSE;
}

	//从文件中加载位图
BOOL SCursor::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	if (hInstance)
		m_hCursor = ::LoadCursor(hInstance, lpFileName);
	else
		m_hCursor = ::LoadCursorFromFile(lpFileName);
	return m_hCursor ? TRUE : FALSE;
}

BOOL SCursor::Destroy()
{
	return ::DestroyCursor(m_hCursor);
}
