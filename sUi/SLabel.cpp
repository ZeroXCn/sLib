#include "SLabel.h"

SLabel::SLabel(SWidget *parent):
SWidget(parent)
{
	SetClassName(TEXT("static"));	//�����ؼ��õ���
	SetTitle(TEXT("Label"));
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER);
	SetPos(0, 0);
	SetWidth(0);
	SetHeight(0);

	SetParent(parent);
	SetMenu((HMENU)520);	//Ӧ���Զ�����ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));
}
SLabel::~SLabel()
{

}

BOOL SLabel::Create()
{
	return SWidget::Create();

}