/**
* 窗口类头文件 SWindow.h
* 主要负责窗口的创建
* @author ZeroX
* @version v1.0 21/07/2017 
*/
#include "../sOS/SThread.h"
#include "SWidget.h"
#include "SWindowActivityEvent.h"
#include "SWindowInputEvent.h"

#ifndef _SWINDOWS_H_
#define _SWINDOWS_H_
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <set>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SWindow:
	public SWidget,
	public SWindowActivityEvent,
	public SWindowInputEvent
{
	static int s_winnum;					//设置一个用于记录窗口自增的参数
protected:

	BOOL		m_bFullScreen;				//是否全屏显示
	int			m_nColorbit;				//色彩模式（32位、24位或16位）

	
	SWindowInputEvent *m_pInputEvent;		//输入事件
	SWindowActivityEvent *m_pActivityEvent;	//活动事件

public:

	//声明空构造函数
	SWindow(SWidget *parent = NULL,LPTSTR name=TEXT("Window") );
	
	//声明虚析构函数，便于在派生类中进行扩展
	virtual ~SWindow();
public:
	//设置窗口属性
	void SetAttribute(
		LPTSTR szTitle,						//设置窗口标题
		HICON szIcon,						//设置图标（大）
		HICON szSmallIcon,					//设置图标（小）
		BOOL bFullScreen = FALSE,			//设置全屏，默认为FALSE
		int nColorbit = 32,					//设置色彩模式，默认为32位色
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素


	void SetAttribute(
		LPTSTR szTitle,					//设置窗口标题
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素
public:

	/* 设置全屏模式 */
	void SetFullScreen(BOOL bFullScreen);

	/* 设置色彩模式 */
	void SetColorbit(int nColorbit);

public:
	/* 显示鼠标 */
	int ShowCursor(BOOL bShow=TRUE);
	int HideCursor();

	/* 取得鼠标绝对位置 */
	POINT GetCursorPos();
	void SetCursorPos(POINT pt);

	/* 限制释放鼠标移动范围 */
	RECT GetClipCursor();
	void ClipCursor(const RECT *rt);
	void FreeCursor();

	//重绘消息
	void RePaint();
protected:

	//设置窗口活动
	void SetWindowInputEvent(SWindowInputEvent *pEvent);

	//设置窗口输入事件
	void SetWindowActivityEvent(SWindowActivityEvent *pEvent);

	//取得窗口活动
	SWindowInputEvent *GetWindowInputEvent();

	//取得窗口输入事件
	SWindowActivityEvent *GetWindowActivityEvent();

protected:
	/* 以下函数为接口重写函数 */

	//消息回调函数
	virtual LRESULT CALLBACK OnProc(MessageParam param);

	//部件创建之前
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);
	
	//部件创建中
	virtual BOOL OnCreate(MessageParam param) final;

	//部件创建之后
	virtual BOOL OnAftCreate(SWnd sWnd);

	//线程空闲运行执行函数
	virtual void OnRunning();

};
#endif
