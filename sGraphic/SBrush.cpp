#include "SBrush.h"

SBrush::SBrush()
{

}

SBrush::SBrush(SGdiObject Obj)
{
	m_hGdiObj = (HBRUSH)Obj.Get();;
}

SBrush::SBrush(HBRUSH hBrush)
{
	m_hGdiObj = (HBRUSH)hBrush;
}
SBrush::~SBrush()
{

}


void SBrush::SetBrush(HBRUSH hBrush)
{
	m_hGdiObj = (HBRUSH)hBrush;
}

HBRUSH SBrush::GetBrush()
{
	return (HBRUSH)m_hGdiObj;
}

LOGBRUSH SBrush::GetBrushStruct()
{
	LOGBRUSH lb;
	SGdiObject::GetObject(sizeof(LOGBRUSH), &lb);
	return lb;
}

	//创建具有指定风格、颜色和模式的逻辑刷子
BOOL SBrush::CreateIndirect(LOGBRUSH lBrush)
{
	m_hGdiObj = (HBRUSH)::CreateBrushIndirect(&lBrush);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBrush::CreateHatch(int fnStyle, COLORREF clrref)
{
	m_hGdiObj = (HBRUSH)::CreateHatchBrush(fnStyle, clrref);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBrush::CreateDIBPattern(HGLOBAL hglbDIBPacked, UINT fuColorSpec)
{
	m_hGdiObj = (HBRUSH)::CreateDIBPatternBrush(hglbDIBPacked, fuColorSpec);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBrush::CreatePattern(HBITMAP hbmp)
{
	m_hGdiObj = (HBRUSH)::CreatePatternBrush(hbmp);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBrush::CreateSolid(COLORREF clrref)
{
	m_hGdiObj = (HBRUSH)::CreateSolidBrush(clrref);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBrush::CreateSysColor(int nIndex)
{
	m_hGdiObj = (HBRUSH)::GetSysColorBrush(nIndex);
	return (m_hGdiObj ? TRUE : FALSE);
}

