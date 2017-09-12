/**
* SApplication类
* 作为Win32的应用程序入口和出口,并且处理一些全局事件
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SAPPLICATION_H_
#define _SAPPLICATION_H_

#include <Windows.h>
#include <set>

#include "SWidget.h"

class SApplication :public SObject
{
protected:
	static SApplication *g_pApp;			//单例模式
	static HINSTANCE	g_hInstance;				//当前程序实例句柄
	static HINSTANCE	g_hPrevInstance;			//父程序实例句柄
	static PSTR g_lpCmdline;						//启动的附加命令
	static int g_nCmdShow;							//启动模式

	std::set<SWidget *>	m_winset;				//窗口集合
public:
	static void SetParam(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);

	//取得窗口实例
	static HINSTANCE GetInstance();

	//取得父窗口实例
	static HINSTANCE GetPrevInstance();

	//取得启动命令行
	static PSTR GetCmdline();

	//取得显示模式命令行
	static int GetCmdShow();
public:
	SApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow);
	~SApplication();
public:

	//取得窗口集合
	std::set<SWidget *> *GetWidgetSet();

public:
	//注册窗体
	BOOL RegisterWidget(SWidget *pWidget);

	//反注册窗体
	BOOL UnRegisterWidget(SWidget *pWidget);

	//退出窗体
	void QuitWidget(SWidget *pWidget);

	//注销窗体
	void DestroyWidget(SWidget *pWidget);
public:
	//取得单例
	static SApplication *GetApp();

public:
	int Exec();
};

#endif