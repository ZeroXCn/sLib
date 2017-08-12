#include "SWindowActivityEvent.h"


SWindowActivityEvent::ActivityParam::ActivityParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam) :
hWnd(hWnd), message(message), wParam(wParam), lParam(lParam)
{
		
};

HWND &SWindowActivityEvent::ActivityParam::GetWnd()
{
	return this->hWnd;
}
UINT &SWindowActivityEvent::ActivityParam::GetMessage()
{
	return this->message;
}
WPARAM &SWindowActivityEvent::ActivityParam::GetWParam()
{
	return this->wParam;
}
LPARAM &SWindowActivityEvent::ActivityParam::GetLParam()
{
	return this->lParam;
}


///////////////////////////////
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate(ActivityParam &param)
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

void SWindowActivityEvent::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}

//�رմ���
BOOL SWindowActivityEvent::OnClose(ActivityParam &param)
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
void SWindowActivityEvent::OnDestory(ActivityParam &param)
{
	//TODO:������ǰ���Ĳ���
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus(ActivityParam &param)
{

}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus(ActivityParam &param)
{

}