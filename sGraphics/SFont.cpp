#include "SFont.h"

SFont::SFont(SGdiObj Obj)
{
	m_hGdiObj = (HFONT)Obj.GetHandle();
}


SFont::SFont(HFONT hFont)
:SGdiHandle<HFONT, LOGFONT>(hFont)
{

}

SFont::~SFont()
{
	
}

/////////
//创建默认字体
BOOL SFont::Create()
{
	//计算公式::-MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72)
	return Create(
		0,
		0,
		0,
		0,
		0,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
		NULL
		);
}
//创建字体-字体,样式,大小
BOOL SFont::Create(int nHeight, LPCTSTR lpszFace, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut)
{
	//计算公式::-MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72)
	return Create(
		-nHeight,
		0,
		0,
		0,
		0,
		fdwItalic,
		fdwUnderline,
		fdwStrikeOut,
		ANSI_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
		lpszFace
		);
}

BOOL SFont::Create(int nHeight, 
	int nWidth, 
	int nEscapement,
	int nOrientation,
	int fnWeight, 
	DWORD fdwItalic, 
	DWORD fdwUnderline, 
	DWORD fdwStrikeOut, 
	DWORD fdwCharSet,
	DWORD fdwOutputPrecision, 
	DWORD fdwClipPrecision,
	DWORD fdwQuality, 
	DWORD fdwPitchAndFamily, 
	LPCTSTR lpszFace)
{
	m_hGdiObj = (HFONT)::CreateFont(nHeight,
									nWidth,
									nEscapement,
									nOrientation,
									fnWeight,
									fdwItalic,
									fdwUnderline,
									fdwStrikeOut,
									fdwCharSet,
									fdwOutputPrecision,
									fdwClipPrecision,
									fdwQuality,
									fdwPitchAndFamily,
									lpszFace
									);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SFont::CreateIndirect(LOGFONT lFont)
{
	m_hGdiObj = (HFONT)::CreateFontIndirect(&lFont);
	return (m_hGdiObj ? TRUE : FALSE);
}