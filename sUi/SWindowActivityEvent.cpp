#include "SWindowActivityEvent.h"


SWindowActivityEvent::ActivityParam::ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), uMsg(message), wParam(wParam), lParam(lParam)
{


};

WORD SWindowActivityEvent::ActivityParam::GetItemId()
{
	return LOWORD(wParam);
}

WORD SWindowActivityEvent::ActivityParam::GetCode()
{
	return HIWORD(wParam);
}
HWND SWindowActivityEvent::ActivityParam::GetChildHandle()
{
	return reinterpret_cast<HWND>(lParam);
}
//取得客户区宽度
WORD SWindowActivityEvent::ActivityParam::GetClientWidth()
{
	return LOWORD(lParam);
}
//取得客户区高度
WORD SWindowActivityEvent::ActivityParam::GetClientHeight()
{
	return HIWORD(lParam);
}
///////////////////////////////
SWindowActivityEvent::SWindowActivityEvent()
{
	m_fCreate = [](ActivityParam){ return TRUE; };
	m_fPaint = [](SDc){};
	m_fEvent = [](){};
	m_fCommand = [](ActivityParam){};
	m_fSize = [](ActivityParam){};
	m_fClose = [](ActivityParam){
		/*
		if (MessageBox(param.hWnd, TEXT("你确定要退出吗？"), TEXT("退出程序"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
		else
		return FALSE;
		*/
		return TRUE; };
	m_fDestory = [](ActivityParam){};
	m_fGetFocus = [](ActivityParam){};
	m_fLostFocus = [](ActivityParam){};
}
SWindowActivityEvent::~SWindowActivityEvent()
{

}

///////////////////////////////
//控件创建之前
BOOL SWindowActivityEvent::OnCreate(ActivityParam param)
{
	return m_fCreate(param);
}

//绘制绘制事件
void SWindowActivityEvent::OnPaint(SDc dc)
{
	m_fPaint(dc);
}

//窗口空闲事件
void SWindowActivityEvent::OnEvent()
{
	m_fEvent();
}
//处理子窗口命令
void SWindowActivityEvent::OnCommand(ActivityParam param)
{
	m_fCommand(param);
}

void SWindowActivityEvent::OnSize(ActivityParam param)
{
	m_fSize(param);
}

//关闭窗口
BOOL SWindowActivityEvent::OnClose(ActivityParam param)
{
	return m_fClose(param);
}

//销毁窗口
void SWindowActivityEvent::OnDestory(ActivityParam param)
{
	//TODO:做销毁前最后的操作
	m_fDestory(param);
}

//取得窗口焦点
void SWindowActivityEvent::OnGetFocus(ActivityParam param)
{
	m_fGetFocus(param);
}

//失去焦点
void SWindowActivityEvent::OnLostFocus(ActivityParam param)
{
	m_fLostFocus(param);
}

//Lambda表达式//////////////////////////////////////
//控件创建之时
void SWindowActivityEvent::OnCreate(std::function<BOOL(ActivityParam)> fCreate)
{
	m_fCreate = fCreate;
}

//绘制绘制事件
void SWindowActivityEvent::OnPaint(std::function<void(SDc)> fPaint)
{
	m_fPaint = fPaint;
}

//窗口空闲事件
void SWindowActivityEvent::OnEvent(std::function<void()> fEvent)
{
	m_fEvent = fEvent;
}

//处理子控件
void SWindowActivityEvent::OnCommand(std::function<void(ActivityParam)> fCommand)
{
	m_fCommand = fCommand;
}
//尺寸变化
void SWindowActivityEvent::OnSize(std::function<void(ActivityParam)> fSize)
{
	m_fSize = fSize;
}

//关闭窗口
void SWindowActivityEvent::OnClose(std::function<BOOL(ActivityParam)> fClose)
{
	m_fClose = fClose;
}

//销毁窗口
void SWindowActivityEvent::OnDestory(std::function<void(ActivityParam)> fDestory)
{
	m_fDestory = fDestory;
}

//取得窗口焦点
void SWindowActivityEvent::OnGetFocus(std::function<void(ActivityParam)> fGetFocus)
{
	m_fGetFocus = fGetFocus;
}

//失去焦点
void SWindowActivityEvent::OnLostFocus(std::function<void(ActivityParam)> fLostFocus)
{
	m_fLostFocus = fLostFocus;
}