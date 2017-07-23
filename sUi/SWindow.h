/**
* 窗口类头文件 SWindow.h
* 主要负责窗口的创建
* @author ZeroX
* @version v1.0 21/07/2017 
*/
#include "../sCore/SThread.h"

#include "SApplication.h"
#include "SMessageHandler.h"
#include "SWidget.h"

#ifndef _SWINDOWS_H_
#define _SWINDOWS_H_
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <set>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SWindow:
	public SThread,
	public SWidget,
	public SMessageHandler
	
{
	friend class SApplication;
protected:
	static int s_winnum;						//设置一个用于记录窗口自增的参数
protected:

	WORD		m_wIcon;					//程序图标（大）
	WORD		m_wSmallIcon;				//程序图标（小）

	BOOL		m_bFullScreen;				//是否全屏显示
	int			m_nColorbit;				//色彩模式（32位、24位或16位）

	BOOL		m_bIsRunning;				//循环标记
protected:
	void Init();

public:
	//声明空构造函数
	SWindow(SWidget *parent=NULL);

	//最简单构造
	SWindow(LPTSTR szTitle);
	
	//声明虚析构函数，便于在派生类中进行扩展
	virtual ~SWindow();
public:
	//设置窗口属性
	void SetAttribute(HINSTANCE hInstance,				//设置程序实例句柄
		LPTSTR szWindowClass,			//设置窗口名称
		LPTSTR szTitle,					//设置窗口标题
		WORD wIcon,						//设置图标（大）
		WORD wSmallIcon,				//设置图标（小）
		BOOL bFullScreen = FALSE,			//设置全屏，默认为FALSE
		int nColorbit = 32,					//设置色彩模式，默认为32位色
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素

	void SetAttribute(
		LPTSTR szWindowClass,			//设置窗口名称
		LPTSTR szTitle,					//设置窗口标题
		WORD wIcon,					//设置图标（大）
		WORD wSmallIcon,				//设置图标（小）
		BOOL bFullScreen = FALSE,			//设置全屏，默认为FALSE
		int nColorbit = 32,					//设置色彩模式，默认为32位色
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素

	void SetAttribute(
		LPTSTR szWindowClass,			//设置窗口名称
		LPTSTR szTitle,					//设置窗口标题
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素


	void SetAttribute(
		LPTSTR szTitle,					//设置窗口标题
		int nWidth = 800,					//设置窗口宽度，默认为800像素
		int nHeight = 600);					//设置窗口高度，默认为600像素
public:
	/* 设置大图标 */
	void SetBigIcon(WORD wIcon);

	/* 设置小图标 */
	void SetSmallIcon(WORD wIcon);

	/* 设置鼠标指针*/
	long SetCursorIcon(WORD wIcon);

	/* 设置全屏模式 */
	void SetFullScreen(BOOL bFullScreen);

	/* 设置色彩模式 */
	void SetColorbit(int nColorbit);

	/* 设置消息处理函数 */
	void SetWndProc(WNDPROC pWndProc);

protected:
	//退出消息循环-相当于结束线程
	void SetRunning(BOOL bRunning);
public:
	virtual void DoModal();
	//显示控件
	virtual void Show();
	virtual void Show(int nCmdShow);

	//隐藏控件
	virtual void Hide();

protected:
	//IMPORTMENT:父类不能调用子类函数,必须将以下方法写成接口
	/*//IMPORTMENT:考虑到可设置静态消息回调函数,以下函数必须public,否则静态函数可能无法调用*/
	//消息回调函数
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//控件创建之前
	virtual BOOL OnCreate();

	//控件创建之后
	virtual BOOL OnCreated();

	//控件入口
	virtual void OnRun();

	//控件循环事件
	virtual void OnEvent();

	//绘制绘制事件
	virtual void OnPaint();

	//关闭窗口
	virtual BOOL OnClose();

	//销毁窗口
	virtual void OnDestory();

	//取得窗口焦点
	virtual void OnGetFocus();

	//失去焦点
	virtual void OnLostFocus();
public:

	//创建控件
	virtual BOOL Create();

	//销毁控件
	virtual void Destroy();

protected:
	//入口和线程入口
	virtual void Run() final;
	
};
#endif
