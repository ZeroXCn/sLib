/**
* SDialog��
* �Ի���ؼ�
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWindow.h"
#include "SLabel.h"
#include "SButton.h"

#ifndef _SDIALOG_H_
#define _SDIALOG_H_

class SDialog :public SWindow
{
protected:
	SLabel *m_pLabel;
	SButton *m_pButton;
public:
	SDialog(SWidget *parent = NULL,LPTSTR lpName=TEXT("Dialog"));
	virtual ~SDialog();
protected:
	//�ض�����
	BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);

	//�ؼ�����
	BOOL OnCreate(ActivityParam param);
};
#endif