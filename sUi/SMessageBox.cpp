#include "SMessageBox.h"
int SMessageBox::Dialog(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, uButtons);
}

int SMessageBox::Information(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONINFORMATION | uButtons);
}
int SMessageBox::Warning(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONWARNING | uButtons);
}
int SMessageBox::Critical(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONSTOP | uButtons);
}

int SMessageBox::Question(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONQUESTION | uButtons);
}
int SMessageBox::About(SWnd sWnd, LPTSTR lpText, LPTSTR lpTitle)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_OK);
}
/////
SMessageBox::SMessageBox(SWidget *parent, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons) :
SDialog(parent)
{
	GetWndClassEx()->style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;	//没有关闭窗口的样式

	GetWindowAttribute()->dwStyle = WS_SYSMENU ;
	GetWindowAttribute()->nWidth = 400;
	GetWindowAttribute()->nHeight = 200;
	GetWindowAttribute()->lpWindowName = lpTitle;
	m_pContent = lpText;
	m_nReturn = 0;
	m_pButton = NULL;
	m_pLabel = NULL;
}
SMessageBox::~SMessageBox()
{
	delete m_pButton;
	delete m_pLabel;
}

//重定义类
BOOL SMessageBox::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	lpWndClassEx->lpszClassName = TEXT("smessagebox");
	lpWinAttribute->lpClassName = GetWndClassEx()->lpszClassName;

	return TRUE;
}

BOOL SMessageBox::OnCreate(ActivityParam param)
{
	m_pButton = new SButton(this, TEXT("Buttom"));
	m_pButton->SetPos(GetWidth() / 3, 2*GetHeight()/3);
	m_pButton->OnClicked([=]{
		SetValue(1);
		SDialog::Destroy();
	});
	m_pButton->Create();

	m_pLabel = new SLabel(this, m_pContent);
	m_pLabel->SetPos(GetWidth()/4, 40);
	m_pLabel->Create();

	return TRUE;

}
void SMessageBox::SetValue(int nReturn)
{
	m_nReturn = nReturn;
}
int SMessageBox::GetValue()
{
	return m_nReturn;
}

int SMessageBox::Exec()
{
	this->DoModal();
	return m_nReturn;
}