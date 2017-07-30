#include "SWindowActivityEvent.h"


SWindowActivityEvent::Param::Param(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam):
hWnd(hWnd), message(message), wParam(wParam), lParam(lParam)
{
		
};

HWND &SWindowActivityEvent::Param::GetWnd()
{
	return this->hWnd;
}
UINT &SWindowActivityEvent::Param::GetMessage()
{
	return this->message;
}
WPARAM &SWindowActivityEvent::Param::GetWParam()
{
	return this->wParam;
}
LPARAM &SWindowActivityEvent::Param::GetLParam()
{
	return this->lParam;
}

void SWindowActivityEvent::Param::SetWnd(HWND &hWnd)
{
	this->hWnd = hWnd;
}
void SWindowActivityEvent::Param::SetMessage(UINT &message)
{
	this->message = message;
}
void SWindowActivityEvent::Param::SetWParam(WPARAM &wParam)
{
	this->wParam = wParam;
}
void SWindowActivityEvent::Param::SetLParam(LPARAM &lParam)
{
	this->lParam = lParam;
}

///////////////////////////////
//控件创建之前
BOOL SWindowActivityEvent::OnCreate(Param &param)
{
	return TRUE;
}

//绘制绘制事件
void SWindowActivityEvent::OnPaint(SDc dc)
{

}

//窗口空闲事件
void SWindowActivityEvent::OnEvent()
{

}

void SWindowActivityEvent::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

//关闭窗口
BOOL SWindowActivityEvent::OnClose(Param &param)
{
	//DOUBT:这里的MessageBox无法正常显示,待解决
	/*
	if (MessageBox(param.hWnd, TEXT("你确定要退出吗？"), TEXT("退出程序"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
		return FALSE;
	*/
	return TRUE;
}

//销毁窗口
void SWindowActivityEvent::OnDestory(Param &param)
{
	//TODO:做销毁前最后的操作
}

//取得窗口焦点
void SWindowActivityEvent::OnGetFocus(Param &param)
{

}

//失去焦点
void SWindowActivityEvent::OnLostFocus(Param &param)
{

}