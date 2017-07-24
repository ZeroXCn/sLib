#include "SLabel.h"

void SLabel::SetText(LPTSTR szText)
{
	lstrcpy(m_text, szText);
}
LPTSTR SLabel::GetText()
{
	return m_text;

}


void SLabel::SetFont(LOGFONT lFont)
{
	m_lFont = lFont;
}
LOGFONT SLabel::GetFont()
{
	return m_lFont;
}


void SLabel::SetTextColor(COLORREF crTextColor)
{
	m_crTextColor = crTextColor;
}
COLORREF SLabel::GetTextColor()
{
	return m_crTextColor;
}


BOOL SLabel::IsTrans()
{
	return m_bTrans;
}
void SLabel::SetTrans(BOOL bTrans)
{
	m_bTrans = bTrans;
}


void SLabel::SetBkColor(COLORREF crBackColor)
{
	m_crBackColor = crBackColor;

}
COLORREF SLabel::GetBkColor()
{
	return m_crBackColor;
}


void SLabel::SetMode(int nMode)
{
	m_nMode = nMode;
}
int SLabel::GetMode()
{
	return m_nMode;
}
////
BOOL SLabel::Create()
{
	SetClassName(TEXT("Label"));
	SetTitle(TEXT("Label"));
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER);
	SetPos(0, 0);
	SetWidth(0);
	SetHeight(0);

	return SWidget::Create();

}