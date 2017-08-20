#include "SMessageHandler.h"
using namespace std;

//��¼������Ϣ������MAP
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
	//�ͷ�������Դ
	UnSubClass(this);

}

SMessageHandler::HandleHandlerMap *SMessageHandler::GetWndHandlerMap()
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
			UnSubClass((HWND)it.first);
			break;
		}
	}
}

//����Ӵ���
bool SMessageHandler::SubChildClass(HANDLE handle, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.insert(make_pair(handle, this));
		return true;
	}
	return false;
}

//�Ƴ��Ӵ���
void SMessageHandler::UnSubChildClass(HANDLE handle, SMessageHandler *parent)
{
	if (parent){
		parent->m_ChildWndMap.erase(handle);
	}
}

//Ĭ�ϴ���
LRESULT CALLBACK SMessageHandler::OnProc(MessageParam param)
{
	//��������������ܵߵ�
	return ::DefWindowProc(param.hWnd, param.uMsg, param.wParam, param.lParam);
}

/////////////////
LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//���ھ��
	UINT message,		 	//��Ϣ��ʶ
	WPARAM wParam,		//��Ϣ����
	LPARAM lParam)		//��Ϣ����
{
	//NOTE:ʹ��GetParent()�޷��ж��Զ�����Ӵ���,ֻ���ж�ϵͳ��Ĭ���Ӵ���
	//NOTE:ʹ��SetParent()����Զ����Ӵ������Ӱ��,����ӿؼ�
	HWND parent = ::GetParent(hWnd);
	if (parent == NULL){
		//TODO:��Ҫ�ж��Ƿ�ֻ��һ���ؼ�,�����Ӵ����¼����߳����Ӵ������д���,ģ̬���ڽ��ɸ����ڴ���
		return SMessageHandler::ParentMessageHandlerProc(hWnd, message, wParam, lParam);
	}
	else{
		return SMessageHandler::ChildMessageHandlerProc(hWnd, message, wParam, lParam);
	}
}


LRESULT CALLBACK SMessageHandler::ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTD:�������û���ҵ����뷵��DefWindowProc(),��������޷��ɹ���������
	SMessageHandler* handler = NULL;
	HandleHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:����δ����hWndʱ����Ϣ˳��WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		//TODO:������Ϣ,ʹ����hWnd֮ǰ����ȷִ�е�����Ļص�����

		/*���������д�����,�����ڴ��������*/
		/* ������WM_CREATE֮ǰ��hWndֵ����handler,�����޷������л�ȡhWnd */

		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:Ӧ���ж�����ָ�������Ǹ������static_cast��dynamic_cast

			if (handler != NULL)
				return handler->OnProc(MessageParam(hWnd, message, wParam, lParam));
		}
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	}else{
		//ȡ���ض�����
		handler = itr->second;
		//TODO:���ж������Ϣ����
		if (message == WM_COMMAND)
		{
			HandleHandlerMap *pChildMap = &handler->m_ChildWndMap;
			//NOTE:������ϵͳ�����Զ�����Ϣ,��ת��������Ϣ������
			HandleHandlerMap::const_iterator itb;
			if (wParam == NULL){//�Զ�����Ϣ
				handle_msg *msg = reinterpret_cast<handle_msg *>(lParam);
				itb = pChildMap->find(msg->hWnd);
				if (itb != pChildMap->end()){
					return itb->second->OnProc(MessageParam(msg->hWnd, msg->uMsg, msg->wParam, msg->lParam));
				}
				delete msg;
			}else{//ϵͳ��Ϣ
				HANDLE childhWnd = reinterpret_cast<HANDLE>(lParam);
				if (childhWnd == NULL){
					//�����ǲ˵������ǿ�ݼ�
					if (HIWORD(wParam) == 0){//�˵�
						childhWnd = ::GetMenu(hWnd);	//ȡ�ò˵�
					}
					else{//��ݼ�

					}

				}
				//���Ҷ�Ӧ������Ϣ
				itb = pChildMap->find(childhWnd);
				if (itb != pChildMap->end()){
					itb->second->OnProc(MessageParam(hWnd, message, wParam, lParam));
				}
			}	
		}
		//����ν��ɸ����ڴ���
		return handler->OnProc(MessageParam(hWnd, message, wParam, lParam));
	
	}

}

LRESULT CALLBACK SMessageHandler::ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//NOTE:ֻ���Զ�����Ϣ,�Żᴥ������,ϵͳ��Ϣ���ᴥ��
	//��ԭ��Ϣ���а�װ
	handle_msg *tempmsg = new handle_msg(hWnd, message, wParam, lParam);

	//ת�������׵�WM_COMMAND,��������д���,wParam����ʹ��(�����ڼ���Ƿ�Ϊ�Զ�����Ϣ)
	//NOTE:Ӧ���Զ���һ��������Ϣ

	::SendMessage(::GetParent(hWnd), WM_COMMAND, (WPARAM)NULL, (LPARAM)tempmsg);

	return 0;
}
