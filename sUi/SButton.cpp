#include "SButton.h"
using namespace std;


SButton::SButton(SWidget *parent, LPTSTR name) :
SControl(parent)
{
	SetTitle(name);
	SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	SetPos(0, 0);
	//���³�����밴���ı�Ҫ��
	SetWidth(100);
	SetHeight(20);

	//�ص���ʼ��
	m_fClicked = [=]{};
}

SButton::~SButton()
{

}

BOOL SButton::OnPreCreate()
{
	return SControl::Register(TEXT("button"), NULL);
}

LRESULT CALLBACK SButton::OnProc(MessageParam param)
{
	//ʹ��Lamdba���ʽ������Ϣ����
	WORD command = HIWORD(param.wParam);
	switch (command)
	{
	case BN_CLICKED:
		m_fClicked();
		OnClicked();
		break;
	default:
		return SControl::OnProc(param);
	}
	return 0;
}
////
void SButton::SetText(SString str)
{
	SControl::SetTitle((LPTSTR)str.c_str());
}
SString SButton::GetText()
{
	return SControl::GetTitle();
}



/////
void SButton::OnClicked(function<void(void)> callback)
{
	m_fClicked = callback;
}
void SButton::OnClicked()
{
}
