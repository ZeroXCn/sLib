#include "SLayered.h"

BOOL SLayered::SetWindowExStyle(HWND hWnd)
{
	if (hWnd){
		::SetWindowLong(hWnd, GWL_EXSTYLE, ::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		return TRUE;
	}
	return FALSE;
}

BOOL SLayered::SetLayeredArrtibutes(HWND hWnd, COLORREF crKey, UINT cAlpha, BOOL dwFlags)
{
	return ::SetLayeredWindowAttributes(hWnd, crKey, cAlpha, dwFlags);
}

BOOL SLayered::UpdateLayeredWindow(HWND hWnd, HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	return ::UpdateLayeredWindow(hWnd,hDst, pptDst, psize, hSrc, pptSrc, crKey, pblend, dwFlags);

}

BOOL SLayered::TransWindow(HWND hWnd, COLORREF crKey, UINT cAlpha, BOOL dwFlags)
{
	bool ret = true;
	ret &= SetWindowExStyle(hWnd) ? true : false;
	ret &= SetLayeredArrtibutes(hWnd, crKey, cAlpha, dwFlags) ? true : false;
	return ret ? TRUE : FALSE;

}
/////
SLayered::SLayered(HWND hWnd) :m_hWnd(hWnd)
{
	m_dwColor = RGB(0,0,0);
	m_nAlpha = 255;
}
SLayered::~SLayered()
{

}
/////
void SLayered::SetAlpha(UINT nAlpha)
{
	m_nAlpha = nAlpha;
}
UINT SLayered::GetAlpha()
{
	return m_nAlpha;
}

void SLayered::SetColor(DWORD dwColor)
{
	m_dwColor = dwColor;
}
DWORD SLayered::GetAColor()
{
	return m_dwColor;
}
/////
//初始化
BOOL SLayered::Init(HWND hWnd)
{
	if (hWnd){
		m_hWnd = hWnd;
		return TRUE;
	}
	return FALSE;
}

//设置对像
BOOL SLayered::SetLayered(BOOL dwFlags,COLORREF crKey, UINT cAlpha)
{
	m_dwColor = crKey;
	m_nAlpha = cAlpha;
	return SLayered::SetLayeredArrtibutes(m_hWnd, m_dwColor, m_nAlpha, dwFlags);
}

BOOL SLayered::SetLayered(BOOL dwFlags, COLORREF crKey)
{
	return SetLayered(dwFlags, crKey, m_nAlpha);
}
BOOL SLayered::SetLayered(BOOL dwFlags, UINT cAlpha)
{
	return SetLayered(dwFlags, m_dwColor, cAlpha);
}
BOOL SLayered::SetLayered(BOOL dwFlags)
{
	return SetLayered(dwFlags, m_dwColor, m_nAlpha);
}
//更新层
BOOL SLayered::UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
{
	return SLayered::UpdateLayeredWindow(m_hWnd, hDst, pptDst, psize, hSrc, pptSrc, crKey, pblend, dwFlags);
}

BOOL SLayered::UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, DWORD dwFlags )
{
	BLENDFUNCTION blendFunction;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;
	blendFunction.BlendFlags = 0;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.SourceConstantAlpha = m_nAlpha;

	return UpdateLayered(hDst, pptDst, psize, hSrc, pptSrc, m_dwColor, &blendFunction, dwFlags);

}

BOOL SLayered::UpdateLayered(HDC hDst, POINT *pptDst, HDC hSrc, POINT *pptSrc, DWORD dwFlags )
{
	RECT rt;
	SIZE size;

	::GetWindowRect(m_hWnd, &rt);
	size.cx = rt.right - rt.left;
	size.cy = rt.bottom - rt.top;

	return UpdateLayered(hDst, pptDst, &size, hSrc, pptSrc,dwFlags);

}

BOOL SLayered::UpdateLayered(HDC hDst, HDC hSrc, DWORD dwFlags)
{

	POINT ptDest{ 0, 0 };
	POINT ptsrc{ 0, 0 };

	return UpdateLayered(hDst, &ptDest, hSrc, &ptsrc, dwFlags);

}

BOOL SLayered::UpdateLayered(HDC hSrc, DWORD dwFlags)
{
	BOOL ret;
	HDC hDestdc;
	HDC hSrcdc;

	hDestdc = ::GetDC(m_hWnd);
	hSrcdc = hSrc;
	
	ret = UpdateLayered(hDestdc, hSrcdc, dwFlags);
	::ReleaseDC(m_hWnd, hDestdc);
	return ret;


}