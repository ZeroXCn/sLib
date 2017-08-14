#include "SControl.h"

unsigned int SControl::g_nControlId = 100;
///
SControl::SControl(SWidget *parent) :SWidget(parent)
{
	/* �����Ƿ����ش���,��������븸��Ŀؼ��б� */
	/* ����,������ڸ�����Ϊ�ؼ�,�����Ϊ���� */

	SetMenu((HMENU)DEFAULT_MENU_VALUE);	//Ӧ���Զ�����ID
	SetInstance((HINSTANCE)::GetModuleHandle(NULL));

	//�ؼ���ʽ������WS_CHILD | WS_VISIBLE

	g_nControlId++;
}

BOOL SControl::OnPreCreate()
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