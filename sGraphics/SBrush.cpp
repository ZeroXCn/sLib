#include "SBrush.h"



SBrush::SBrush(SGdiObj Obj)
{
	m_hGdiObj = (HBRUSH)Obj.GetHandle();;
}

SBrush::SBrush(HBRUSH hBrush)
:SGdiHandle<HBRUSH, LOGBRUSH>(hBrush)
{
	
}
SBrush::~SBrush()
{

}

//��������ָ�������ɫ��ģʽ���߼�ˢ��
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

