#include "SWindowInputEvent.h"



SWindowInputEvent::InputParam::InputParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), message(message), wParam(wParam), lParam(lParam)
{

};

HWND &SWindowInputEvent::InputParam::GetWnd()
{
	return this->hWnd;
}
UINT &SWindowInputEvent::InputParam::GetMessage()
{
	return this->message;
}
WPARAM &SWindowInputEvent::InputParam::GetWParam()
{
	return this->wParam;
}
LPARAM &SWindowInputEvent::InputParam::GetLParam()
{
	return this->lParam;
}

void SWindowInputEvent::InputParam::SetWnd(HWND &hWnd)
{
	this->hWnd = hWnd;
}
void SWindowInputEvent::InputParam::SetMessage(UINT &message)
{
	this->message = message;
}
void SWindowInputEvent::InputParam::SetWParam(WPARAM &wParam)
{
	this->wParam = wParam;
}
void SWindowInputEvent::InputParam::SetLParam(LPARAM &lParam)
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