#include "SWindowActivityEvent.h"


///////////////////////////////
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate()
{
	return TRUE;
}

//���ƻ����¼�
void SWindowActivityEvent::OnPaint(SDc dc)
{

}

//���ڿ����¼�
void SWindowActivityEvent::OnEvent()
{

}

//�رմ���
BOOL SWindowActivityEvent::OnClose(HWND hWnd)
{
	//DOUBT:�����MessageBox�޷�������ʾ,�����
	/*
	if (MessageBox(hWnd, TEXT("��ȷ��Ҫ�˳���"), TEXT("�˳�����"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
		return FALSE;
	*/
	return TRUE;
}

//���ٴ���
void SWindowActivityEvent::OnDestory()
{
	//TODO:������ǰ���Ĳ���
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus()
{

}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus()
{

}