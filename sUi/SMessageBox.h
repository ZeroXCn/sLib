/**
* SMessageBox类
* @brief 消息盒子
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
	SLabel *m_pLabel;			//提示条
	LPTSTR m_pContent;			//内容
	SButton *m_pButton;			//按钮
	int m_nReturn;				//返回值
public:
	SMessageBox(SWidget *parent, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_OK);
	virtual ~SMessageBox();
protected:
	//重定义类
	BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);

	//控件创建
	BOOL OnCreate(ActivityParam param);

	//设置返回值
	void SetValue(int nReturn);
	int GetValue();
public:
	int Exec();
};
#endif