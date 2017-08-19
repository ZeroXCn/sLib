#include "SMenu.h"

SMenu::SMenu(HMENU hMenu) :
SHandle(hMenu)
{

}

SMenu::SMenu(LPTSTR lpMenuName, SMenu *sMenu, BOOL bPopupMenu)
{
	if (sMenu){
		if (bPopupMenu)SMenu::CreatePopupMenu();
		else SMenu::Create();
		SMenu::AddMenu(lpMenuName, sMenu->GetHandle());
	}
}

SMenu::~SMenu()
{
	/* �����Զ��ͷ�,�ɳ���Ա�Լ��ж��ͷ� */
}


///
HMENU SMenu::Create()
{
	SetHandle(::CreateMenu()); //�����˵�
	return GetHandle();
}

HMENU SMenu::CreatePopupMenu()
{
	SetHandle(::CreatePopupMenu()); //�����˵�
	return GetHandle();
}

//���ز˵�
HMENU SMenu::LoadMenu(LPTSTR lpMenuName, HINSTANCE hInstance)
{
	SetHandle(::LoadMenu(hInstance, lpMenuName));
	return GetHandle();
}

HMENU SMenu::LoadMenuIndirect(const MENUTEMPLATE *lpMenuTemplate)
{
	SetHandle(::LoadMenuIndirect(lpMenuTemplate));
	return GetHandle();
}

BOOL SMenu::DestroyMenu()
{
	return ::DestroyMenu(GetHandle());
}

BOOL SMenu::DeleteMenu(UINT  uPosition, UINT  uFlags)
{
	return ::DeleteMenu(GetHandle(), uPosition, uFlags);
}

BOOL SMenu::RemoveMenu(UINT  uPosition, UINT  uFlags)
{
	return ::RemoveMenu(GetHandle(), uPosition, uFlags);
}
///
BOOL SMenu::Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags)
{
	return ::AppendMenu(sParent.GetHandle(), uFlags, (unsigned int)sChild.GetHandle(), lpNewltem);
}
BOOL SMenu::AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags)
{
	return ::AppendMenu(GetHandle(), uFlags, uIDNewltem, lpNewltem);
}
BOOL SMenu::AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags)
{
	return ::AppendMenu(GetHandle(), uFlags, (unsigned int)sMenu.GetHandle(), lpNewltem);
}

SMenu SMenu::AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags)
{
	 
	::AppendMenu(GetHandle(), uFlags, uIDNewltem, lpNewltem);
	return *this;
}

SMenu SMenu::AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags)
{
	::AppendMenu(GetHandle(), MF_POPUP, (unsigned int)sMenu.GetHandle(), lpNewltem);
	return *this;
}

SMenu SMenu::InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition, UINT uFlags)
{
	::InsertMenu(GetHandle(), uPosition, uFlags, uIDNewltem, lpNewltem);
	return *this;
}

SMenu SMenu::InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition, UINT uFlags, std::function<void(SMenu)> fOperator)
{
	SMenu temp = InsertItem(lpNewltem, uIDNewltem, uPosition, uFlags);
	fOperator(temp);
	return temp;

}


SMenu SMenu::AddSeparator()
{
	::AppendMenu(GetHandle(), MF_SEPARATOR, NULL, NULL);
	return *this;
}

SMenu SMenu::NewMenu(LPTSTR lpNewltem)
{
	SMenu temp;
	temp.Create();
	AddMenu(lpNewltem, temp, MF_POPUP);
	return temp;
}
SMenu SMenu::NewMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator)
{
	SMenu temp = NewMenu(lpNewltem);
	fOperator(temp);
	return temp;
}

SMenu SMenu::NewPopupMenu(LPTSTR lpNewltem)
{
	SMenu temp;
	temp.CreatePopupMenu();
	AddMenu(lpNewltem, temp, MF_POPUP);
	return temp;
}
SMenu SMenu::NewPopupMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator)
{
	SMenu temp = NewPopupMenu(lpNewltem);
	fOperator(temp);
	return temp;
}

////

//�����˵�
BOOL SMenu::TrackPopupMenu(UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT* prcRect)
{
	return ::TrackPopupMenu(GetHandle(), uFlags, x, y, nReserved, hWnd, prcRect);
}

UINT  SMenu::GetMenuState(UINT uId, UINT uFlags)
{
	return ::GetMenuState(GetHandle(), uId, uFlags);
}

//ָ���Ĳ˵��ʹ���Ϊһ��Բ��ť��
BOOL SMenu::CheckMenuRadioItem(UINT idFirst, UINT idLast, UINT idCheck, UINT uFlags)
{
	return ::CheckMenuRadioItem(GetHandle(), idFirst, idLast, idCheck, uFlags);
}

BOOL SMenu::EnableMenuItem(UINT uIDEnableItem, UINT wEnable)
{
	return ::EnableMenuItem(GetHandle(), uIDEnableItem, wEnable);
}
//�ڵ����˵���Ϊ�˵�������ѡ�б�ǻ��Ƴ�ѡ�б�Ǻʹ���һ��ˮƽ�ָ��ߵ�
DWORD SMenu::CheckMenuItem(UINT uIDCheckItem, UINT uCheck)
{
	return ::CheckMenuItem(GetHandle(), uIDCheckItem, uCheck);
}

//���úͻ�ȡ�˵�����Ϣ
BOOL SMenu::SetMenuItemInfo(UINT uItem,BOOL fByPosition,LPMENUITEMINFO lpmii)
{
	return ::SetMenuItemInfo(GetHandle(), uItem, fByPosition, lpmii);
}
BOOL SMenu::GetMenuItemInfo(UINT uItem,BOOL fByPosition,LPMENUITEMINFO lpmii)
{
	return ::GetMenuItemInfo(GetHandle(), uItem, fByPosition, lpmii);
}

int SMenu::GetMenuItemCount()
{
	return ::GetMenuItemCount(GetHandle());
}

UINT SMenu::GetMenuItemID(int nPos)
{
	return ::GetMenuItemID(GetHandle(), nPos);
}

//ȡ��һ������ʽ�˵�
HMENU SMenu::GetSubMenu(int nPos)
{
	return ::GetSubMenu(GetHandle(), nPos);
}

BOOL SMenu::SetMenuDefaultItem(UINT uItem, UINT fByPos)
{
	return ::SetMenuDefaultItem(GetHandle(), uItem, fByPos);
}
UINT SMenu::GetMenuDefaultItem(UINT  fByPos, UINT  gmdiFlags)
{
	return ::GetMenuDefaultItem(GetHandle(), fByPos, gmdiFlags);
}

//Ϊ�˵�������λͼ
BOOL SMenu::SetMenuItemBitmaps(UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
{
	return ::SetMenuItemBitmaps(GetHandle(), uPosition, uFlags, hBitmapUnchecked, hBitmapChecked);
}

//����Ƿ�Ϊ�˵�
BOOL SMenu::IsMenu(HMENU hMenu)
{
	return ::IsMenu(hMenu);
}

BOOL SMenu::AppendMenu(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR  lpNewItem)
{
	return ::AppendMenu(GetHandle(), uFlags, uIDNewItem, lpNewItem);
}

BOOL SMenu::InsertMenuItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii)
{
	return ::InsertMenuItem(GetHandle(), ultem, fByPosition, lpmii);
}
BOOL SMenu::InsertMenu(UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR  lpNewItem)
{
	return ::InsertMenu(GetHandle(), uPosition, uFlags, uIDNewItem, lpNewItem);
}