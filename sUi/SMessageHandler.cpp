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
	//释放所有资源
	UnSubClass(this);

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

WNDPROC SMessageHandler::ChangeMessageProv(HWND hWnd, WNDPROC pWndProc)
{
	UnSubClass(hWnd);
	SetMessageProc(pWndProc);
	SubClass(hWnd);
	return (WNDPROC)::SetWindowLongW(hWnd, GWL_WNDPROC, (long)pWndProc);
}
LRESULT CALLBACK SMessageHandler::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return OnProc(hWnd, message, wParam, lParam);
}


////
bool SMessageHandler::SubClass(HWND hwnd)
{
	//说明用户自定义消息函数
	if (m_pWndProc != SMessageHandler::GetMessageHandlerProc())
		return true;

	s_WndHandlerMap.erase(hwnd);
	m_pWndProc = MessageHandlerProc;
	::SetWindowLong(hwnd, GWL_WNDPROC, (long)GetMessageHandlerProc());
	
	s_WndHandlerMap.insert(make_pair(hwnd, this));
	return true;
}
void SMessageHandler::UnSubClass(HWND hwnd)
{
	//说明用户自定义消息函数
	if (m_pWndProc != SMessageHandler::GetMessageHandlerProc())
		return ;

	s_WndHandlerMap.erase(hwnd);
	if (!::IsWindow(hwnd) || !m_pWndProc)
		return;
	

	m_pWndProc = DefWindowProc;
	::SetWindowLong(hwnd, GWL_WNDPROC, (LONG)DefWindowProc);

}

void SMessageHandler::UnSubClass(SMessageHandler *handler)
{
	for (auto it : s_WndHandlerMap)
	{
		if (it.second == handler)
		{
			UnSubClass(it.first);
			break;
		}
	}
}

//添加子窗口
bool SMessageHandler::SubChildClass(HWND hwnd, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.insert(make_pair(hwnd, this));
		return true;
	}
	return false;
}

//移除子窗口
void SMessageHandler::UnSubChildClass(HWND hwnd, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.erase(hwnd);
	}
}

//默认处理
LRESULT CALLBACK SMessageHandler::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

/////////////////
LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//窗口句柄
	UINT message,		 	//消息标识
	WPARAM wParam,		//消息参数
	LPARAM lParam)		//消息参数
{
	//NOTE:使用GetParent()无法判断自定义的子窗口,只能判断系统的默认子窗口
	HWND parent = ::GetParent(hWnd);
	if (parent == NULL){
		//TODO:还要判断是否只是一个控件,否则子窗口事件开线程让子窗口自行处理,模态窗口交由父窗口处理
		return SMessageHandler::ParentMessageHandlerProc(hWnd, message, wParam, lParam);
	}
	else{
		//DOUBT:?子窗口没有执行到这里??????
		return SMessageHandler::ChildMessageHandlerProc(hWnd, message, wParam, lParam);
	}
}


LRESULT CALLBACK SMessageHandler::ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTD:这里如果没有找到必须返回DefWindowProc(),否则可能无法成功创建窗体

	SMessageHandler* handler = NULL;
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:窗体未返回hWnd时的消息顺序WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		//TODO:拦截消息,使返回hWnd之前能正确执行到子类的回调函数
		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:应该判断以下指针属于那个对象的static_cast或dynamic_cast

			if (handler != NULL)
				return handler->OnProc(hWnd, message, wParam, lParam);
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		//取得特定对象
		handler = itr->second;
		//TODO:进行额外的消息拦截
		if (message == WM_COMMAND)
		{
			WndHandlerMap *pChildMap = &handler->m_ChildWndMap;
			//NOTE:不管是系统还是自定义消息,都转到自身消息处理函数
			WndHandlerMap::const_iterator itb;
			if (wParam == NULL){//自定义消息
				wnd_msg *msg= reinterpret_cast<wnd_msg *>(lParam);
				itb = pChildMap->find(msg->hWnd);
				if (itb != pChildMap->end()){
					return itb->second->OnProc(msg->hWnd, msg->message, msg->wParam, msg->lParam);
				}
				delete msg;
			}else{//系统消息
				HWND childhWnd = reinterpret_cast<HWND>(lParam);
				itb = pChildMap->find(childhWnd);
				if (itb != pChildMap->end()){
					return itb->second->OnProc(hWnd, message, wParam, lParam);
				}
			}	
		}

		return handler->OnProc(hWnd, message, wParam, lParam);
	
	}

}

LRESULT CALLBACK SMessageHandler::ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTE:只有自定义消息,才会触发函数,系统消息不会触发
	//将原消息进行包装
	wnd_msg *tempmsg = new wnd_msg(hWnd, message, wParam, lParam);

	//转发到父亲的WM_COMMAND,在这里进行处理,wParam待定使用(可用于检测是否为自定义消息)
	//NOTE:应该自定义一个处理消息

	::SendMessage(::GetParent(hWnd), WM_COMMAND, (WPARAM)NULL, (LPARAM)tempmsg);

	return 0;
}
