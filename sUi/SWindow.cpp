/*************************************
��Ϸ����Դ�ļ� SWindow.cpp
*************************************/
#include "SWindow.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ʼ����̬����	
int SWindow::s_winnum = 0;

void SWindow::Init()
{
	//NOTE:�����ClassName�����������ظ�
	_stprintf_s(m_szClassName, TEXT("Win32%d"), s_winnum++);
	_stprintf_s(m_szTitle, TEXT("Win32%d"), s_winnum++);

	m_hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance(): ::GetModuleHandle(NULL);
	m_wIcon = NULL;
	m_wSmallIcon = NULL;
	m_bFullScreen = FALSE;
	m_nColorbit = 32;

	m_bIsRunning = TRUE;

	m_InputEvent = (SWindowInputEvent *) this;
	m_ActivityEvent = (SWindowActivityEvent *) this;

	SApplication::GetApp()->RegisterWindow(this);
}

/* ���ڿչ��캯�� */
SWindow::SWindow(SWidget *parent) :
	SWidget(parent)
{
	Init();
	
}

SWindow::SWindow(LPTSTR szTitle) :
	SWidget(NULL)
{
	Init();
	_stprintf_s(m_szTitle, szTitle);

}

/* ������������ */
SWindow::~SWindow()
{
	//TODO:ֻ������Դ�ͷ�,���ܷ�ע��
	//TODO:�߳̽����������Ա��ͷ�,
	SApplication::GetApp()->DestroyWindow(this);
}


void SWindow::SetAttribute(HINSTANCE hInstance, LPTSTR szClassName, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	m_hInstance = hInstance;						//��������ʵ��Ϊ��ǰ����ʵ�����					

	lstrcpy(m_szClassName, szClassName);		//��������ע�����Ƹ���_szWindowClass
	lstrcpy(m_szTitle, szTitle);					//�����⸳��m_szTitle

	/* ������Ļģʽ�ʹ�С */
	m_bFullScreen = bFullScreen;
	m_nColorbit = nColorbit;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	/*����ͼ��͹��*/
	m_wIcon = wIcon;
	m_wSmallIcon = wSmallIcon;

}

void SWindow::SetAttribute(LPTSTR szWindowClass, LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, BOOL bFullScreen, int nColorbit, int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		szWindowClass,
		szTitle,
		wIcon,
		wSmallIcon,
		bFullScreen,
		nColorbit,
		nWidth,
		nHeight);

}

void SWindow::SetAttribute(LPTSTR szWindowClass, LPTSTR szTitle ,int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		szWindowClass,
		szTitle,
		NULL,
		NULL,
		FALSE,
		32,
		nWidth,
		nHeight);

}

void SWindow::SetAttribute(LPTSTR szTitle, int nWidth, int nHeight)
{
	SetAttribute(GetInstance(),
		m_szClassName,
		szTitle,
		NULL,
		NULL,
		FALSE,
		32,
		nWidth,
		nHeight);

}


long SWindow::SetCursorIcon(WORD wIcon){
	
	long lCur = (long)LoadCursor(GetInstance(), MAKEINTRESOURCE(wIcon));
	if (m_hWnd){
		::SetClassLong(m_hWnd, GCL_HCURSOR, lCur);
		return lCur;
	}
	return 0;
}


void SWindow::SetBigIcon(WORD wIcon)
{
	m_wIcon = wIcon;
}


void SWindow::SetSmallIcon(WORD wIcon)
{
	m_wSmallIcon = wIcon;
}


void SWindow::SetFullScreen(BOOL bFullScreen)
{
	m_bFullScreen = bFullScreen;
}


void SWindow::SetColorbit(int nColorbit)
{
	m_nColorbit = nColorbit;
}

void SWindow::SetWndProc(WNDPROC pWndProc)
{
	Subclass(m_hWnd);
	SetMessageProc(pWndProc);
	::SetWindowLong(m_hWnd, GWL_WNDPROC, (long)pWndProc);
}

void SWindow::SetRunning(BOOL bRunning)
{
	m_bIsRunning = bRunning;
}

BOOL SWindow::IsCreated()
{
	return m_hWnd?TRUE:FALSE;
}

/////
void SWindow::DoModal()
{
	if (!IsCreated()){
		if (Create()){
			Show();
			OnRun();
		}
	}
	else SWidget::Show(SW_SHOWNORMAL);
}

//��ʾ�ؼ�
void SWindow::Show()
{
	Show(SW_SHOWNORMAL);
}
void SWindow::Show(int nCmdShow)
{
	if (!IsCreated()){
		Start();	//�����߳�
	}
	else SWidget::Show(nCmdShow);
	
	return;

}

//���ؿؼ�
void SWindow::Hide()
{
	Show(SW_HIDE);
}

//////////////

LRESULT CALLBACK SWindow::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:					//���ڽ�����Ϣ:CreateWindow�������󴴽�����ʱ���ʹ���Ϣ
		m_ActivityEvent->OnCreate();
		break;

	case WM_PAINT:					//�����ػ���Ϣ
		m_ActivityEvent->OnPaint(hWnd);
		break;
		
	case WM_KEYDOWN:				//������Ϣ  
		m_InputEvent->OnKeyDown(hWnd, wParam);
		break;
	case WM_KEYUP:					//������Ϣ  
		m_InputEvent->OnKeyUp(hWnd, wParam);
		break;

	case WM_LBUTTONDOWN:			//������������Ϣ
		m_InputEvent->OnMouseLButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_LBUTTONUP:				//������������Ϣ
		m_InputEvent->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEWHEEL:				//�������¼�
		m_InputEvent->OnMouseWheel(hWnd, wParam);
		break;

	case WM_LBUTTONDBLCLK:			//������˫����Ϣ
		m_InputEvent->OnMouseDoubleClick(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_RBUTTONDOWN:			//����Ҽ�������Ϣ
		m_InputEvent->OnMouseRButtonDown(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;
	case WM_RBUTTONUP:				//����Ҽ�������Ϣ
		m_InputEvent->OnMouseLButtonUp(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_MOUSEMOVE:				//����ƶ���Ϣ
		m_InputEvent->OnMouseMove(hWnd, LOWORD(lParam), HIWORD(lParam), wParam);
		break;

	case WM_SETFOCUS:				//��Ϸ���ڵõ�������Ϣ
		m_ActivityEvent->OnGetFocus();
		break;

	case WM_KILLFOCUS:				//��Ϸ����ʧȥ������Ϣ
		m_ActivityEvent->OnLostFocus();
		break;

	case WM_CLOSE:					//���ڹر���Ϣ
		if (m_ActivityEvent->OnClose(hWnd))				//���ڹر�ǰ�Ĵ���
			DestroyWindow(hWnd);	//�������ٴ�����Ϣ
		break;

	case WM_DESTROY:				//����������Ϣ
		m_ActivityEvent->OnDestory();
		PostQuitMessage(0);			//DOUBT:������,�������˳�������,����ɽ��ղ���WM_QUIT��Ϣ
		break;
		//case	WM_SYSCOMMAND //ϵͳ�˵������󻯰�ť����С��������ԭ��ť���رհ�ť;���û��˵�����WM_COMMAND������Ŷ

	default:
			//IMPORTMENT:�˴���hWnd���ܲ�Ϊm_hWnd(����δ����ǰ����þ�̬��Ϣ����,��ʱm_hWnd==NULL),��Ӧ�ö�HWND��װ,��Ϊ���
		return DefWindowProc(hWnd, message, wParam, lParam);
	
	}
	return 0;
}


void SWindow::OnRun()
{
	MSG msg;											//������Ϣ�ṹ

	/* ��Ϣѭ�� */
	while (m_bIsRunning)
	{
		//NOTE:����ڶ�����Ϊm_hWnd�ᵼ���޷�����WM_QUIT��Ϣ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//������Ϣ
		{
			if (msg.message == WM_QUIT)					//������˳���Ϣ�����˳�ѭ��
				break;
				
			TranslateMessage(&msg);						//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);						//������Ϣ
		}
		else
		{
			OnEvent();//�����¼�ѭ��

		}
	}
	//���ٴ���
	Unsubclass(m_hWnd);									//�������Ϣ����
	SApplication::GetApp()->QuitWindow(this);			//֪ͨ���߳�,�߳̽���
}

void SWindow::OnEvent()
{
	//TODO:��Ҫѭ�����¼�:�߼��¼�
}


//�����ؼ�
BOOL SWindow::Create(){

	WNDCLASSEX wcApp;							//����������
	wcApp.cbSize = sizeof(wcApp);

	//���������Ը�ֵ
	wcApp.lpszClassName = m_szClassName;						//���ô�������
	wcApp.style = CS_HREDRAW;									//���崰�ڷ��
	wcApp.lpfnWndProc = m_pWndProc;								//ָ����Ϣ��������
	wcApp.hInstance = m_hInstance;								//ָ���崰��Ӧ�ó���ľ��
	wcApp.cbWndExtra = 0;										//ָ�򴰿ڹ��̺�����ָ��. ����ʹ�� CallWindowProc�������ô��ڹ���.
	wcApp.cbClsExtra = 0;										//ָ����������֮��ĸ����ڴ�ռ���ֽ���. ϵͳ��ʼ��Ϊ0.
	wcApp.hIconSm = m_wIcon ? LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wIcon)) : NULL;			//���س���ͼ�꣨��
	wcApp.hIcon = m_wSmallIcon ? LoadIcon(m_hInstance, MAKEINTRESOURCE(m_wSmallIcon)) : NULL;	//���س���ͼ�꣨С��
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);				//���������ʽ
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW);				//���ô��ڱ���ɫ
	wcApp.lpszMenuName = NULL;									//���ô���û�в˵�

	//ע�ᴰ����
	//DOUBT:ûCreate֮ǰ�Ѿ���ʼ��Ϣ�ķ���,��ʱm_hWnd��Ϊ��,���Ա����ҷ�����RegisterClassEx()֮ǰ����m_hWnd
	if (!RegisterClassEx(&wcApp))
		return FALSE;

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
	if ((m_bFullScreen && m_nWidth != ::GetSystemMetrics(SM_CXSCREEN))
		|| m_nWidth>GetSystemMetrics(SM_CXSCREEN))
	{
		DevMode.dmPelsWidth = m_nWidth;						//��Ļ����
		DevMode.dmPelsHeight = m_nHeight;					//��Ļ�߶�	
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
			::ChangeDisplaySettings(NULL, 0);		//�ָ�ԭ������Ļ����
			return FALSE;						//����FALSE
		}
	}

	/* �жϴ�����ʾ��ʽ����������Ӧ�Ĵ������� */
	if (m_bFullScreen)
	{
		/* ȫ��״̬�� */
		//���ô������Ͻ�λ��
		m_nPosX = 0;
		m_nPosY = 0;
		m_dwStyle = WS_POPUP;			//������Ϸ���ڷ��Ϊ�ޱ߿�ĵ���ʽ����
	}
	else
	{
		/*��ȫ��״̬�£�������ʾ����Ļ����*/
		//������ϱ߿��Ĵ��ڴ�С
		m_nWidth = m_nWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2;
		m_nHeight = m_nHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 10;

		//�����ڴ��ھ���ʱ���������Ͻǵ�λ��
		m_nPosX = (GetSystemMetrics(SM_CXSCREEN) - m_nWidth) / 2;
		m_nPosY = (GetSystemMetrics(SM_CYSCREEN) - m_nHeight) / 2;

		//������Ϸ���ڷ��Ϊ����������ϵͳ�˵�����С���Ĵ���
		m_dwStyle = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	}

	m_nWidth += 10;
	m_nHeight += 8;

	SetParam((SMessageHandler *)this);	//���ò���,����Ϣ˳������ȷִ�е�������Ϣ,�����������

	if (SWidget::Create())
	{
		Subclass(m_hWnd);		//����Ϣ����
		return TRUE;
	}
	else
	{
		MessageBox(NULL, TEXT("ע�ᴰ��ʧ��"), TEXT("error"), 0);
		return FALSE;
	}

	return TRUE;
	
}

void SWindow::Run(){
	if (Create()){
		Show();
		OnRun();
	}

}


void  SWindow::Destroy(){
	
	SWidget::Destroy();
}