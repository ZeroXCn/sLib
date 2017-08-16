#include"SEditText.h"
#include "../sCore/SDebug.h"
SEditText::SEditText(SWidget *parent, LPTSTR content) :
SControl(parent)
{
	GetWindowAttribute()->lpClassName = TEXT("edit");
	GetWindowAttribute()->lpWindowName = content;
	GetWindowAttribute()->dwStyle = WS_CHILD | WS_VISIBLE | WS_BORDER;
	GetWindowAttribute()->nPosX = 0;
	GetWindowAttribute()->nPosY = 0;
	GetWindowAttribute()->nWidth = 180;
	GetWindowAttribute()->nHeight = 24;

	m_fTextChanged = [=]{};
}
SEditText::~SEditText()
{

}

//��Ϣ����
LRESULT CALLBACK SEditText::OnProc(MessageParam param)
{
	WORD command = HIWORD(param.wParam);
	SDebug::WriteLine(TEXT("%d"), command);
	switch (command)
	{
	case EN_CHANGE:
		OnTextChanged();
		break;
	default:
		SControl::OnProc(param);
		break;
	}
	return 0;
}
///
//����ȡ�ð�ť�ı�
void SEditText::SetCurrentText(SString str)
{
	GetWnd().SendMessage(WM_SETTEXT, NULL, (LPARAM)str.c_str());
}
SString SEditText::GetCurrentText()
{
	TCHAR ret[256] = { 0 };
	GetWnd().SendMessage(WM_GETTEXT, 256, (LPARAM)ret);
	return ret;
}



//�ı������ı�
void SEditText::OnTextChanged()
{
	m_fTextChanged();
}

void SEditText::OnTextChanged(std::function<void(void)> callback)
{
	m_fTextChanged = callback;
}

//����ֻ��
BOOL SEditText::IsReadOnly()
{
	return (BOOL)GetWnd().SendMessage(ES_READONLY, 0, 0);
}
void SEditText::SetReadOnly(BOOL bReadOnly)
{
	if (bReadOnly == TRUE)
		GetWnd().SendMessage(EM_SETREADONLY, 1, 0);
	else
		GetWnd().SendMessage(EM_SETREADONLY, 0, 0);
}