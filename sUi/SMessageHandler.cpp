#include "SMessageHandler.h"
using namespace std;

//记录对象消息函数的MAP
SMessageHandler::HandleHandlerMap SMessageHandler::s_WndHandlerMap;


/////



SMessageHandler::MessageParam::MessageParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), uMsg(message), wParam(wParam), lParam(lParam)
{

}


WORD SMessageHandler::MessageParam::GetItemId()
{
	return LOWORD(wParam);
}
WORD SMessageHandler::MessageParam::GetCode()
{
	return HIWORD(wParam);
}
HWND SMessageHandler::MessageParam::GetChildHandle()
{
	return reinterpret_cast<HWND>(lParam);
}

///
SMessageHandler::handle_hash::handle_hash()
{

}

size_t SMessageHandler::handle_hash::operator()(const HANDLE& handle) const
{
	return size_t(handle);
}

bool SMessageHandler::handle_hash::operator()(const HANDLE& handle1, const HANDLE& handle2) const
{
	return   handle1 != handle2;
}
///
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

SMessageHandler::HandleHandlerMap *SMessageHandler::GetWndHandlerMap()
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

WNDPROC SMessageHandler::ChangeMessageProc(HWND hWnd, WNDPROC pWndProc)
{
	UnSubClass(hWnd);
	SetMessageProc(pWndProc);
	SubClass(hWnd);
	return (WNDPROC)::SetWindowLongW(hWnd, GWL_WNDPROC, (long)pWndProc);
}

LRESULT CALLBACK SMessageHandler::Proc(MessageParam param)
{
	return OnProc(param);
}


LRESULT CALLBACK SMessageHandler::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return OnProc(MessageParam(hWnd, message, wParam, lParam));
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
			UnSubClass((HWND)it.first);
			break;
		}
	}
}

//添加子窗口
bool SMessageHandler::SubChildClass(HANDLE handle, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.insert(make_pair(handle, this));
		return true;
	}
	return false;
}

//移除子窗口
void SMessageHandler::UnSubChildClass(HANDLE handle, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.erase(handle);
	}
}

//默认处理
LRESULT CALLBACK SMessageHandler::OnProc(MessageParam param)
{
	//最后两个参数不能颠倒
	return ::DefWindowProc(param.hWnd, param.uMsg, param.wParam, param.lParam);
}

/////////////////
LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//窗口句柄
	UINT message,		 	//消息标识
	WPARAM wParam,		//消息参数
	LPARAM lParam)		//消息参数
{
	//NOTE:使用GetParent()无法判断自定义的子窗口,只能判断系统的默认子窗口
	//NOTE:使用SetParent()会对自定义子窗口造成影响,变成子控件
	HWND parent = ::GetParent(hWnd);
	if (parent == NULL){
		//TODO:还要判断是否只是一个控件,否则子窗口事件开线程让子窗口自行处理,模态窗口交由父窗口处理
		return SMessageHandler::ParentMessageHandlerProc(hWnd, message, wParam, lParam);
	}
	else{
		return SMessageHandler::ChildMessageHandlerProc(hWnd, message, wParam, lParam);
	}
}


LRESULT CALLBACK SMessageHandler::ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTD:这里如果没有找到必须返回DefWindowProc(),否则可能无法成功创建窗体
	SMessageHandler* handler = NULL;
	HandleHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:窗体未返回hWnd时的消息顺序WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		//TODO:拦截消息,使返回hWnd之前能正确执行到子类的回调函数

		/*以下内容有待修正,必须在此类中完成*/
		/* 必须在WM_CREATE之前将hWnd值赋给handler,否则无法从类中获取hWnd */

		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:应该判断以下指针属于那个对象的static_cast或dynamic_cast

			if (handler != NULL)
				return handler->OnProc(MessageParam(hWnd, message, wParam, lParam));
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		//取得特定对象
		handler = itr->second;
		//TODO:进行额外的消息拦截
		if (message == WM_COMMAND)
		{
			HandleHandlerMap *pChildMap = &handler->m_ChildWndMap;
			//NOTE:不管是系统还是自定义消息,都转到自身消息处理函数
			HandleHandlerMap::const_iterator itb;
			if (wParam == NULL){//自定义消息
				handle_msg *msg = reinterpret_cast<handle_msg *>(lParam);
				itb = pChildMap->find(msg->hWnd);
				if (itb != pChildMap->end()){
					return itb->second->OnProc(MessageParam(msg->hWnd, msg->uMsg, msg->wParam, msg->lParam));
				}
				delete msg;
			}else{//系统消息
				HANDLE childhWnd = reinterpret_cast<HANDLE>(lParam);
				if (childhWnd == NULL){
					//可能是菜单或者是快捷键
					if (HIWORD(wParam) == 0){//菜单
						childhWnd = ::GetMenu(hWnd);	//取得菜单
					}
					else{//快捷键

					}

				}
				//查找对应的子消息
				itb = pChildMap->find(childhWnd);
				if (itb != pChildMap->end()){
					itb->second->OnProc(MessageParam(hWnd, message, wParam, lParam));
				}
			}	
		}
		//最后任交由父窗口处理
		return handler->OnProc(MessageParam(hWnd, message, wParam, lParam));
	
	}

}

LRESULT CALLBACK SMessageHandler::ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTE:只有自定义消息,才会触发函数,系统消息不会触发
	//将原消息进行包装
	handle_msg *tempmsg = new handle_msg(hWnd, message, wParam, lParam);

	//转发到父亲的WM_COMMAND,在这里进行处理,wParam待定使用(可用于检测是否为自定义消息)
	//NOTE:应该自定义一个处理消息

	::SendMessage(::GetParent(hWnd), WM_COMMAND, (WPARAM)NULL, (LPARAM)tempmsg);

	return 0;
}
