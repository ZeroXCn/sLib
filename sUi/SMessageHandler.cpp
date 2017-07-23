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
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK SMessageHandler::MessageHandlerProc(HWND hWnd,		//���ھ��
	UINT message,		 	//��Ϣ��ʶ
	WPARAM wParam,		//��Ϣ����
	LPARAM lParam)		//��Ϣ����
{
	//NOTD:�������û���ҵ����뷵��DefWindowProc(),��������޷��ɹ���������
	
	WndHandlerMap::const_iterator itr = s_WndHandlerMap.find(hWnd);
	if (itr == s_WndHandlerMap.end())
		return DefWindowProc(hWnd, message, wParam, lParam);

	SMessageHandler* handler = itr->second;
	LRESULT done = handler->OnProc(hWnd, message, wParam, lParam);
	/*
	if (done)
		return done;
	else
		return CallWindowProc(DefWindowProc, hWnd, message, wParam, lParam);	//�������Ӵ���
		//NOTE:������仰������δ֪�쳣,������Ҳ�Ȳ�����(���˲²�����������ѭ��)
		return CallWindowProc(handler->GetMessageProc(), hWnd, message, wParam, lParam);	//�������Ӵ���

	*/
}
