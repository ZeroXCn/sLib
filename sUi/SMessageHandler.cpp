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
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//窗口句柄
	UINT message,		 	//消息标识
	WPARAM wParam,		//消息参数
	LPARAM lParam)		//消息参数
{
	//NOTD:这里如果没有找到必须返回DefWindowProc(),否则可能无法成功创建窗体
	
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end())
		return DefWindowProc(hWnd, message, wParam, lParam);

	SMessageHandler* handler = itr->second;
	LRESULT done = handler->OnProc(hWnd, message, wParam, lParam);
	/*
	if (done)
		return done;
	else
		return CallWindowProc(DefWindowProc, hWnd, message, wParam, lParam);	//适用于子窗口
		//NOTE:以下这句话会引起未知异常,单步走也救不了你(个人猜测是引起了死循环)
		return CallWindowProc(handler->GetMessageProc(), hWnd, message, wParam, lParam);	//适用于子窗口

	*/
}
