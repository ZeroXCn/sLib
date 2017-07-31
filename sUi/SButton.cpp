#include "SButton.h"


SButton::SButton(LPTSTR name, SWidget *parent) :
SWidget(parent)
{
	SetTitle(name);
	SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	SetPos(0, 0);
	SetWidth(100);
	SetHeight(20);

	SetParent(parent);
	SetMenu((HMENU)520);	//应该自动分配ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));
}

SButton::~SButton()
{

}

BOOL SButton::OnPreCreate()
{
	return SWidget::Register(TEXT("button"),NULL);
}


