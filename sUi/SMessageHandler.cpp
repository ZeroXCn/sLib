#include "SMessageHandler.h"
//��¼������Ϣ������MAP
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
	//�ͷ�������Դ
	UnSubClass(this);

}

SMessageHandler::WndHandlerMap *SMessageHandler::GetWndHandlerMap()
{
	return &s_WndHandlerMap;
}

//ȡ����Ϣ������
WNDPROC SMessageHandler::GetMessageProc()
{
	return m_pWndProc;
}

//������Ϣ������
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
	//˵���û��Զ�����Ϣ����
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
	//˵���û��Զ�����Ϣ����
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

//����Ӵ���
bool SMessageHandler::SubChildClass(HWND hwnd, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.insert(make_pair(hwnd, this));
		return true;
	}
	return false;
}

//�Ƴ��Ӵ���
void SMessageHandler::UnSubChildClass(HWND hwnd, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.erase(hwnd);
	}
}

//Ĭ�ϴ���
LRESULT CALLBACK SMessageHandler::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

/////////////////
LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//���ھ��
	UINT message,		 	//��Ϣ��ʶ
	WPARAM wParam,		//��Ϣ����
	LPARAM lParam)		//��Ϣ����
{
	//NOTE:ʹ��GetParent()�޷��ж��Զ�����Ӵ���,ֻ���ж�ϵͳ��Ĭ���Ӵ���
	HWND parent = ::GetParent(hWnd);
	if (parent == NULL){
		//TODO:��Ҫ�ж��Ƿ�ֻ��һ���ؼ�,�����Ӵ����¼����߳����Ӵ������д���,ģ̬���ڽ��ɸ����ڴ���
		return SMessageHandler::ParentMessageHandlerProc(hWnd, message, wParam, lParam);
	}
	else{
		//DOUBT:?�Ӵ���û��ִ�е�����??????
		return SMessageHandler::ChildMessageHandlerProc(hWnd, message, wParam, lParam);
	}
}


LRESULT CALLBACK SMessageHandler::ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTD:�������û���ҵ����뷵��DefWindowProc(),��������޷��ɹ���������

	SMessageHandler* handler = NULL;
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:����δ����hWndʱ����Ϣ˳��WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		//TODO:������Ϣ,ʹ����hWnd֮ǰ����ȷִ�е�����Ļص�����
		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:Ӧ���ж�����ָ�������Ǹ������static_cast��dynamic_cast

			if (handler != NULL)
				return handler->OnProc(hWnd, message, wParam, lParam);
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		//ȡ���ض�����
		handler = itr->second;
		//TODO:���ж������Ϣ����
		if (message == WM_COMMAND)
		{
			WndHandlerMap *pChildMap = &handler->m_ChildWndMap;
			//NOTE:������ϵͳ�����Զ�����Ϣ,��ת��������Ϣ������
			WndHandlerMap::const_iterator itb;
			if (wParam == NULL){//�Զ�����Ϣ
				wnd_msg *msg= reinterpret_cast<wnd_msg *>(lParam);
				itb = pChildMap->find(msg->hWnd);
				if (itb != pChildMap->end()){
					return itb->second->OnProc(msg->hWnd, msg->message, msg->wParam, msg->lParam);
				}
				delete msg;
			}else{//ϵͳ��Ϣ
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
	//NOTE:ֻ���Զ�����Ϣ,�Żᴥ������,ϵͳ��Ϣ���ᴥ��
	//��ԭ��Ϣ���а�װ
	wnd_msg *tempmsg = new wnd_msg(hWnd, message, wParam, lParam);

	//ת�������׵�WM_COMMAND,��������д���,wParam����ʹ��(�����ڼ���Ƿ�Ϊ�Զ�����Ϣ)
	//NOTE:Ӧ���Զ���һ��������Ϣ

	::SendMessage(::GetParent(hWnd), WM_COMMAND, (WPARAM)NULL, (LPARAM)tempmsg);

	return 0;
}
