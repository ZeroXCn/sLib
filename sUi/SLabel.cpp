#include "SLabel.h"

SLabel::SLabel(SWidget *parent, LPTSTR name) :
SControl(parent)
{
	GetWindowAttribute()->lpClassName = TEXT("static");
	GetWindowAttribute()->lpWindowName = name;
	GetWindowAttribute()->dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT;
	GetWindowAttribute()->nPosX = 0; 
	GetWindowAttribute()->nPosY = 0;
	GetWindowAttribute()->nWidth = 100; 
	GetWindowAttribute()->nHeight = 100;
}
SLabel::~SLabel()
{

}
///
//����ȡ�ð�ť�ı�
void SLabel::SetText(SString str)
{
	SControl::SetTitle((LPTSTR)str.c_str());
}
SString SLabel::GetText()
{
	return SControl::GetTitle();
}
//

//�������ı���С
void SLabel::AdjustText()
{
	//TODO:���̫��
	//HFONT font = SWidget::GetFont();
	LPTSTR text = SWidget::GetTitle();
	SIZE size = GetDC().GetTextExtentPoint(text, _tcslen(text));
	SetWidth(size.cx);
	SetHeight(size.cy);
}