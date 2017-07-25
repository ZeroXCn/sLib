/**
* SWindowActivityEvent类
* 窗体活动消息
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sGraphic/SDc.h"
#include "SWnd.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_

#include <Windows.h>
class SWindowActivityEvent:public SObject
{
public:

	//以下消息必须给出默认的系统处理方法

	//控件创建之前
	virtual BOOL OnCreate();

	//绘制绘制事件
	virtual void OnPaint(SDc dc);

	//窗口空闲事件
	virtual void OnEvent();

	//关闭窗口
	virtual BOOL OnClose(HWND hWnd);

	//销毁窗口
	virtual void OnDestory();

	//取得窗口焦点
	virtual void OnGetFocus();

	//失去焦点
	virtual void OnLostFocus();
};

#endif