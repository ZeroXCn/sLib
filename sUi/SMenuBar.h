/**
* SMenuBar��
* �˵��ؼ�
* @author ZeroX
* @version v1.0 17/08/2017
*/
#include "SControl.h"
#include "SMenu.h"
#ifndef _SMENUBAR_H_
#define _SMENUBAR_H_
#include <functional>
class SMenuBar :
	public SMenu,
	protected SControl
{
protected:
	std::function<void(int nID)> m_fOnProc;
public:
	SMenuBar(SWidget *parent);
	SMenuBar(LPTSTR title, SMenuBar *sMenu);
	virtual ~SMenuBar();

protected:
	//��Ϣ����
	virtual LRESULT CALLBACK OnProc(MessageParam param);
public:
	void OnProc(std::function<void(int nID)> fOnProc);
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);				//��Ӳ˵�

	SMenu NewMenu(LPTSTR lpNewltem);													//����һ���Ӳ˵�
	SMenu NewMenu(LPTSTR lpNewltem, std::function < void(SMenu) > fOperator);			//����һ���Ӳ˵�
	SMenu NewPopupMenu(LPTSTR lpNewltem);												//����һ���Ӳ˵�
	SMenu NewPopupMenu(LPTSTR lpNewltem, std::function < void(SMenu) > fOperator);		//����һ���Ӳ˵�

	using SControl::Proc;																//��������Ϣ����ӿ�
public:
	BOOL Create();																		//��������˵�
public:
	//�����˵�
	BOOL TrackPopupMenu(SWnd sWnd, int x, int y, UINT uFlags = TPM_LEFTALIGN, CONST RECT* prcRect = NULL, int nReserved = 0);
	BOOL TrackPopupMenu(int x, int y, UINT uFlags = TPM_LEFTALIGN, CONST RECT* prcRect = NULL, int nReserved = 0);


};

#endif