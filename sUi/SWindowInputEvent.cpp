#include "SWindowInputEvent.h"



SWindowInputEvent::InputParam::InputParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), uMsg(message), wParam(wParam), lParam(lParam)
{

};


int SWindowInputEvent::InputParam::GetMouseX()
{
	return LOWORD(lParam);
}
int SWindowInputEvent::InputParam::GetMouseY()
{
	return HIWORD(lParam);
}

//ָ���������״̬��һ������ > 0 û����|< 0������
SHORT SWindowInputEvent::InputParam::GetKeyState(int nVirtKey)
{
	return ::GetKeyState(nVirtKey);
}

//ȷ���û���ǰ�Ƿ����˼����ϵ�һ����
//����ѱ���������λ0��Ϊ1��������Ϊ0
//���Ŀǰ���ڰ���״̬����λ15��Ϊ1����̧����Ϊ0��
SHORT SWindowInputEvent::InputParam::GetAsyncKeyState(int nVirtKey)
{
	return ::GetAsyncKeyState(nVirtKey);
}

//�ж����ⰴ���Ƿ񱻰���
BOOL SWindowInputEvent::InputParam::GetKeyboardState(PBYTE lpKeyState)
{
	return ::GetKeyboardState(lpKeyState);
}

///////////////////////////////

//���̰���
void SWindowInputEvent::OnKeyDown(InputParam param)
{

}
//���̵���
void SWindowInputEvent::OnKeyUp(InputParam param)
{

}
//����������
void SWindowInputEvent::OnMouseLButtonDown(InputParam param)
{

}
//����������
void SWindowInputEvent::OnMouseLButtonUp(InputParam param)
{

}
//������
void SWindowInputEvent::OnMouseWheel(InputParam param)
{

}
//������˫��
void SWindowInputEvent::OnMouseDoubleClick(InputParam param)
{

}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonDown(InputParam param)
{

}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonUp(InputParam param)
{

}
//����ƶ�
void SWindowInputEvent::OnMouseMove(InputParam param)
{

}