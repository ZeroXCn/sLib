#include "SLabel.h"

SLabel::SLabel(SWidget *parent, LPTSTR name) :
SControl(parent)
{
	SetTitle(name);
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT );
	SetPos(0, 0);

	//���³�����밴���ı�Ҫ��
	SetWidth(100);
	SetHeight(100);


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


///
BOOL SLabel::OnPreCreate()
{
	return SControl::Register(TEXT("static"), NULL);
}

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