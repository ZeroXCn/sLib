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

protected:
	enum class QueryMethod
	{
		GET=1,
		PEEK=2,
	};
	class MessageParam
	{
		public:
			HWND hWnd;
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;
	public:
		MessageParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);
	public:

		WORD GetItemId();//取得控件ID
		WORD GetCode();	//取得通知码
		HWND GetChildHandle();	//子窗口句柄
	};
private:
	class handle_hash
	{
	public:
		enum
		{
			bucket_size = 4,
			min_buckets = 8
		};
		handle_hash();
		size_t operator()(const HANDLE& handle) const;
		bool operator()(const HANDLE& handle1, const HANDLE& handle2) const;
	};
	typedef std::hash_map<HANDLE, SMessageHandler *, handle_hash> HandleHandlerMap;
	typedef MessageParam handle_msg;
public:
	//普通函数
	static LRESULT CALLBACK MessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static WNDPROC GetMessageHandlerProc();

	static LRESULT CALLBACK ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
	static HandleHandlerMap s_WndHandlerMap;		//记录全局父窗口消息的map
	HandleHandlerMap m_ChildWndMap;					//记录某个父窗口下的子消息map
protected:
	WNDPROC m_pWndProc;								//消息函数				
	QueryMethod m_queryMethod;							//获取消息的方式
protected:
	//对象方法
	virtual LRESULT CALLBACK OnProc(MessageParam param);

protected:
	/* 只有继承本类才有效 */
	SMessageHandler();
	virtual ~SMessageHandler();

protected:
	//采用GET方式
	BOOL QueryMessage(LPMSG lpMsg,		// 检索到的消息
		HWND  hWnd,						// 窗口指向
		UINT  wMsgFilterMin,			// 消息范围的下界限参数
		UINT  wMsgFilterMax				// 上界限参数
		);
	//采用PEEK方式
	BOOL QueryMessage(LPMSG lpMsg,		// 检索到的消息
		HWND  hWnd,						// 窗口指向
		UINT  wMsgFilterMin,			// 消息范围的下界限参数
		UINT  wMsgFilterMax,			// 上界限参数
		UINT  wRemoveMsg				// 消息在被检索之后要如何处理
		);
public:
	//取得记录集
	HandleHandlerMap *GetWndHandlerMap();

	//取得消息处理函数
	WNDPROC GetMessageProc();

	//设置消息处理函数
	void SetMessageProc(WNDPROC pWndProc);

	//改变消息处理函数
	WNDPROC ChangeMessageProc(HWND hWnd, WNDPROC pWndProc);

	//公开的消息处理回调函数
	LRESULT CALLBACK Proc(MessageParam param);
	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	/*以下操作适合父窗口*/
	//窗口子类化
	bool SubClass(HWND hwnd);

	//窗口反子类化
	void UnSubClass(HWND hwnd);
	void UnSubClass(SMessageHandler *handler);

	//添加子窗口
	bool SubChildClass(HANDLE handle, SMessageHandler *parent);

	//移除子窗口
	void UnSubChildClass(HANDLE handle, SMessageHandler *parent);

	//取得设置消息获取方式
	void SetMessageQueryMethod(QueryMethod method);
	QueryMethod GetMessageQueryMethod();
public:
	/* 消息接口 */
	//进入消息循环
	virtual void OnMsgLoop();

	//空闲消息处理
	virtual void OnMsgLoopEvent();
};

#endif