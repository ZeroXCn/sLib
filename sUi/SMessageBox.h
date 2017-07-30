/**
* 窗口类头文件 SWindow.h
* 主要负责窗口的创建
* @author ZeroX
* @version v1.0 30/07/2017
*/

#include "SDialog.h"
#include "SLabel.h"
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


public:
	SMessageBox(SDialog *parent, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons = MB_OK);
	virtual ~SMessageBox();
protected:
	void OnPaint(SDc dc);
public:
	int Exec();
};
#endif