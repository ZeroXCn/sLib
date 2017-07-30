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
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate(Param &param)
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
BOOL SWindowActivityEvent::OnClose(Param &param)
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
void SWindowActivityEvent::OnDestory(Param &param)
{
	//TODO:������ǰ���Ĳ���
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus(Param &param)
{

}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus(Param &param)
{

}