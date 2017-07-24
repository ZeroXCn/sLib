#include "SWindowActivityEvent.h"

SWindowActivityEvent::SWindowActivityEvent()
{
	m_Graphics = new SGraphics();
}


SWindowActivityEvent::~SWindowActivityEvent()
{
	delete m_Graphics;
}
//////////////////////////////////
SGraphics *SWindowActivityEvent::GetGraphics()
{
	return m_Graphics;
}
void SWindowActivityEvent::SetGraphics(SGraphics *g)
{
	m_Graphics = g;
}
///////////////////////////////
//控件创建之前
BOOL SWindowActivityEvent::OnCreate()
{
	return TRUE;
}

//绘制绘制事件
void SWindowActivityEvent::OnPaint(SGraphics *g)
{
	//NOTE:不写BeginPaint程序将会进入死循环,一直处理一个接一个的WM_PAINT消息
	PAINTSTRUCT ps; //定义，无初始化,由BeginPaint初始化
	HDC Hdc = g->BeginPaint(&ps);
	//TODO:负责窗口绘制工作,并且绘制其下子控件


	g->EndPaint(&ps);
}

//关闭窗口
BOOL SWindowActivityEvent::OnClose(HWND hWnd)
{
	//DOUBT:这里的MessageBox无法正常显示,待解决
	
	if (MessageBox(hWnd, TEXT("你确定要退出吗？"), TEXT("退出程序"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
	return TRUE;
	else
	return FALSE;
	
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