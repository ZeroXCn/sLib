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
//ȡ�ÿͻ������
WORD SWindowActivityEvent::ActivityParam::GetClientWidth()
{
	return LOWORD(lParam);
}
//ȡ�ÿͻ����߶�
WORD SWindowActivityEvent::ActivityParam::GetClientHeight()
{
	return HIWORD(lParam);
}
///////////////////////////////
SWindowActivityEvent::SWindowActivityEvent()
{
	m_fCreate = [](ActivityParam){ return TRUE; };
	m_fPaint = [](SGraphics){};
	m_fEvent = [](){};
	m_fTimer = [](ActivityParam){};
	m_fCommand = [](ActivityParam){};
	m_fSize = [](ActivityParam){};
	m_fClose = [](ActivityParam){
		/*
		if (MessageBox(param.hWnd, TEXT("��ȷ��Ҫ�˳���"), TEXT("�˳�����"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
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
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate(ActivityParam param)
{
	return m_fCreate(param);
}

//���ƻ����¼�
void SWindowActivityEvent::OnPaint(ActivityParam param)
{
	PAINTSTRUCT ps;					//���壬�޳�ʼ��,��BeginPaint��ʼ��
	SGraphics2D graphics2d(param.hWnd);
	SDc sDc;
	//NOTE:��дBeginPaint���򽫻������ѭ��,һֱ����һ����һ����WM_PAINT��Ϣ
	HDC hDC = ::BeginPaint(param.hWnd, &ps);

	graphics2d.SetDC(hDC);
	sDc.SetHandle(hDC);

	//TODO:���𴰿ڻ��ƹ���,���һ��������ӿؼ�
	OnPaint(graphics2d);
	OnPaint(sDc);

	::EndPaint(param.hWnd, &ps);

}
void SWindowActivityEvent::OnPaint(SGraphics graphics)
{
	m_fPaint(graphics);
}

void SWindowActivityEvent::OnPaint(SDc sDc)
{

}

//���ڿ����¼�
void SWindowActivityEvent::OnEvent()
{
	m_fEvent();
}
//��ʱ��
void SWindowActivityEvent::OnTimer(ActivityParam param)
{
	m_fTimer(param);
}
//�����Ӵ�������
void SWindowActivityEvent::OnCommand(ActivityParam param)
{
	m_fCommand(param);
}

void SWindowActivityEvent::OnSize(ActivityParam param)
{
	m_fSize(param);
}

//�رմ���
BOOL SWindowActivityEvent::OnClose(ActivityParam param)
{
	return m_fClose(param);
}

//���ٴ���
void SWindowActivityEvent::OnDestory(ActivityParam param)
{
	//TODO:������ǰ���Ĳ���
	m_fDestory(param);
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus(ActivityParam param)
{
	m_fGetFocus(param);
}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus(ActivityParam param)
{
	m_fLostFocus(param);
}

//Lambda���ʽ//////////////////////////////////////
//�ؼ�����֮ʱ
void SWindowActivityEvent::OnCreate(std::function<BOOL(ActivityParam)> fCreate)
{
	m_fCreate = fCreate;
}

//���ƻ����¼�
void SWindowActivityEvent::OnPaint(std::function<void(SGraphics)> fPaint)
{
	m_fPaint = fPaint;
}

//���ڿ����¼�
void SWindowActivityEvent::OnEvent(std::function<void()> fEvent)
{
	m_fEvent = fEvent;
}

//��ʱ��
void SWindowActivityEvent::OnTimer(std::function<void(ActivityParam)> fTimer)
{
	m_fTimer = fTimer;
}

//�����ӿؼ�
void SWindowActivityEvent::OnCommand(std::function<void(ActivityParam)> fCommand)
{
	m_fCommand = fCommand;
}
//�ߴ�仯
void SWindowActivityEvent::OnSize(std::function<void(ActivityParam)> fSize)
{
	m_fSize = fSize;
}

//�رմ���
void SWindowActivityEvent::OnClose(std::function<BOOL(ActivityParam)> fClose)
{
	m_fClose = fClose;
}

//���ٴ���
void SWindowActivityEvent::OnDestory(std::function<void(ActivityParam)> fDestory)
{
	m_fDestory = fDestory;
}

//ȡ�ô��ڽ���
void SWindowActivityEvent::OnGetFocus(std::function<void(ActivityParam)> fGetFocus)
{
	m_fGetFocus = fGetFocus;
}

//ʧȥ����
void SWindowActivityEvent::OnLostFocus(std::function<void(ActivityParam)> fLostFocus)
{
	m_fLostFocus = fLostFocus;
}