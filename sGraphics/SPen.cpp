#include "SPen.h"


SPen::SPen(SGdiObj Obj)
{
	m_hGdiObj = (HPEN)Obj.GetHandle();
}

SPen::SPen(HPEN hPen)
:SGdiHandle<HPEN, LOGPEN>(hPen)
{
	
}
SPen::~SPen()
{

}


//指定的样式、宽度和颜色创建画笔
BOOL SPen::Create(int nPenStyle, int nWidth, COLORREF crColor)
{
	m_hGdiObj = (HPEN) ::CreatePen(nPenStyle, nWidth, crColor);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SPen::CreateIndirect(LOGPEN lPen)
{
	m_hGdiObj = (HPEN) ::CreatePenIndirect(&lPen);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SPen::CreateEx(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle)
{
	m_hGdiObj = (HPEN) ::ExtCreatePen(iPenStyle, cWidth, plbrush, cStyle, pstyle);
	return (m_hGdiObj ? TRUE : FALSE);
}