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
class SMenuBar :protected SControl
{
protected:
	SMenu m_Menu;
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
	SMenu AddMenu(LPTSTR lpNewltem, SMenu sMenu, UINT uFlags = MF_POPUP);			//��Ӳ˵�

	SMenu CreateMenu(LPTSTR lpNewltem);												//����һ���Ӳ˵�
	using SControl::Proc;															//��������Ϣ����ӿ�

};

#endif