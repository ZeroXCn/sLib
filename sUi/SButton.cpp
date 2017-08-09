#include "SButton.h"
using namespace std;


SButton::SButton(SWidget *parent,LPTSTR name) :
SWidget(parent)
{
	SetTitle(name);
	SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	SetPos(0, 0);
	//���³�����밴���ı�Ҫ��
	SetWidth(100);
	SetHeight(20);

	SetParent(parent);
	SetMenu((HMENU)DEFAULT_MENU_VALUE);	//Ӧ���Զ�����ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));

	//�ص���ʼ��
	m_fClicked = [=]{};
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
	//ʹ��Lamdba���ʽ������Ϣ����
	WORD command = HIWORD(wParam);
	switch (command)
	{
	case BN_CLICKED:
		m_fClicked();
		OnClicked();
		break;
	default:
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
////
void SButton::SetText(SString str)
{
	SWidget::SetTitle((LPTSTR)str.c_str());
}
SString SButton::GetText()
{
	return SWidget::GetTitle();
}



/////
void SButton::OnClicked(function<void(void)> callback)
{
	m_fClicked = callback;
}
void SButton::OnClicked()
{
}
