/**
* SMenu类
* HMENU 句柄封装
* @author ZeroX
* @version v1.0 17/08/2017
*/
#include "SHandle.h"
#ifndef _SMENU_H_
#define _SMENU_H_
#include <Windows.h>
#include <functional>
class SMenu :public SHandle<HMENU>
{
public:
	SMenu(HMENU hMenu=NULL);
	SMenu(LPTSTR lpMenuName,SMenu *sMenu,BOOL bPopupMenu=FALSE);
	~SMenu();

	HMENU Create();				//创建新菜单句柄
	HMENU CreatePopupMenu();	//创建弹出菜单

	HMENU LoadMenu(LPTSTR lpMenuName, HINSTANCE hInstance = NULL);//加载菜单
	HMENU LoadMenuIndirect(const MENUTEMPLATE *lpMenuTemplate);

	BOOL DestroyMenu();								//销毁菜单句柄
	BOOL DeleteMenu(UINT  uPosition,UINT  uFlags);	//删除一个菜单项
	BOOL RemoveMenu(UINT  uPosition, UINT  uFlags);	//删去一个菜单项包括该项所弹出的菜单
public:
	static BOOL Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags = MF_POPUP);	//依附
	BOOL AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags);				//附加子项
	BOOL AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags);					//附加子项

	SMenu AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags = MF_STRING);		//添加子项
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);			//添加菜单
	SMenu InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition=0, UINT uFlags = MF_STRING);//
	SMenu InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition, UINT uFlags, std::function<void(SMenu)> fOperator);

	SMenu AddSeparator();															//添加一条水平分割符

	SMenu NewMenu(LPTSTR lpNewltem);
	SMenu NewMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator);			//创建菜单项
	SMenu NewPopupMenu(LPTSTR lpNewltem);											//创建弹出式菜单
	SMenu NewPopupMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator);
public:
	//弹出菜单
	BOOL TrackPopupMenu(UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT* prcRect);

	//取得菜单状态
	UINT  GetMenuState(UINT uId, UINT uFlags);

	//指定的菜单项并使其成为一个圆按钮项
	BOOL CheckMenuRadioItem(UINT idFirst, UINT idLast, UINT idCheck, UINT uFlags);
	//允许、禁止或变灰指定的菜单条目
	BOOL EnableMenuItem(UINT uIDEnableItem, UINT wEnable);
	//在弹出菜单中为菜单项增加选中标记或移除选中标记和创建一个水平分隔线等
	DWORD CheckMenuItem(UINT uIDCheckItem, UINT uCheck);

	//设置和获取菜单项信息
	BOOL SetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);
	BOOL GetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);

	//获取菜单项数
	int GetMenuItemCount();

	//获取菜单项ID
	UINT GetMenuItemID(int nPos);

	//取得一个弹出式菜单
	HMENU GetSubMenu(int nPos);

	//设置和获取缺省菜单项
	BOOL SetMenuDefaultItem(UINT uItem, UINT fByPos);
	UINT GetMenuDefaultItem(UINT fByPos,UINT gmdiFlags);

	//为菜单项设置位图
	BOOL SetMenuItemBitmaps(UINT uPosition,UINT uFlags,HBITMAP hBitmapUnchecked,HBITMAP hBitmapChecked);

	//句柄是否为菜单
	static BOOL IsMenu(HMENU hMenu);

	//添加菜单
	BOOL AppendMenu(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR  lpNewItem);

	//插入项
	BOOL InsertMenuItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii);

	//插入项
	BOOL InsertMenu(UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCTSTR  lpNewItem);

};


#endif