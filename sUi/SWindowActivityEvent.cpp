#include "SWindowActivityEvent.h"


///////////////////////////////
//控件创建之前
BOOL SWindowActivityEvent::OnCreate()
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

//关闭窗口
BOOL SWindowActivityEvent::OnClose(HWND hWnd)
{
	//DOUBT:这里的MessageBox无法正常显示,待解决
	/*
	if (MessageBox(hWnd, TEXT("你确定要退出吗？"), TEXT("退出程序"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
		return FALSE;
	*/
	return TRUE;
}

//销毁窗口
void SWindowActivityEvent::OnDestory()
{
	//TODO:做销毁前最后的操作
}

//取得窗口焦点
void SWindowActivityEvent::OnGetFocus()
{

}

//失去焦点
void SWindowActivityEvent::OnLostFocus()
{

}