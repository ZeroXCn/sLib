#include "SCursor.h"

SCursor::SCursor(HCURSOR hCursor) :
SHandle(hCursor)
{
	
}
SCursor::~SCursor()
{

}


//����һ��ָ����С��λģʽ���ȵ�Ĺ��
BOOL SCursor::Create(HINSTANCE htnst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID *pvANDPlane, CONST VOID *pvXORPlane)
{
	m_handle = ::CreateCursor(htnst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
	return m_handle ? TRUE : FALSE;
}

//����Դ�м���λͼ
BOOL SCursor::Load(UINT uRcid, HINSTANCE hInstance)
{
	m_handle = ::LoadCursor(hInstance, MAKEINTRESOURCE(uRcid));
	return m_handle ? TRUE : FALSE;
}

//���ļ��м���λͼ
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
