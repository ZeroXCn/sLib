#include "SDialog.h"
#include "SMessageBox.h"
SDialog::SDialog(SWidget *parent, LPTSTR lpName) :SWindow(parent)
{
	GetWindowAttribute()->nWidth = 480;
	GetWindowAttribute()->nHeight = 480;
	SetPosAtCenter();
	m_pButton = NULL;
	m_pLabel = NULL;
}

SDialog::~SDialog()
{
	delete m_pButton;
	delete m_pLabel;
}

//重定义类
BOOL SDialog::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	lpWndClassEx->lpszClassName = TEXT("sdialog");
	lpWinAttribute->lpClassName = GetWndClassEx()->lpszClassName;
	lpWinAttribute->lpWindowName = TEXT("Dialog");

	return TRUE;
}

BOOL SDialog::OnCreate(ActivityParam param)
{
	m_pButton = new SButton(this, TEXT("Buttom"));
	m_pButton->SetPos(GetWidth() - 150, GetHeight() - 100);
	m_pButton->OnClicked([=]{
		SMessageBox::About(param.hWnd, TEXT("Click"), TEXT("OK"));
	});
	m_pButton->Create();

	m_pLabel = new SLabel(this);
	m_pLabel->SetPos(40, 2*GetHeight() / 3);
	m_pLabel->Create();

	return TRUE;

}