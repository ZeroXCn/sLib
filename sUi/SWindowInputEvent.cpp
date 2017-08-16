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

/////////////////////////////////////////
SWindowInputEvent::SWindowInputEvent()
{
	
	m_fKeyDown = [](InputParam){};
	m_fKeyUp = [](InputParam){};
	m_fMouseLButtonDown = [](InputParam){};
	m_fMouseLButtonUp = [](InputParam){};
	m_fMouseWheel = [](InputParam){};
	m_fMouseDoubleClick = [](InputParam){};
	m_fMouseRButtonDown = [](InputParam){};
	m_fMouseRButtonUp = [](InputParam){};
	m_fMouseMove = [](InputParam){};
	
}
SWindowInputEvent::~SWindowInputEvent()
{

}

/////////////////////////////////////////
//���̰���
void SWindowInputEvent::OnKeyDown(InputParam param)
{
	m_fKeyDown(param);
}
//���̵���
void SWindowInputEvent::OnKeyUp(InputParam param)
{
	m_fKeyUp(param);
}
//����������
void SWindowInputEvent::OnMouseLButtonDown(InputParam param)
{
	m_fMouseLButtonDown(param);
}
//����������
void SWindowInputEvent::OnMouseLButtonUp(InputParam param)
{
	m_fMouseLButtonUp(param);
}
//������
void SWindowInputEvent::OnMouseWheel(InputParam param)
{
	m_fMouseWheel(param);
}
//������˫��
void SWindowInputEvent::OnMouseDoubleClick(InputParam param)
{
	m_fMouseDoubleClick(param);
}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonDown(InputParam param)
{
	m_fMouseRButtonDown(param);
}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonUp(InputParam param)
{
	m_fMouseRButtonUp(param);
}
//����ƶ�
void SWindowInputEvent::OnMouseMove(InputParam param)
{
	m_fMouseMove(param);
}

//Lambda���ʽ/////////////////////////

//���̰���
void SWindowInputEvent::OnKeyDown(std::function<void(InputParam)> fKeyDowm)
{
	m_fKeyDown = fKeyDowm;
}
//���̵���
void SWindowInputEvent::OnKeyUp(std::function<void(InputParam)> fKeyUp)
{
	m_fKeyUp = fKeyUp;
}
//����������
void SWindowInputEvent::OnMouseLButtonDown(std::function<void(InputParam)> fMouseLButtonDown)
{
	m_fMouseLButtonDown = fMouseLButtonDown;
}
//����������
void SWindowInputEvent::OnMouseLButtonUp(std::function<void(InputParam)> fMouseLButtonUp)
{
	m_fMouseLButtonUp = fMouseLButtonUp;
}
//������
void SWindowInputEvent::OnMouseWheel(std::function<void(InputParam)> fMouseWheel)
{
	m_fMouseWheel = fMouseWheel;
}
//������˫��
void SWindowInputEvent::OnMouseDoubleClick(std::function<void(InputParam)> fMouseDoubleClick)
{
	m_fMouseDoubleClick = fMouseDoubleClick;
}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonDown(std::function<void(InputParam)> fMouseRButtonDown)
{
	m_fMouseRButtonDown = fMouseRButtonDown;
}
//����Ҽ�����
void SWindowInputEvent::OnMouseRButtonUp(std::function<void(InputParam)> fMouseRButtonUp)
{
	m_fMouseRButtonUp = fMouseRButtonUp;
}
//����ƶ�
void SWindowInputEvent::OnMouseMove(std::function<void(InputParam)> fMouseMove)
{
	m_fMouseMove = fMouseMove;
}