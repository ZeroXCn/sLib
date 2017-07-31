/**
* SWindowActivityEvent接口类
* 窗体活动消息
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sGraphic/SDc.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_

#include <Windows.h>
class SWindowActivityEvent
{
public:
	class ActivityParam
	{
	public:
		HWND &hWnd;			//句柄
		UINT &message;		//消息
		WPARAM &wParam;		//参数1
		LPARAM &lParam;		//参数2
	public:
		ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);
	public:
		HWND &GetWnd();
		UINT &GetMessage();
		WPARAM &GetWParam();
		LPARAM &GetLParam();

		void SetWnd(HWND &hWnd);
		void SetMessage(UINT &message);
		void SetWParam(WPARAM &wParam);
		void SetLParam(LPARAM &lParam);

	};
public:

	//以下消息必须给出默认的系统处理方法

	//控件创建之前
	virtual BOOL OnCreate(ActivityParam &param);

	//绘制绘制事件
	virtual void OnPaint(SDc dc);

	//窗口空闲事件
	virtual void OnEvent();

	//处理子控件
	virtual void OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//关闭窗口
	virtual BOOL OnClose(ActivityParam &param);

	//销毁窗口
	virtual void OnDestory(ActivityParam &param);

	//取得窗口焦点
	virtual void OnGetFocus(ActivityParam &param);

	//失去焦点
	virtual void OnLostFocus(ActivityParam &param);
};

#endif