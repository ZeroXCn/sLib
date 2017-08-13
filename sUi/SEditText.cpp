#include"SEditText.h"
#include "../sCore/SDebug.h"
SEditText::SEditText(SWidget *parent, LPTSTR content) :
SControl(parent)
{
	SetTitle(content);			//Ĭ������
	SetStyle(WS_CHILD | WS_VISIBLE | WS_BORDER);
	SetPos(0, 0);

	//���³�����밴���ı�Ҫ��
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

//��Ϣ����
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
//����ȡ�ð�ť�ı�
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



//�ı������ı�
void SEditText::OnTextChanged()
{

}


void SEditText::OnTextChanged(std::function<void(void)> callback)
{
	m_fTextChanged = callback;
}