#include "SMenu.h"

SMenu::SMenu()
{
	m_hMenu = NULL;
}

SMenu::~SMenu()
{
	/* 不会自动释放,由程序员自己判断释放 */
}

SMenu::SMenu(HMENU hMenu)
{
	SetHandle(hMenu);
}
HMENU SMenu::GetHandle()
{
	return m_hMenu;
}
void SMenu::SetHandle(HMENU hMenu)
{
	m_hMenu = hMenu;
}
//


HMENU SMenu::Create()
{
	m_hMenu = ::CreateMenu(); //创建菜单
	return m_hMenu;
}
void SMenu::Destroy()
{
	::DestroyMenu(m_hMenu);
}
///
BOOL SMenu::Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags)
{
	return ::AppendMenu(sParent.GetHandle(), uFlags, (unsigned int)sChild.GetHandle(), lpNewltem);
}
BOOL SMenu::AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags)
{
	return ::AppendMenu(m_hMenu, uFlags, uIDNewltem, lpNewltem);
}
BOOL SMenu::AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags)
{
	return ::AppendMenu(m_hMenu, uFlags, (unsigned int)sMenu.GetHandle(), lpNewltem);
}

SMenu SMenu::AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags)
{
	 
	::AppendMenu(m_hMenu, uFlags, uIDNewltem, lpNewltem);
	return *this;
}

SMenu SMenu::AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags)
{
	::AppendMenu(m_hMenu, MF_POPUP, (unsigned int)sMenu.GetHandle(), lpNewltem);
	return *this;
}


BOOL SMenu::InsertItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii)
{
	return ::InsertMenuItem(m_hMenu, ultem, fByPosition, lpmii);
}


SMenu SMenu::AddSeparator()
{
	::AppendMenu(m_hMenu, MF_SEPARATOR, NULL, NULL);
	return *this;
}
