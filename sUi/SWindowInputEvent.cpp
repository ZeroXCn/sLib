#include "SWindowInputEvent.h"



SWindowInputEvent::Param::Param(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), message(message), wParam(wParam), lParam(lParam)
{

};

HWND &SWindowInputEvent::Param::GetWnd()
{
	return this->hWnd;
}
UINT &SWindowInputEvent::Param::GetMessage()
{
	return this->message;
}
WPARAM &SWindowInputEvent::Param::GetWParam()
{
	return this->wParam;
}
LPARAM &SWindowInputEvent::Param::GetLParam()
{
	return this->lParam;
}

void SWindowInputEvent::Param::SetWnd(HWND &hWnd)
{
	this->hWnd = hWnd;
}
void SWindowInputEvent::Param::SetMessage(UINT &message)
{
	this->message = message;
}
void SWindowInputEvent::Param::SetWParam(WPARAM &wParam)
{
	this->wParam = wParam;
}
void SWindowInputEvent::Param::SetLParam(LPARAM &lParam)
{
	this->lParam = lParam;
}

///////////////////////////////

//�����
void SWindowInputEvent::OnKeyEvent()
{

}
//���̰���
void SWindowInputEvent::OnKeyDown(HWND hWnd, WPARAM wParam)
{

}
//���̵���
void SWindowInputEvent::OnKeyUp(HWND hWnd, WPARAM wParam)
{

}
//����������
void SWindowInputEvent::OnMouseLButtonDown(HWND hWnd, int x, int y, WPARAM wParam)
{

}
//����������
void SWindowInputEvent::OnMouseLButtonUp(HWND hWnd, int x, int y, WPARAM wParam)
{

}
//������
void SWindowInputEvent::OnMouseWheel(HWND hWnd, WPARAM wParam)
{

}
//������˫��
void SWindowInputEvent::OnMouseDoubleClick(HWND hWnd, int x, int y, WPARAM wParam)
{

}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonDown(HWND hWnd, int x, int y, WPARAM wParam)
{

}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonUp(HWND hWnd, int x, int y, WPARAM wParam)
{

}
//����ƶ�
void SWindowInputEvent::OnMouseMove(HWND hWnd, int x, int y, WPARAM wParam)
{

}