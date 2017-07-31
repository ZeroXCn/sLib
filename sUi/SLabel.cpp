#include "SLabel.h"

SLabel::SLabel(LPTSTR name , SWidget *parent) :
SWidget(parent)
{
	SetTitle(name);
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER);
	SetPos(0, 0);
	SetWidth(0);
	SetHeight(0);

	SetParent(parent);
	SetMenu((HMENU)520);	//应该自动分配ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));
}
SLabel::~SLabel()
{

}
BOOL SLabel::OnPreCreate()
{
	return SWidget::Register(TEXT("static"), NULL);
}