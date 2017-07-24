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
//�ؼ�����֮ǰ
BOOL SWindowActivityEvent::OnCreate()
{
	return TRUE;
}

//���ƻ����¼�
void SWindowActivityEvent::OnPaint(SGraphics *g)
{
	//NOTE:��дBeginPaint���򽫻������ѭ��,һֱ����һ����һ����WM_PAINT��Ϣ
	PAINTSTRUCT ps; //���壬�޳�ʼ��,��BeginPaint��ʼ��
	HDC Hdc = g->BeginPaint(&ps);
	//TODO:���𴰿ڻ��ƹ���,���һ��������ӿؼ�


	g->EndPaint(&ps);
}

//�رմ���
BOOL SWindowActivityEvent::OnClose(HWND hWnd)
{
	//DOUBT:�����MessageBox�޷�������ʾ,�����
	
	if (MessageBox(hWnd, TEXT("��ȷ��Ҫ�˳���"), TEXT("�˳�����"), MB_YESNO | MB_DEFBUTTON2 | MB_ICONASTERISK) == IDYES)
	return TRUE;
	else
	return FALSE;
	
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