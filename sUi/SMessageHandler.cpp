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


bool SMessageHandler::Subclass(HWND hwnd)
{
	//˵���û��Զ�����Ϣ����
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
	//˵���û��Զ�����Ϣ����
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

LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//���ھ��
	UINT message,		 	//��Ϣ��ʶ
	WPARAM wParam,		//��Ϣ����
	LPARAM lParam)		//��Ϣ����
{
	//NOTD:�������û���ҵ����뷵��DefWindowProc(),��������޷��ɹ���������

	SMessageHandler* handler = NULL;
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end()){
		//NOTE:����δ����hWndʱ����Ϣ˳��WM_GETMINMAXINFO,WM_NCCREATE,WM_NCCALCSIZE,WM_CREATE
		if (message == WM_NCCREATE || message == WM_CREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			handler = static_cast<SMessageHandler*>(lpcs->lpCreateParams);
			//TODO:Ӧ���ж�����ָ�������Ǹ������static_cast��dynamic_cast

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
