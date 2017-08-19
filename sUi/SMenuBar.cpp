#include "SMenuBar.h"

SMenuBar::SMenuBar(SWidget *parent, BOOL bPopupMenu) :
SControl(parent)
{
	m_fOnProc = [=](int){};
	if (bPopupMenu)SMenu::CreatePopupMenu();
	else SMenu::Create();
	if (parent && parent->GetMenu().GetHandle()){
		SubChildClass(SMenu::GetHandle(), (SMessageHandler *)parent);
	}
	
}

SMenuBar::SMenuBar(LPTSTR title, SMenuBar *sMenu, BOOL bPopupMenu)
{
	if (sMenu){
		if (bPopupMenu)SMenu::CreatePopupMenu();
		else SMenu::Create();
		SMenu::AddMenu(title, sMenu->GetHandle());
	}
}
SMenuBar::~SMenuBar()
{
	SMenu::DestroyMenu();
	if (GetParent()){
		UnSubChildClass(m_Wnd.GetHandle(), (SMessageHandler *)GetParent());
	}
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
///
BOOL SMenuBar::Create()
{
	if (GetParent()){
		//移除原菜单
		UnSubChildClass(GetParent()->GetMenu().GetHandle(), (SMessageHandler *)GetParent());
		GetParent()->SetMenu(SMenu::GetHandle());
		SubChildClass(SMenu::GetHandle(), (SMessageHandler *)GetParent());
		return TRUE;
	}
	return FALSE;
}

////
BOOL SMenuBar::TrackPopupMenu(SWnd sWnd,int x, int y, UINT uFlags, CONST RECT* prcRect , int nReserved )
{
	if (sWnd.GetHandle())
		return SMenu::TrackPopupMenu(uFlags, x, y, nReserved, sWnd.GetHandle(), prcRect);
	return FALSE;
}

BOOL SMenuBar::TrackPopupMenu(int x, int y, UINT uFlags, CONST RECT* prcRect , int nReserved)
{
	if (GetParent() && GetParent()->GetWnd().GetHandle())
		return SMenu::TrackPopupMenu(uFlags, x, y, nReserved, GetParent()->GetWnd().GetHandle(), prcRect);
	return FALSE;
}

