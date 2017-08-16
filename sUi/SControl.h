/**
* SControl类
* 控件基类
* @author ZeroX
* @version v1.0 30/07/2017
*/
#include "SWidget.h"
#ifndef _SCONTROL_H_
#define _SCONTROL_H_

#define DEFAULT_MENU_VALUE g_nControlId

class SControl :public SWidget
{
protected:
	static unsigned int g_nControlId;			//记录控件ID的自增
protected:
	/* 父类公开函数隐藏 */
	using SWidget::GetTitle;
	using SWidget::SetTitle;
protected:
	SControl(SWidget *parent = NULL);
	virtual ~SControl();
protected:
	//创建成功前
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);
	//创建成功后
	virtual BOOL OnAftCreate(SWnd sWnd);
	//消息处理
	virtual LRESULT CALLBACK OnProc(MessageParam param);
};

#endif