#include "SIcon.h"

SIcon::SIcon(HICON hIcon) :
SHandle(hIcon)
{

}
SIcon::~SIcon()
{

}


BOOL SIcon::Create(HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, const BYTE *lpbANDbits, const BYTE *lpbXORbits)
{
	m_handle = ::CreateIcon(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
	return m_handle ? TRUE : FALSE;
}

//����Դ�м���λͼ
BOOL SIcon::Load(UINT uRcid, HINSTANCE hInstance )
{
	m_handle = ::LoadIcon(hInstance, MAKEINTRESOURCE(uRcid));
	return m_handle ? TRUE : FALSE;
}

//���ļ��м���λͼ
BOOL SIcon::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	//m_handle = (HICON)::LoadImage(hInstance, lpFileName, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //���ؼ����Զ���icoͼ��
	m_handle = ::LoadIcon(hInstance, lpFileName);
	return m_handle ? TRUE : FALSE;
}

//����ͼ��
BOOL SIcon::Destroy()
{
	return ::DestroyIcon(m_handle);
}

BOOL SIcon::DrawIcon(HDC hDC, int x, int y)
{
	return ::DrawIcon(hDC, x, y, m_handle);
}
BOOL SIcon::DrawIconEx(HDC hdc, int x, int y, int nWidth, int nHeight, UINT istepifAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
	return ::DrawIconEx(hdc, x, y,  m_handle ,nWidth, nHeight, istepifAniCur, hbrFlickerFreeDraw, diFlags);
}