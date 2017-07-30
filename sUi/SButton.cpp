#include "SButton.h"


SButton::SButton(SWidget *parent):
SWidget(parent)
{
	SetClassName(TEXT("button"));	//使用"button"类创建按钮
	SetTitle(TEXT("Button"));
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

BOOL SButton::Create()
{
	return SWidget::Create();

}

