/**
* SWnd类
* HWND封装类
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SHandle.h"
#ifndef _SWND_H_
#define _SWND_H_
#include <Windows.h>

class SWnd :public SHandle<HWND>
{
public:
	SWnd(HWND hWnd=NULL);

	virtual ~SWnd();
public:
	//替换,获取指定窗口所属类的WNDCLASSEX结构
	DWORD SetClassLong(int nlndex, LONG dwNewLong);
	DWORD GetClassLong(int nlndex);

	//改变指定窗口的标题栏的文本内容
	BOOL SetWindowText(LPCTSTR lpString);

	//将指定窗口的标题条文本（如果存在）拷贝到一个缓存区内。
	int GetWindowText(LPTSTR lpString, int nMaxCount);

	//改变指定窗口的属性-用于改变回调函数-返回旧的回调函数
	LONG SetWindowLong(int nIndex,LONG dwNewLong);
	LONG GetWindowLong(int nIndex);


	//返回指定窗口的边框矩形的尺寸
	BOOL GetWindowRect(LPRECT lpRect);
	RECT GetWindowRect();

	//获取窗口客户区的大小。注意一下：窗口的客户区为窗口中除标题栏、菜单栏之外的地方
	BOOL GetClientRect(LPRECT lpRect);

	//屏幕坐标到客户区坐标的转换
	BOOL ScreenToClient(LPPOINT lpPoint);

	//矩形的用户坐标转换成屏幕坐标
	BOOL ClientToScreen(LPPOINT lpPoint);

	//改变子窗口、弹出窗口和顶层窗口的大小、位置和Z轴次序
	BOOL SetWindowPos(HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags);

	//改变指定窗口的位置和大小
	BOOL MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint);

	//将创建指定窗口的线程设置到前台，并且激活该窗口
	BOOL SetForegroundWindow();

	//对指定的窗口设置键盘焦点
	HWND SetFocus();

	//该函数设置指定窗口的显示状态
	BOOL ShowWindow(int nCmdShow);

	//向指定的窗体更新区域添加一个矩形，然后窗口客户区域的这一部分将被重新绘制
	BOOL InvalidateRect(CONST RECT *lpRect,BOOL bErase );

	//该函数更新指定窗口的无效矩形区域，使之有效。
	BOOL ValidateRect(CONST RECT *lpRect);
		
	//更新指定窗口的客户区
	BOOL UpdateWindow();

	//更新一个分层窗口的位置，大小，形状，内容和半透明度。
	BOOL UpdateLayeredWindow(HDC hdcDst,POINT *pptDst,SIZE *psize,HDC hdcSrc,POINT *pptSrc,COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	
	//设置分层窗口透明度，常和 UpdateLayeredWindow 函数结合使用
	BOOL SetLayeredWindowAttributes(COLORREF crKey,BYTE bAlpha,DWORD dwFlags);

	//根据fuRedraw旗标的设置，重画全部或部分窗口。
	BOOL RedrawWindow(CONST RECT* lprcUpdate, HRGN hrgnUpdate, UINT fuRedraw);

	//窗口的客户区域或整个屏幕的显示设备上下文环境的句柄-窗口客户区
	HDC GetDC();

	//返回hWnd参数所指定的窗口的设备环境--覆盖了整个窗口
	HDC GetWindowDC();

	//释放设备上下文环境（DC）供其他应用程序使用--与GetDC和GetWindowDC配合使用
	int ReleaseDC(HDC hdc);

	//为指定窗口进行绘图工作的准备
	HDC BeginPaint(LPPAINTSTRUCT lpPaint);

	//标记指定窗口的绘画过程结束
	BOOL EndPaint(CONST PAINTSTRUCT *lpPaint);

	//设置父窗口句柄。
	HWND SetParent(HWND parent);

	//获取父窗口句柄。
	HWND GetParent();

	//遍历子控件
	HWND GetDlgItem(int nIDDDlgItem);

	//将uValue的值设为对话框控件的文本
	BOOL SetDlgItemInt(int nIDDDlgItem, UINT uValue, BOOL bSigned);
	BOOL SetDlgItemText(int nIDDDlgItem, LPCTSTR IpString);

	//获取指定窗口的先祖窗口的句柄。
	HWND GetAncestor(UINT gaFlags);

	//允许/禁止指定的窗口或控件接受鼠标和键盘的输入
	BOOL EnableWindow(BOOL bEnable);

	//发送消息
	LRESULT SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam);

	//投递消息
	BOOL PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

	//枚举一个父窗口的所有子窗口。
	BOOL EnumChildWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);

	//窗口是否被隐藏
	BOOL IsWindowVisible();

	//设置新菜单
	BOOL SetMenu(HMENU hMenu);

	//取得菜单
	HMENU GetMenu();

	//允许应用程序为复制或修改而访问
	HMENU GetSystemMenu(BOOL bRevert);

	//获取菜单项的范围大小 
	BOOL GetMenuItemRect(HMENU  hMenu, UINT   uItem, LPRECT lprcItem);
	BOOL GetMenuItemRect(UINT   uItem, LPRECT lprcItem);

	//高亮显示菜单项
	BOOL HiliteMenuItem(HMENU hmenu,UINT  uItemHilite,UINT  uHilite);
	BOOL HiliteMenuItem(UINT  uItemHilite, UINT  uHilite);

	//获取某点除的菜单项
	int MenuItemFromPoint(HMENU hMenu,POINT ptScreen);
	int MenuItemFromPoint(POINT ptScreen);

	//定时器-
	UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse, TIMERPROC lpTimerFunc);//时器ID,时间间隔,回调函数
	BOOL KillTimer(UINT_PTR nIDEvent);

	//是否是最大化/最下化的窗口
	BOOL IsZoomed();
	BOOL IsIconic();
};
#endif