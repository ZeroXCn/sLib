/**
* SWidget类
* 所有部件的基类
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SThread.h"
#include "../sGraphic/SDc.h"
#include "SWnd.h"
#include "SInstance.h"
#include "SApplication.h"
#include "SMessageHandler.h"
#ifndef _SWIDGET_H_
#define _SWIDGET_H_

#include <Windows.h>

//用于创建win的属性表
typedef struct tagWINATTRIBUTE
{
	LPCTSTR lpClassName;
	LPCTSTR lpWindowName;
	DWORD dwStyle;
	int nPosX;
	int nPosY;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;

	//附加项
	BOOL bEnabled;
	BOOL bVisible;

}WINATTRIBUTE, *LPWINATTRIBUTE;



class SWidget:
	public SObject,
	public SRunnable,
	public SMessageHandler
{
	friend class SApplication;
public:
	//注册一个类
	static ATOM SWidget::RegisterWidget(const WNDCLASSEX *wxClassEx);
	//创建一个窗口
	static HWND SWidget::CreateWidget(const WINATTRIBUTE *waWinAttribute);
protected:
	SWidget *m_pParent;				//父类控件
	
	SWnd m_Wnd;						//控件句柄
	SThread *m_pThread;				//线程

	/* 以下属性只提供临时使用,Create()完成后自动释放 */
	ATOM m_useClass;				//使用的类类型
	WNDCLASSEX *m_pWndClassEx;		//类属性
	WINATTRIBUTE *m_pWinAttribute;	//窗口属性

public:
	SWidget(SWidget *parent = NULL);
	SWidget(SWidget &obj);	//深拷贝
	virtual ~SWidget();
private:
	/* 私有操作 */
	void InitAttribute();
	BOOL DoPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute);
	BOOL DoAftCreate(SWnd sWnd);
public:
	/* 控件通用操作 */
	/* 属性表获取与设置 */
	LPWNDCLASSEX GetWndClassEx();
	LPWINATTRIBUTE GetWindowAttribute();
public:
	/* 部件的一些通用操作 */
	//获取设置控件父类
	SWidget *GetParent();

	//获取设置控件句柄
	SWnd GetWnd();

	//获取设备上下文
	SDc GetDC();
public:
	/* 属性设置-包括动态和静态更换 */
	/* 以下操作针对窗口-GWL_ */
	// 获取设置控件可用状态 
	BOOL IsEnabled();
	void SetEnabled(BOOL bEnabled);

	// 获取设置控件可见状态 
	BOOL IsVisible();
	void SetVisible(BOOL bVisible);

	void SetInstance(HINSTANCE hInstance);
	HINSTANCE GetInstance();

	//取得设置文本字体
	void SetFont(HFONT font);
	HFONT GetFont();

	// 设置控件标题 
	void SetTitle(LPTSTR szTitle);
	LPTSTR GetTitle(LPTSTR szTitle, int iCount);
	LPTSTR GetTitle();

	// 设置控件样式 
	void SetStyle(DWORD dwStyle);
	DWORD GetStyle();
	BOOL IsHaveStyle(DWORD dwStyle);

	// 获取设置控件位置 
	POINT GetPos();
	int GetPosX();
	int GetPosY();
	void SetPos(int x, int y);
	void SetPosAtCenter();//设置坐标为屏幕中心
	void MovePos(int x, int y);

	// 获取设置控件宽高 
	int GetWidth();
	int GetHeight();
	void SetWidth(int nWidth);
	void SetHeight(int nHeight);
	SIZE GetSize();

	//设置,获取菜单
	void SetMenu(HMENU hMenu);
	HMENU GetMenu();

	// 获取设置控件矩形 
	RECT GetRect();
	void SetRect(RECT rt);

	/* 以下操作针对类-会影响父类的子类类型 */
	/* WndClass属性变更-只支持静态GCL_ */
	//替换菜单名
	void SetMenuName(LPTSTR lpMenuName);
	LPTSTR GetMenuName();
	//设置大图标
	void SetBigIcon(HICON szIcon);
	HICON GetBigIcon();
	//设置小图标
	void SetSmallIcon(HICON szIcon);
	HICON GetSmallIcon();
	//设置鼠标指针
	void SetCursorIcon(HICON szIcon);
	HICON GetCursorIcon();
	//替换背景画刷
	void SetBkBr(HBRUSH hBr);
	HBRUSH GetBkBr();

public:
	/* 窗口是否创建*/
	BOOL IsCreated();

public:
	// 置顶窗口
	BOOL SetForegroundWindow();

	// 取得焦点
	HWND SetFocus();
public:
	//IMPORTMENT:对于从父类继承的同名函数,如果没有写重载方法,则不会从父类继承其他的重载方法,要么都不写
	//显示控件
	virtual void ShowWindow();
	virtual void ShowWindow(int nCmdShow);

	//隐藏控件
	virtual void HideWindow();

	//更新控件
	void UpdateWindow();
	void UpdateWindow(int left, int top, int right, int bottom);

	//重绘控件
	void ReDrawWindow();
protected:
	//IMPORTMENT:父类不能调用子类函数,必须将以下方法写成接口
	/*//IMPORTMENT:考虑到可设置静态消息回调函数,以下函数必须public,否则静态函数可能无法调用*/
	//消息回调函数
	virtual LRESULT CALLBACK OnProc(MessageParam param);

	//创建部件之前-用来标记控件类型
	virtual BOOL OnPreCreate(WNDCLASSEX *lpWndClassEx,WINATTRIBUTE *lpWinAttribute);

	//创建部件之后
	virtual BOOL OnAftCreate(SWnd sWnd);

	//线程主循环部分
	virtual void OnRun();

	//控件循环事件
	virtual void OnRunning();

	//控件退出事件
	virtual void OnRan();

public:
	//入口和线程入口
	virtual void Run() final;

	//创建控件
	virtual BOOL Create();

	//销毁控件
	virtual void Destroy() ;
	
	//模态显示
	virtual int DoModal();

	//非模态显示
	virtual void Show();

};

#endif