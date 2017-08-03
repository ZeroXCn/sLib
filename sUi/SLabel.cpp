#include "SLabel.h"

SLabel::SLabel(SWidget *parent, LPTSTR name) :
SWidget(parent)
{
	SetTitle(name);
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT );
	SetPos(0, 0);

	//以下长宽必须按照文本要求
	SetWidth(100);
	SetHeight(100);

	SetParent(parent);
	SetMenu((HMENU)DEFAULT_MENU_VALUE);	//应该自动分配ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));
}
SLabel::~SLabel()
{

}
///
//设置取得按钮文本
void SLabel::SetText(SString str)
{
	SWidget::SetTitle((LPTSTR)str.c_str());
}
SString SLabel::GetText()
{
	return SWidget::GetTitle();
}


///
BOOL SLabel::OnPreCreate()
{
	return SWidget::Register(TEXT("static"), NULL);
}

//调整到文本大小
void SLabel::AdjustText()
{
	//TODO:误差太大
	//HFONT font = SWidget::GetFont();
	LPTSTR text = SWidget::GetTitle();
	SIZE size = GetDC().GetTextExtentPoint(text, _tcslen(text));
	SetWidth(size.cx);
	SetHeight(size.cy);
}