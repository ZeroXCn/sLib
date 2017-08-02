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
	SetMenu((HMENU)DEFAULT_MENU_VALUE);	//应该自动分配ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));
}

SButton::~SButton()
{

}

BOOL SButton::OnPreCreate()
{
	return SWidget::Register(TEXT("button"),NULL);
}

LRESULT CALLBACK SButton::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//使用Lamdba表达式进行消息处理
	WORD command = HIWORD(wParam);
	switch (command)
	{
	case BN_CLICKED:
		m_fClicked();
		break;
	default:
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void SButton::OnClicked(function<void(void)> callback)
{
	m_fClicked = callback;
}