#include "SButton.h"
using namespace std;


SButton::SButton(SWidget *parent, LPTSTR name) :
SControl(parent)
{
	GetWindowAttribute()->lpClassName = TEXT("button");
	GetWindowAttribute()->lpWindowName = name;
	GetWindowAttribute()->dwStyle = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON;
	GetWindowAttribute()->nPosX = 0; 
	GetWindowAttribute()->nPosY = 0;
	GetWindowAttribute()->nWidth = 100; 
	GetWindowAttribute()->nHeight = 20;

	//�ص���ʼ��
	m_fClicked = [=]{};
}

SButton::~SButton()
{

}


LRESULT CALLBACK SButton::OnProc(MessageParam param)
{
	//ʹ��Lamdba���ʽ������Ϣ����
	WORD command = param.GetCode();
	switch (command)
	{
	case BN_CLICKED:
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
	m_fClicked();
}
