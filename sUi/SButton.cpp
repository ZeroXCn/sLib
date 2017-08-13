#include "SButton.h"
using namespace std;


SButton::SButton(SWidget *parent, LPTSTR name) :
SControl(parent)
{
	SetTitle(name);
	SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	SetPos(0, 0);
	//以下长宽必须按照文本要求
	SetWidth(100);
	SetHeight(20);

	//回调初始化
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
	//使用Lamdba表达式进行消息处理
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
