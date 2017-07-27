#include "SPalette.h"
SPalette::SPalette()
{

}

SPalette::SPalette(SGdiObject Obj)
{
	m_hGdiObj = (HPALETTE)Obj.Get();
}

SPalette::SPalette(HPALETTE hPalette)
{
	m_hGdiObj = (HPALETTE)hPalette;
}
SPalette::~SPalette()
{

}

void SPalette::SetPalette(HPALETTE hPalette)
{
	m_hGdiObj = (HPALETTE)hPalette;
}
HPALETTE SPalette::GetPalette()
{
	return (HPALETTE)m_hGdiObj;

}
LOGPALETTE SPalette::GetPaletteStruct()
{
	LOGPALETTE lpl;
	SGdiObject::GetObject(sizeof(LOGPALETTE), &lpl);
	return lpl;
}

BOOL SPalette::Create(LOGPALETTE lplgpl)
{
	m_hGdiObj = (HPALETTE) ::CreatePalette(&lplgpl);
	return (m_hGdiObj ? TRUE : FALSE);
}