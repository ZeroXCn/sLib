/**
* SWidget类
* 所有控件的基类
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#ifndef _SWIDGET_H_
#define _SWIDGET_H_

#include <Windows.h>

class SWidget:public SObject
{
protected:
	SWidget *m_pParent;				//父类控件

	HWND m_hWnd;					//控件句柄
	HINSTANCE m_hInstance;			//当前控件实例句柄
	HMENU m_hMenu;					//菜单实例句柄
	LPVOID m_lpParam;				//传递给消息函数的参数指针

	TCHAR m_szClassName[64];		//控件类型名称
	TCHAR m_szTitle[128];			//控件标题名称
	DWORD m_dwStyle;				//声明控件风格变量

	int	m_nPosX, m_nPosY;			//控件位置
	int	m_nWidth, m_nHeight;		//控件宽度和高度
	BOOL m_bEnabled;				//控件是否可用
	BOOL m_bVisible;				//是否可见

	TCHAR m_szTip[64];				//提示
public:
	SWidget(SWidget *parent = NULL);
	virtual ~SWidget();

protected:
	/* 设置实例句柄 */
	void SetInstance(HINSTANCE hInstance);

	/* 设置控件句柄 */
	void SetWnd(HWND hWnd);

	/* 设置菜单句柄-或者是控件ID */
	void SetMenu(HMENU hMenu);

	/* 设置参数 */
	void SetParam(LPVOID lpParam);
public:
	//获取控件实例句柄
	HINSTANCE GetInstance();

	//获取控件句柄
	HWND GetWnd();

	//获取设备上下文
	HDC GetDC();

	/* 设置参数 */
	LPVOID GetParam();

	/* 设置控件类型名称 */
	void SetClassName(LPTSTR szClassName);
	LPTSTR(GetClassName)();

	/* 设置控件标题 */
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	/* 设置控件样式 */
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	
	/* 获取设置控件位置 */
	POINT GetPos();
	void SetPos(int x,int y);
	void SetPos(POINT pt);
	void MovePos(int x, int y);
	void MovePos(POINT pt);

	/* 获取设置控件宽高 */
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);

	/* 获取设置控件矩形 */
	RECT GetRect();
	void SetRect(RECT rt);

	/* 获取设置控件可用状态 */
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	/* 获取设置控件可见状态 */
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	/* 获取设置控件提示 */
	LPTSTR GetTip();
	void SetTip(LPTSTR str);
public:
	//IMPORTMENT:对于从父类继承的同名函数,如果没有写重载方法,则不会从父类继承其他的重载方法,要么都不写
	//显示控件
	virtual void Show();
	virtual void Show(int nCmdShow);

	//隐藏控件
	virtual void Hide();

	//更新控件
	void Update();
	void Update(int left, int top, int right, int bottom);

	//重绘控件
	void RePaint();

public:
	//创建控件
	virtual BOOL Create() ;

	//销毁控件
	virtual void Destroy() ;

};

#endif