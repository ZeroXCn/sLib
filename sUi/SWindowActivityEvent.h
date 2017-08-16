/**
* SWindowActivityEvent接口类
* 窗体活动消息
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sGraphic/SDc.h"
#ifndef _SWINDOWACTIVITYEVENT_H_
#define _SWINDOWACTIVITYEVENT_H_
#include <functional>
#include <Windows.h>
class SWindowActivityEvent
{
public:
	class ActivityParam
	{
	public:
		HWND hWnd;			//句柄
		UINT uMsg;		//消息
		WPARAM wParam;		//参数1
		LPARAM lParam;		//参数2
	public:
		ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);



	};
private:
	std::function<BOOL(ActivityParam)> m_fCreate;
	std::function<void(SDc)> m_fPaint;
	std::function<void()> m_fEvent;
	std::function<void(ActivityParam)> m_fCommand;
	std::function<BOOL(ActivityParam)> m_fClose;
	std::function<void(ActivityParam)> m_fDestory;
	std::function<void(ActivityParam)> m_fGetFocus;
	std::function<void(ActivityParam)> m_fLostFocus;
public:
	SWindowActivityEvent();
	virtual ~SWindowActivityEvent();
public:
	//以下消息必须给出默认的系统处理方法

	//控件创建之时
	virtual BOOL OnCreate(ActivityParam param);

	//绘制绘制事件
	virtual void OnPaint(SDc dc);

	//窗口空闲事件
	virtual void OnEvent();

	//处理子控件
	virtual void OnCommand(ActivityParam param);

	//关闭窗口
	virtual BOOL OnClose(ActivityParam param);

	//销毁窗口
	virtual void OnDestory(ActivityParam param);

	//取得窗口焦点
	virtual void OnGetFocus(ActivityParam param);

	//失去焦点
	virtual void OnLostFocus(ActivityParam param);

public:
	//控件创建之时
	void OnCreate(std::function<BOOL(ActivityParam)> fCreate);

	//绘制绘制事件
	void OnPaint(std::function<void(SDc)> fPaint);

	//窗口空闲事件
	void OnEvent(std::function<void()> fEvent);

	//处理子控件
	void OnCommand(std::function<void(ActivityParam)> fCommand);

	//关闭窗口
	void OnClose(std::function<BOOL(ActivityParam)> fClose);

	//销毁窗口
	void OnDestory(std::function<void(ActivityParam)> fDestory);

	//取得窗口焦点
	void OnGetFocus(std::function<void(ActivityParam)> fGetFocus);

	//失去焦点
	void OnLostFocus(std::function<void(ActivityParam)> fLostFocus);
};

#endif