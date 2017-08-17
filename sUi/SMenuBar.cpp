#include "SMenuBar.h"

SMenuBar::SMenuBar(SWidget *parent) :
SControl(parent)
{
	m_fOnProc = [=](int){};
	m_Menu.Create();
	if (parent)
		parent->SetMenu(m_Menu.GetHandle());
}

SMenuBar::SMenuBar(LPTSTR title, SMenuBar *sMenu)
{
	if (sMenu){
		m_Menu.Create();
		m_Menu.AddMenu(title, sMenu->m_Menu);
	}
}
SMenuBar::~SMenuBar()
{
	m_Menu.Destroy();
}

//
//消息处理
LRESULT CALLBACK SMenuBar::OnProc(MessageParam param)
{
	WORD Id = param.GetItemId();
	m_fOnProc(Id);
	return SControl::OnProc(param);
}

//
void SMenuBar::OnProc(std::function<void(int nID)> fOnProc)
{
	m_fOnProc = fOnProc;
}


SMenu SMenuBar::AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags)
{
	m_Menu.AddMenu(lpNewltem, sMenu, uFlags);
	return m_Menu;
}

SMenu SMenuBar::CreateMenu(LPTSTR lpNewltem)
{
	SMenu temp;
	temp.Create();
	AddMenu(lpNewltem, temp);
	return temp;
}



