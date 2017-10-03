#include "SPalette.h"


SPalette::SPalette(SGdiObj Obj)
{
	m_hGdiObj = (HPALETTE)Obj.GetHandle();
}

SPalette::SPalette(HPALETTE hPalette)
:SGdiHandle<HPALETTE, LOGPALETTE>(hPalette)
{

}
SPalette::~SPalette()
{


}


BOOL SPalette::Create(LOGPALETTE lplgpl)
{
	m_hGdiObj = (HPALETTE) ::CreatePalette(&lplgpl);
	return (m_hGdiObj ? TRUE : FALSE);
}