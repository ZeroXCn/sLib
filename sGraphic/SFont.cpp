#include "SFont.h"

SFont::SFont()
{

}

SFont::SFont(LOGFONT hFont)
{
	m_hGdiObj = (HFONT)::CreateFontIndirect(&hFont);
}