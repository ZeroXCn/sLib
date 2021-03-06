#include "SControl.h"

unsigned int SControl::g_nControlId = 100;
///
SControl::SControl(SWidget *parent) :SWidget(parent)
{
	/* 无论是否重载此类,都必须加入父类的控件列表 */
	/* 另外,如果存在父类则为控件,否则变为窗口 */
	GetWndClassEx()->style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;	//没有关闭窗口的样式以及子类化

	//控件样式都含有WS_CHILD | WS_VISIBLE
	GetWindowAttribute()->dwStyle = WS_CHILD | WS_VISIBLE;
	GetWindowAttribute()->lpParam = parent ? parent->GetWnd().GetHandle() : NULL;
	GetWindowAttribute()->hMenu = (HMENU)DEFAULT_MENU_VALUE;
	GetWindowAttribute()->hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	

	m_pWndClassEx->lpszClassName = NULL;
	
	//添加到父类子控件初始化列表
	AddInitChild(parent, (SWidget *)this);

	g_nControlId++;
}
SControl::~SControl()
{
	UnSubChildClass(GetWnd().GetHandle(), (SMessageHandler *)GetParent());
}

///////////////////////////////
BOOL SControl::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	/* 通用操作 */

	return TRUE;
}

BOOL SControl::OnAftCreate(SWnd sWnd)
{
	//所有控件都必须SetParent();并且加入父类的自控列表
	
	//TODO:需要添加判断
	m_Wnd.SetHandle(sWnd.GetHandle());						//系统控件的消息不执行WM_NCCREATE自定义内容,只能在此在进行一次
	m_Wnd.SetParent(GetParent() ? GetParent()->GetWnd().GetHandle() : NULL);
	SubChildClass(sWnd.GetHandle(), (SMessageHandler *)GetParent());

	return TRUE;
}

LRESULT CALLBACK SControl::OnProc(MessageParam param)
{
	return SMessageHandler::OnProc(param);
}