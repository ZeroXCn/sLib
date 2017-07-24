#include "SMessageHandler.h"

//记录对象消息函数的MAP
SMessageHandler::WndHandlerMap SMessageHandler::s_WndHandlerMap;

WNDPROC SMessageHandler::GetMessageHandlerProc()
{
	return MessageHandlerProc;
}

SMessageHandler::SMessageHandler()
{
	m_pWndProc = GetMessageHandlerProc();
}
SMessageHandler::~SMessageHandler()
{
	
}

SMessageHandler::WndHandlerMap *SMessageHandler::GetWndHandlerMap()
{
	return &s_WndHandlerMap;
}

//取得消息处理函数
WNDPROC SMessageHandler::GetMessageProc()
{
	return m_pWndProc;
}

//设置消息处理函数
void SMessageHandler::SetMessageProc(WNDPROC pWndProc)
{
	m_pWndProc = pWndProc;
}


bool SMessageHandler::Subclass(HWND hwnd)
{
	//说明用户自定义消息函数
	if (m_pWndProc != SMessageHandler::MessageHandlerProc)
		return true;

	s_WndHandlerMap.erase(hwnd);
	m_pWndProc = MessageHandlerProc;
	::SetWindowLong(hwnd, GWL_WNDPROC, (long)MessageHandlerProc);
	
	s_WndHandlerMap.insert(make_pair(hwnd, this));
	return true;
}
void SMessageHandler::Unsubclass(HWND hwnd)
{
	//说明用户自定义消息函数
	if (m_pWndProc != SMessageHandler::MessageHandlerProc)
		return ;

	s_WndHandlerMap.erase(hwnd);
	if (!::IsWindow(hwnd) || !m_pWndProc)
		return;
	

	m_pWndProc = DefWindowProc;
	::SetWindowLong(hwnd, GWL_WNDPROC, (LONG)DefWindowProc);

}


LRESULT CALLBACK SMessageHandler::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//窗口句柄
	UINT message,		 	//消息标识
	WPARAM wParam,		//消息参数
	LPARAM lParam)		//消息参数
{
	//NOTD:这里如果没有找到必须返回DefWindowProc(),否则可能无法成功创建窗体

	SMessageHandler* handler = NULL;
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:窗体未返回hWnd时的消息顺序WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:应该判断以下指针属于那个对象的static_cast或dynamic_cast

			if (handler != NULL)
				return handler->OnProc(hWnd, message, wParam, lParam);
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	}
	else{
		handler = itr->second;
		return handler->OnProc(hWnd, message, wParam, lParam);
	}
	
}
