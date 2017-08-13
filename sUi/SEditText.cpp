#include"SEditText.h"
#include "../sCore/SDebug.h"
SEditText::SEditText(SWidget *parent, LPTSTR content) :
SControl(parent)
{
	SetTitle(content);			//默认内容
	SetStyle(WS_CHILD | WS_VISIBLE | WS_BORDER);
	SetPos(0, 0);

	//以下长宽必须按照文本要求
	SetWidth(180);
	SetHeight(24);

	m_fTextChanged = [=]{};
}
SEditText::~SEditText()
{

}
///////

BOOL SEditText::OnPreCreate()
{
	return SControl::Register(TEXT("edit"), NULL);
}

//消息处理
LRESULT CALLBACK SEditText::OnProc(MessageParam param)
{
	WORD command = HIWORD(param.wParam);
	SDebug::WriteLine(TEXT("%d"), command);
	switch (command)
	{
	case EN_CHANGE:
		OnTextChanged();
		m_fTextChanged();
		break;
	default:
		SControl::OnProc(param);
		break;
	}
	return 0;
}
///
//设置取得按钮文本
void SEditText::SetCurrentText(SString str)
{
	GetWnd().SendMessage(WM_SETTEXT, NULL, (LPARAM)str.c_str());
}
SString SEditText::GetCurrentText()
{
	TCHAR ret[256];
	GetWnd().SendMessage(WM_GETTEXT, 256, (LPARAM)ret);
	return ret;
}



//文本发生改变
void SEditText::OnTextChanged()
{

}


void SEditText::OnTextChanged(std::function<void(void)> callback)
{
	m_fTextChanged = callback;
}