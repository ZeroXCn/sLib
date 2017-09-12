/*************************************
��Ϸ����Դ�ļ� SWindow.cpp
*************************************/
#include "SWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ���ڿչ��캯�� */
SWindow::SWindow(SWidget *parent, LPTSTR name) :
	SWidget(parent)
{
	GetWndClassEx()->lpszClassName = TEXT("swindow");						//��ע�����
	GetWndClassEx()->style =CS_HREDRAW | CS_VREDRAW				;			//���崰�ڷ��(��Ϸ�в�Ӧ�ò���CS_DBLCLKS��ʽ)
	GetWndClassEx()->hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���س���ͼ�꣨��
	GetWndClassEx()->hIconSm = LoadIcon(NULL, IDI_APPLICATION);				//���س���ͼ�꣨С��
	GetWndClassEx()->hCursor = LoadCursor(NULL, IDC_ARROW);					//���������ʽ
	GetWndClassEx()->hbrBackground = (HBRUSH)(COLOR_WINDOW);				//���ô��ڱ���ɫ
	GetWndClassEx()->lpszMenuName = NULL;									//���ô���û�в˵�


	//NOTE:�����m_szTitle����������ظ�,��Ϊ��������ҿ��ܻ�鵽�������
	GetWindowAttribute()->lpClassName = GetWndClassEx()->lpszClassName;		//���ô�����
	GetWindowAttribute()->lpWindowName = name;								//���ڱ���
	GetWindowAttribute()->dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;//���ڷ��
	GetWindowAttribute()->nWidth = 800;										//���ڿ��
	GetWindowAttribute()->nHeight = 600;									//���ڸ߶�

	/*��ȫ��״̬�£�������ʾ����Ļ����*/
	//������ϱ߿��Ĵ��ڴ�С
	int nWidth = GetWindowAttribute()->nWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
	int nHeight = GetWindowAttribute()->nHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

	//�����ڴ��ھ���ʱ���������Ͻǵ�λ��
	GetWindowAttribute()->nPosX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
	GetWindowAttribute()->nPosY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;

	m_bFullScreen = FALSE;
	m_nColorbit = 32;
	m_pInputEvent = (SWindowInputEvent *) this;
	m_pActivityEvent = (SWindowActivityEvent *) this;

}

/* ������������ */
SWindow::~SWindow()
{
	SApplication::GetApp()->DestroyWidget(this);
}

void SWindow::SetAttribute(LPTSTR szTitle, HICON hIcon, HICON hSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	//�����⸳��m_szTitle
	GetWindowAttribute()->lpWindowName = szTitle;

	/* ������Ļģʽ�ʹ�С */
	SetFullScreen(bFullScreen);
	SetColorbit(nColorbit);
	GetWindowAttribute()->nWidth = nWidth;
	GetWindowAttribute()->nHeight = nHeight;

	/*����ͼ��͹��*/
	GetWndClassEx()->hIcon = hIcon;
	GetWndClassEx()->hIconSm = hSmallIcon;

}

void SWindow::SetAttribute(LPTSTR szTitle, int nWidth, int nHeight)
{
	SetAttribute(
		szTitle,
		GetWndClassEx()->hIcon,
		GetWndClassEx()->hIconSm,
		m_bFullScreen,
		m_nColorbit,
		nWidth,
		nHeight);

}

void SWindow::SetFullScreen(BOOL bFullScreen)
{
	m_bFullScreen = bFullScreen;
}


void SWindow::SetColorbit(int nColorbit)
{
	m_nColorbit = nColorbit;
}

////////////////
/* ��ʾ��� */
int SWindow::ShowCursor(BOOL bShow)
{
	return ::ShowCursor(bShow);
}

int SWindow::HideCursor()
{
	return ::ShowCursor(FALSE);
}

/* �����ͷ�����ƶ���Χ */
RECT SWindow::GetClipCursor()
{
	RECT rt;
	::GetClipCursor(&rt);
	return rt;
}
void SWindow::ClipCursor(const RECT *rt)
{
	::ClipCursor(rt);
}
void SWindow::FreeCursor()
{
	::ClipCursor(NULL);
}

/* ȡ��������λ�� */
POINT SWindow::GetCursorPos()
{
	POINT pt;
	::GetCursorPos(&pt);
	return pt;
}
void SWindow::SetCursorPos(POINT pt)
{
	::SetCursorPos(pt.x,pt.y);
}

void SWindow::RePaint()
{
	SWidget::UpdateWindow();
}

//////////////
//���ô��ڻ
void SWindow::SetWindowInputEvent(SWindowInputEvent *pEvent)
{
	/* TODO:������ڴ�й©,���û��Լ��ж��ͷ� */
	m_pInputEvent = pEvent;
}

//���ô��������¼�
void SWindow::SetWindowActivityEvent(SWindowActivityEvent *pEvent)
{
	/* TODO:������ڴ�й©,���û��Լ��ж��ͷ� */
	m_pActivityEvent = pEvent;
}

//ȡ�ô��ڻ
SWindowInputEvent *SWindow::GetWindowInputEvent()
{
	return m_pInputEvent;
}

//ȡ�ô��������¼�
SWindowActivityEvent *SWindow::GetWindowActivityEvent()
{
	return m_pActivityEvent;
}



LRESULT CALLBACK SWindow::OnProc(MessageParam param)
{
	SWindowActivityEvent::ActivityParam acParam(param.hWnd, param.uMsg, param.wParam, param.lParam);
	SWindowInputEvent::InputParam inParam(param.hWnd, param.uMsg, param.wParam, param.lParam);

	//TODO:��ͬ��������ʱ������������,��Ӱ���ٶ�-��ò���ָ���������

	switch (param.uMsg)
	{
	case WM_PAINT:					//�����ػ���Ϣ
		m_pActivityEvent->OnPaint(acParam);
		break;

	case WM_TIMER:
		m_pActivityEvent->OnTimer(acParam);
		break;

	case WM_COMMAND:
		m_pActivityEvent->OnCommand(acParam);
		break;

	case WM_SIZE:
		m_pActivityEvent->OnSize(acParam);
		break;
////////////////
	case WM_KEYDOWN:				//������Ϣ  
		m_pInputEvent->OnKeyDown(inParam);
		break;
	case WM_KEYUP:					//������Ϣ  
		m_pInputEvent->OnKeyUp(inParam);
		break;

	case WM_LBUTTONDOWN:			//������������Ϣ
		m_pInputEvent->OnMouseLButtonDown(inParam);
		break;

	case WM_LBUTTONUP:				//������������Ϣ
		m_pInputEvent->OnMouseLButtonUp(inParam);
		break;

	case WM_MOUSEWHEEL:				//�������¼�
		m_pInputEvent->OnMouseWheel(inParam);
		break;

	case WM_LBUTTONDBLCLK:			//������˫����Ϣ
		m_pInputEvent->OnMouseDoubleClick(inParam);
		break;

	case WM_RBUTTONDOWN:			//����Ҽ�������Ϣ
		m_pInputEvent->OnMouseRButtonDown(inParam);
		break;
	case WM_RBUTTONUP:				//����Ҽ�������Ϣ
		m_pInputEvent->OnMouseLButtonUp(inParam);
		break;

	case WM_MOUSEMOVE:				//����ƶ���Ϣ
		m_pInputEvent->OnMouseMove(inParam);
		break;

	case WM_SETFOCUS:				//��Ϸ���ڵõ�������Ϣ
		m_pActivityEvent->OnGetFocus(acParam);
		break;

	case WM_KILLFOCUS:				//��Ϸ����ʧȥ������Ϣ
		m_pActivityEvent->OnLostFocus(acParam);
		break;

	case WM_CLOSE:					//���ڹر���Ϣ
		if (m_pActivityEvent->OnClose(acParam))				//���ڹر�ǰ�Ĵ���
			::DestroyWindow(param.hWnd);	//�������ٴ�����Ϣ
		break;

	case WM_DESTROY:				//����������Ϣ
		m_pActivityEvent->OnDestory(acParam);
		//TODO:����Ϣ����ʱ,Ҫ��ֻ�˳��Ӵ��ڶ���Ӱ�츸����
		::PostQuitMessage(0);			//DOUBT:������,�������˳������,����ɽ��ղ���WM_QUIT��Ϣ
		break;
		//case	WM_SYSCOMMAND //ϵͳ�˵������󻯰�ť����С��������ԭ��ť���رհ�ť;���û��˵�����WM_COMMAND������Ŷ

	default:
		//���ø���ĺ�������
		return SWidget::OnProc(param);
	
	}
	return 0;
}
BOOL SWindow::OnPreCreate(WNDCLASSEX *lpWndClassEx, WINATTRIBUTE *lpWinAttribute)
{
	int &nPosX = lpWinAttribute->nPosX;
	int &nPosY = lpWinAttribute->nPosY;
	int &nWidth = lpWinAttribute->nWidth;
	int &nHeight = lpWinAttribute->nHeight;
	DWORD &dwStyle = lpWinAttribute->dwStyle;

	/*ʹ��DEVMODE�ṹ������Ļ��ʾģʽ*/
	DEVMODE DevMode;
	ZeroMemory(&DevMode, sizeof(DevMode));					//���ṹDevMode���ڴ�����
	DevMode.dmSize = sizeof(DevMode);						//����DevMode�洢�ռ��Դ洢��Ļ��������

	//�õ�ǰ��Ļ��ʾģʽ�������DevMode
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &DevMode);

	BOOL bDisplayChange = FALSE;							//��ʶ��Ļ��ʾģʽ�Ƿ�ı�

	//�����Ļ��ʾģʽλ������Ϸ��ͬ
	if (DevMode.dmBitsPerPel != (unsigned long)m_nColorbit)
	{
		DevMode.dmBitsPerPel = m_nColorbit;					//������ʾģʽλ��
		bDisplayChange = TRUE;
	}

	//���ȫ��״̬�µ���Ļ�ߴ��봰�ڲ�ͬ������Ļ�ߴ�С�ڴ���,����Ҫ������ʾģʽ
	if ((m_bFullScreen && nWidth != ::GetSystemMetrics(SM_CXSCREEN))
		|| nWidth>GetSystemMetrics(SM_CXSCREEN))
	{
		DevMode.dmPelsWidth = nWidth;						//��Ļ���
		DevMode.dmPelsHeight = nHeight;					//��Ļ�߶�	
		bDisplayChange = TRUE;
	}

	//�����ʾģʽ�����ı�
	if (bDisplayChange)
	{
		LONG result = ::ChangeDisplaySettings(&DevMode, 0);	//��̬�޸���Ļ��ʾģʽ	
		//�ж��޸���ʾģʽ�Ƿ�ɹ�
		if (result == DISP_CHANGE_SUCCESSFUL)
		{
			// �����̬�޸���ʾģʽ�ɹ������޸���ʾģʽ
			::ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN);
		}
		else
		{
			//�����̬�޸���ʾģʽʧ�ܣ��ָ�ԭ������Ļ����
			::ChangeDisplaySettings(NULL, 0);	//�ָ�ԭ������Ļ����
			return FALSE;						//����FALSE
		}
	}

	/* �жϴ�����ʾ��ʽ����������Ӧ�Ĵ������� */
	if (m_bFullScreen)
	{
		/* ȫ��״̬�� */
		//���ô������Ͻ�λ��
		nPosX = 0;
		nPosY = 0;
		dwStyle = WS_POPUP;			//������Ϸ���ڷ��Ϊ�ޱ߿�ĵ���ʽ����

	}
	
	return TRUE;
}

BOOL SWindow::OnCreate(MessageParam param)
{
	return m_pActivityEvent->OnCreate(SWindowActivityEvent::ActivityParam(param.hWnd, param.uMsg, param.wParam, param.lParam));
}


BOOL SWindow::OnAftCreate(SWnd sWnd)
{
	if (!sWnd.GetHandle()){
		::MessageBox(NULL, TEXT("ע�ᴰ��ʧ��"), TEXT("error"), 0);
		return FALSE;
	}
	return TRUE;

}

//
void SWindow::OnRunning()
{
	m_pActivityEvent->OnEvent();
	SWidget::OnRunning();
}

