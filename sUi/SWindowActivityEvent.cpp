#include "SWindowActivityEvent.h"


SWindowActivityEvent::ActivityParam::ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), uMsg(message), wParam(wParam), lParam(lParam)
{
		
};


///////////////////////////////
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate(ActivityParam param)
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

void SWindowActivityEvent::OnCommand(ActivityParam param)
{

}

//�رմ���
BOOL SWindowActivityEvent::OnClose(ActivityParam param)
{
	//DOUBT:�����MessageBox�޷�������ʾ,�����
	/*
	if (MessageBox(param.hWnd, TEXT("��ȷ��Ҫ�˳���"), TEXT("�˳�����"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
		return TRUE;
	else
		return FALSE;
	*/
	return TRUE;
}

//���ٴ���
void SWindowActivityEvent::OnDestory(ActivityParam param)
{
	//TODO:������ǰ���Ĳ���
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus(ActivityParam param)
{

}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus(ActivityParam param)
{

}