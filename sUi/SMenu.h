/**
* SMenu��
* HMENU �����װ
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

	HMENU Create();				//�����²˵����
	HMENU CreatePopupMenu();	//���������˵�

	HMENU LoadMenu(LPTSTR lpMenuName, HINSTANCE hInstance = NULL);//���ز˵�
	HMENU LoadMenuIndirect(const MENUTEMPLATE *lpMenuTemplate);

	BOOL DestroyMenu();								//���ٲ˵����
	BOOL DeleteMenu(UINT  uPosition,UINT  uFlags);	//ɾ��һ���˵���
	BOOL RemoveMenu(UINT  uPosition, UINT  uFlags);	//ɾȥһ���˵�����������������Ĳ˵�
public:
	static BOOL Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags = MF_POPUP);	//����
	BOOL AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags);				//��������
	BOOL AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags);					//��������

	SMenu AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags = MF_STRING);		//�������
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);			//��Ӳ˵�
	SMenu InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition=0, UINT uFlags = MF_STRING);//
	SMenu InsertItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uPosition, UINT uFlags, std::function<void(SMenu)> fOperator);

	SMenu AddSeparator();															//���һ��ˮƽ�ָ��

	SMenu NewMenu(LPTSTR lpNewltem);
	SMenu NewMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator);			//�����˵���
	SMenu NewPopupMenu(LPTSTR lpNewltem);											//��������ʽ�˵�
	SMenu NewPopupMenu(LPTSTR lpNewltem, std::function<void(SMenu)> fOperator);
public:
	//�����˵�
	BOOL TrackPopupMenu(UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT* prcRect);

	//ȡ�ò˵�״̬
	UINT  GetMenuState(UINT uId, UINT uFlags);

	//ָ���Ĳ˵��ʹ���Ϊһ��Բ��ť��
	BOOL CheckMenuRadioItem(UINT idFirst, UINT idLast, UINT idCheck, UINT uFlags);
	//������ֹ����ָ���Ĳ˵���Ŀ
	BOOL EnableMenuItem(UINT uIDEnableItem, UINT wEnable);
	//�ڵ����˵���Ϊ�˵�������ѡ�б�ǻ��Ƴ�ѡ�б�Ǻʹ���һ��ˮƽ�ָ��ߵ�
	DWORD CheckMenuItem(UINT uIDCheckItem, UINT uCheck);

	//���úͻ�ȡ�˵�����Ϣ
	BOOL SetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);
	BOOL GetMenuItemInfo(UINT uItem, BOOL fByPosition, LPMENUITEMINFO lpmii);

	//��ȡ�˵�����
	int GetMenuItemCount();

	//��ȡ�˵���ID
	UINT GetMenuItemID(int nPos);

	//ȡ��һ������ʽ�˵�
	HMENU GetSubMenu(int nPos);

	//���úͻ�ȡȱʡ�˵���
	BOOL SetMenuDefaultItem(UINT uItem, UINT fByPos);
	UINT GetMenuDefaultItem(UINT fByPos,UINT gmdiFlags);

	//Ϊ�˵�������λͼ
	BOOL SetMenuItemBitmaps(UINT uPosition,UINT uFlags,HBITMAP hBitmapUnchecked,HBITMAP hBitmapChecked);

	//����Ƿ�Ϊ�˵�
	static BOOL IsMenu(HMENU hMenu);

	//��Ӳ˵�
	BOOL AppendMenu(UINT uFlags, UINT_PTR uIDNewItem, LPCTSTR  lpNewItem);

	//������
	BOOL InsertMenuItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii);

	//������
	BOOL InsertMenu(UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCTSTR  lpNewItem);

};


#endif