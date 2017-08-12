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

///////////////////////////////

//键盘按下
void SWindowInputEvent::OnKeyDown(InputParam &param)
{

}
//键盘弹起
void SWindowInputEvent::OnKeyUp(InputParam &param)
{

}
//鼠标左键按下
void SWindowInputEvent::OnMouseLButtonDown(InputParam &param)
{

}
//鼠标左键弹起
void SWindowInputEvent::OnMouseLButtonUp(InputParam &param)
{

}
//鼠标滚轮
void SWindowInputEvent::OnMouseWheel(InputParam &param)
{

}
//鼠标左键双击
void SWindowInputEvent::OnMouseDoubleClick(InputParam &param)
{

}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonDown(InputParam &param)
{

}
//鼠标右键按下
void SWindowInputEvent::OnMouseRButtonUp(InputParam &param)
{

}
//鼠标移动
void SWindowInputEvent::OnMouseMove(InputParam &param)
{

}