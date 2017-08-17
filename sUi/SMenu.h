/**
* SMenu类
* HMENU 句柄封装
* @author ZeroX
* @version v1.0 17/08/2017
*/
#include "../sCore/SObject.h"
#ifndef _SMENU_H_
#define _SMENU_H_
#include <Windows.h>

class SMenu :public SObject
{
protected:
	HMENU m_hMenu;			//菜单句柄
public:
	SMenu();
	SMenu(HMENU hMenu);
	~SMenu();

	HMENU GetHandle();
	void SetHandle(HMENU hMenu);

	HMENU Create();		//创建新菜单句柄
	void Destroy();		//销毁菜单句柄
public:
	static BOOL Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags = MF_POPUP);	//依附
	BOOL AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags);				//附加子项
	BOOL AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags);					//附加子项
	SMenu AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags = MF_STRING);		//添加子项
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);			//添加菜单
	BOOL InsertItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii);			//插入项

	SMenu AddSeparator();															//添加一条水平分割符

};


#endif