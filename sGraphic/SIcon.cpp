#include "SIcon.h"

SIcon::SIcon()
{
	m_hIcon = NULL;
}
SIcon::SIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}
SIcon::~SIcon()
{

}

void SIcon::SetIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}
HICON SIcon::GetIcon()
{
	return m_hIcon;
}


BOOL SIcon::Create(HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, const BYTE *lpbANDbits, const BYTE *lpbXORbits)
{
	m_hIcon = ::CreateIcon(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
	return m_hIcon ? TRUE : FALSE;
}

//从资源中加载位图
BOOL SIcon::Load(UINT uRcid, HINSTANCE hInstance )
{
	m_hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE(uRcid));
	return m_hIcon ? TRUE : FALSE;
}

//从文件中加载位图
BOOL SIcon::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	m_hIcon = ::LoadIcon(hInstance, lpFileName);
	return m_hIcon ? TRUE : FALSE;
}

//撤销图标
BOOL SIcon::Destroy()
{
	return ::DestroyIcon(m_hIcon);
}

BOOL SIcon::DrawIcon(HDC hDC, int x, int y)
{
	return ::DrawIcon(hDC, x, y, m_hIcon);
}
BOOL SIcon::DrawIconEx(HDC hdc, int x, int y, int nWidth, int nHeight, UINT istepifAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
	return ::DrawIconEx(hdc, x, y,  m_hIcon ,nWidth, nHeight, istepifAniCur, hbrFlickerFreeDraw, diFlags);
}