/**
* SMessageBox��
* @brief ��Ϣ����
* @author ZeroX
* @version v1.0 30/07/2017
*/

#include "SDialog.h"
#include "SLabel.h"
#include "SButton.h"
#ifndef _SMESSAGEBOX_H_
#define _SMESSAGEBOX_H_
#include <Windows.h>

class SMessageBox :protected SDialog
{
public:
	static int Dialog(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons);
	static int Information(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_YESNO);
	static int Warning(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_YESNO);
	static int Critical(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_YESNO);
	static int Question(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_YESNO);
	static int About(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText);
protected:
	SLabel *m_pLabel;			//��ʾ��
	LPTSTR m_pContent;			//����
	SButton *m_pButton;			//��ť
	int m_nReturn;				//����ֵ
public:
	SMessageBox(SWidget *parent, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_OK);
	virtual ~SMessageBox();
protected:
	//�ض�����
	BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);

	//�ؼ�����
	BOOL OnCreate(ActivityParam param);

	//���÷���ֵ
	void SetValue(int nReturn);
	int GetValue();
public:
	int Exec();
};
#endif