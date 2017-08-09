/**
* SMessageHandler抽象类
* 消息处理程序,实现从普通函数到对象方法转换
*
* @author ZeroX 参考自colin<linzhenqun@gmail.com>
* @address http://blog.csdn.net/linzhengqun/article/details/6540366
* @version v1.0 21/07/2017
*/

#ifndef _SMESSAGEHANDLER_H_
#define _SMESSAGEHANDLER_H_

#include <Windows.h>
#include <hash_map>


//typedef LRESULT(CALLBACK *WNDPROC)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
class SMessageHandler
{
private:
	class wnd_hash
	{
	public:
		enum
		{
			bucket_size = 4,
			min_buckets = 8
		};
		wnd_hash()
		{
		}
		size_t operator()(const HWND& hwnd) const
		{
			return size_t(hwnd);
		}
		bool operator()(const HWND& hwnd1, const HWND& hwnd2) const
		{
			return   hwnd1 != hwnd2;
		}
	};
	class wnd_msg
	{
	public:
		HWND hWnd; UINT message; WPARAM wParam; LPARAM lParam;
	public:
		wnd_msg(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) :
			hWnd(hWnd), message(message), wParam(wParam), lParam(lParam){}
	};
	typedef std::hash_map<HWND, SMessageHandler *, wnd_hash> WndHandlerMap;

public:
	//普通函数
	static LRESULT CALLBACK MessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static WNDPROC GetMessageHandlerProc();

	static LRESULT CALLBACK ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
	static WndHandlerMap s_WndHandlerMap;		//记录全局父窗口消息的map
	WndHandlerMap m_ChildWndMap;				//记录某个父窗口下的子消息map
protected:
	WNDPROC m_pWndProc;

protected:
	//对象方法
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	SMessageHandler();
	virtual ~SMessageHandler();
public:
	//取得记录集
	WndHandlerMap *GetWndHandlerMap();

	//取得消息处理函数
	WNDPROC GetMessageProc();

	//设置消息处理函数
	void SetMessageProc(WNDPROC pWndProc);

	//改变消息处理函数
	WNDPROC ChangeMessageProv(HWND hWnd, WNDPROC pWndProc);

	//公开的消息处理回调函数
	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	/*以下操作适合父窗口*/
	//窗口子类化
	bool SubClass(HWND hwnd);

	//窗口反子类化
	void UnSubClass(HWND hwnd);
	void UnSubClass(SMessageHandler *handler);

	//添加子窗口
	bool SubChildClass(HWND hwnd, SMessageHandler *parent);

	//移除子窗口
	void UnSubChildClass(HWND hwnd, SMessageHandler *parent);
};

#endif