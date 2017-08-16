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

//指定虚拟键的状态的一个函数 > 0 没按下|< 0被按下
SHORT SWindowInputEvent::InputParam::GetKeyState(int nVirtKey)
{
	return ::GetKeyState(nVirtKey);
}

//确定用户当前是否按下了键盘上的一个键
//如键已被按过，则位0设为1；否则设为0
//如键目前处于按下状态，则位15设为1；如抬起，则为0。
SHORT SWindowInputEvent::InputParam::GetAsyncKeyState(int nVirtKey)
{
	return ::GetAsyncKeyState(nVirtKey);
}

//判断虚拟按键是否被按下
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
//键盘按下
void SWindowInputEvent::OnKeyDown(InputParam param)
{
	m_fKeyDown(param);
}
//键盘弹起
void SWindowInputEvent::OnKeyUp(InputParam param)
{
	m_fKeyUp(param);
}
//鼠标左键按下
void SWindowInputEvent::OnMouseLButtonDown(InputParam param)
{
	m_fMouseLButtonDown(param);
}
//鼠标左键弹起
void SWindowInputEvent::OnMouseLButtonUp(InputParam param)
{
	m_fMouseLButtonUp(param);
}
//鼠标滚轮
void SWindowInputEvent::OnMouseWheel(InputParam param)
{
	m_fMouseWheel(param);
}
//鼠标左键双击
void SWindowInputEvent::OnMouseDoubleClick(InputParam param)
{
	m_fMouseDoubleClick(param);
}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonDown(InputParam param)
{
	m_fMouseRButtonDown(param);
}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonUp(InputParam param)
{
	m_fMouseRButtonUp(param);
}
//鼠标移动
void SWindowInputEvent::OnMouseMove(InputParam param)
{
	m_fMouseMove(param);
}

//Lambda表达式/////////////////////////

//键盘按下
void SWindowInputEvent::OnKeyDown(std::function<void(InputParam)> fKeyDowm)
{
	m_fKeyDown = fKeyDowm;
}
//键盘弹起
void SWindowInputEvent::OnKeyUp(std::function<void(InputParam)> fKeyUp)
{
	m_fKeyUp = fKeyUp;
}
//鼠标左键按下
void SWindowInputEvent::OnMouseLButtonDown(std::function<void(InputParam)> fMouseLButtonDown)
{
	m_fMouseLButtonDown = fMouseLButtonDown;
}
//鼠标左键弹起
void SWindowInputEvent::OnMouseLButtonUp(std::function<void(InputParam)> fMouseLButtonUp)
{
	m_fMouseLButtonUp = fMouseLButtonUp;
}
//鼠标滚轮
void SWindowInputEvent::OnMouseWheel(std::function<void(InputParam)> fMouseWheel)
{
	m_fMouseWheel = fMouseWheel;
}
//鼠标左键双击
void SWindowInputEvent::OnMouseDoubleClick(std::function<void(InputParam)> fMouseDoubleClick)
{
	m_fMouseDoubleClick = fMouseDoubleClick;
}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonDown(std::function<void(InputParam)> fMouseRButtonDown)
{
	m_fMouseRButtonDown = fMouseRButtonDown;
}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonUp(std::function<void(InputParam)> fMouseRButtonUp)
{
	m_fMouseRButtonUp = fMouseRButtonUp;
}
//鼠标移动
void SWindowInputEvent::OnMouseMove(std::function<void(InputParam)> fMouseMove)
{
	m_fMouseMove = fMouseMove;
}