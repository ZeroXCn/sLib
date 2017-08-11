#include "SPalette.h"
SPalette::SPalette()
{

}

SPalette::SPalette(SGdiObject Obj)
{
	m_hGdiObj = (HPALETTE)Obj.GetHandle();
}

SPalette::SPalette(HPALETTE hPalette)
{
	m_hGdiObj = (HPALETTE)hPalette;
}
SPalette::~SPalette()
{

}

void SPalette::SetHandle(HPALETTE hPalette)
{
	m_hGdiObj = (HPALETTE)hPalette;
}
HPALETTE SPalette::GetHandle()
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