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
	SControl(SWidget *parent = NULL);
protected:
	//创建成功后
	virtual BOOL OnAftCreate(SWnd sWnd);
	//消息处理
	virtual LRESULT CALLBACK OnProc(MessageParam param);
};

#endif