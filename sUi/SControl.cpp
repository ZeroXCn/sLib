#include "SControl.h"

unsigned int SControl::g_nControlId = 100;
///
SControl::SControl(SWidget *parent) :SWidget(parent)
{
	/* �����Ƿ����ش���,��������븸��Ŀؼ��б� */
	/* ����,������ڸ�����Ϊ�ؼ�,�����Ϊ���� */
	GetWndClassEx()->style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;	//û�йرմ��ڵ���ʽ�Լ����໯

	//�ؼ���ʽ������WS_CHILD | WS_VISIBLE
	GetWindowAttribute()->dwStyle = WS_CHILD | WS_VISIBLE;
	GetWindowAttribute()->hMenu = (HMENU)DEFAULT_MENU_VALUE;
	GetWindowAttribute()->hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	

	m_pWndClassEx->lpszClassName = NULL;
	

	g_nControlId++;
}
SControl::~SControl()
{

}

BOOL SControl::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	/* ͨ�ò��� */

	return TRUE;
}

BOOL SControl::OnAftCreate(SWnd sWnd)
{
	//���пؼ�������SetParent();���Ҽ��븸����Կ��б�
	
	//TODO:��Ҫ����ж�
	m_Wnd.SetHandle(sWnd.GetHandle());						//ϵͳ�ؼ�����Ϣ��ִ��WM_NCCREATE�Զ�������,ֻ���ڴ��ڽ���һ��
	m_Wnd.SetParent(GetParent() ? GetParent()->GetWnd().GetHandle() : NULL);
	SubChildClass(sWnd.GetHandle(), (SMessageHandler *)GetParent());

	return TRUE;
}

LRESULT CALLBACK SControl::OnProc(MessageParam param)
{
	return SMessageHandler::OnProc(param);
}