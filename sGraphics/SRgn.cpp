#include "SRgn.h"


SRgn::SRgn(SGdiObj Obj)
{
	m_hGdiObj = (HRGN)Obj.GetHandle();
}
SRgn::SRgn(HRGN hRgn)
:SGdiHandle<HRGN, void*>(hRgn)
{

}
SRgn::~SRgn()
{

}



BOOL SRgn::CreateElliptic(int nLeft, int nTop, int nRight, int nBottom)
{
	m_hGdiObj = (HRGN) ::CreateEllipticRgn(nLeft, nTop, nRight, nBottom);
	return (m_hGdiObj ? TRUE : FALSE);
}


BOOL SRgn::CreateElliptieIndirect(RECT lRect)
{
	m_hGdiObj = (HRGN) ::CreateEllipticRgnIndirect(&lRect);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SRgn::CreatePolygon(POINT lPoints, int nCount, int nMode)
{
	m_hGdiObj = (HRGN) ::CreatePolygonRgn(&lPoints, nCount, nMode);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SRgn::CreateRect(int nLeft, int nTop, int nRight, int nBottom)
{
	m_hGdiObj = (HRGN) ::CreateRectRgn(nLeft, nTop, nRight, nBottom);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SRgn::CreateRectIndirect(RECT lRect)
{
	m_hGdiObj = (HRGN) ::CreateRectRgnIndirect(&lRect);
	return (m_hGdiObj ? TRUE : FALSE);
}

int SRgn::Combine(HRGN hrgnSrc1, HRGN hrgnSrc2, int nMode)
{
	return ::CombineRgn((HRGN)m_hGdiObj, hrgnSrc1, hrgnSrc2, nMode);
}