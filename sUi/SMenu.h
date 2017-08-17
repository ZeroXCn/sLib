/**
* SMenu��
* HMENU �����װ
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
	HMENU m_hMenu;			//�˵����
public:
	SMenu();
	SMenu(HMENU hMenu);
	~SMenu();

	HMENU GetHandle();
	void SetHandle(HMENU hMenu);

	HMENU Create();		//�����²˵����
	void Destroy();		//���ٲ˵����
public:
	static BOOL Append(SMenu sParent, LPTSTR lpNewltem, SMenu sChild, UINT uFlags = MF_POPUP);	//����
	BOOL AppendItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags);				//��������
	BOOL AppendItem(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags);					//��������
	SMenu AddItem(LPTSTR lpNewltem, UINT uIDNewltem, UINT uFlags = MF_STRING);		//�������
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);			//��Ӳ˵�
	BOOL InsertItem(UINT ultem, BOOL fByPosition, LPMENUITEMINFO lpmii);			//������

	SMenu AddSeparator();															//���һ��ˮƽ�ָ��

};


#endif