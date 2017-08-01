#include "SWidget.h"

SWidget::SWidget(SWidget *parent)
{
	m_pParent = parent;

	m_hInstance = SApplication::GetApp() ? SApplication::GetApp()->GetInstance() : ::GetModuleHandle(NULL);

	m_parentWnd = m_pParent ? m_pParent->GetWnd().GetWnd() : NULL;
	m_hMenu = NULL;
	m_lpParam = NULL;

	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_bEnabled = TRUE;
	m_bVisible = TRUE;
	m_bIsRunning = TRUE;
	m_bSysClass = FALSE;

	lstrcpy(m_szTitle, TEXT("Widget"));
	lstrcpy(m_szTip, TEXT(""));

	m_pThread = new SThread((SRunnable *) this);

	//TODO:ֻ�д��ڲŽ��д���ע��

}
SWidget::~SWidget()
{
	//TODO:ֻ������Դ�ͷ�,���ܷ�ע��
	//TODO:�߳̽���������Ա��ͷ�,

	delete m_pThread;
}

/////
SWidget *SWidget::GetParent()
{
	return m_pParent;
}
void  SWidget::SetParent(SWidget *parent)
{
	m_pParent = parent;
	m_parentWnd = parent?parent->GetWnd().GetWnd():NULL;
}

/* ����ʵ����� */
void SWidget::SetInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

/* ���ÿؼ���� */
void SWidget::SetWnd(SWnd pWnd)
{
	m_Wnd = pWnd;
}

/* ���ò˵���� */
void SWidget::SetMenu(HMENU hMenu)
{
	m_hMenu = hMenu;
}

HMENU SWidget::GetMenu()
{
	return m_hMenu;
}

/* ���ò��� */
void SWidget::SetParam(LPVOID lpParam)
{
	m_lpParam = lpParam;
}

//��ȡ�ؼ�ʵ�����
HINSTANCE SWidget::GetInstance()
{
	return m_hInstance;
}

//��ȡ�ؼ����
SWnd SWidget::GetWnd()
{
	return m_Wnd;
}

//��ȡ�豸������
SDc SWidget::GetDC()
{
	SDc dc;
	if (m_Wnd.GetWnd())
		dc.SetDC(m_Wnd.GetDC());
	return dc;
}

/* ���ò��� */
LPVOID SWidget::GetParam()
{
	return m_lpParam;
}

/* ���ÿؼ��������� */
void SWidget::SetClassName(LPTSTR szClassName)
{
	lstrcpy(m_szClassName, szClassName);
}
LPTSTR SWidget::GetClassName()
{
	return m_szClassName;
}

/* ���ÿؼ����� */
void SWidget::SetTitle(LPTSTR szTitle)
{
	lstrcpy(m_szTitle, szTitle);					//�����⸳��m_szTitle
	if (m_Wnd.GetWnd())
		m_Wnd.SetWindowText(m_szTitle);
}
LPTSTR SWidget::GetTitle()
{
	return m_szTitle;
}
LPTSTR SWidget::GetTitle(LPTSTR szTitle, int iCount)
{
	if (m_Wnd.GetWnd()){
		m_Wnd.GetWindowText(szTitle, iCount);
		return szTitle;
	}
	else
		return m_szTitle;
}

/* ���ÿؼ���ʽ */
void SWidget::SetStyle(DWORD dwStyle)
{
	if (m_Wnd.GetWnd()){
		m_Wnd.SetWindowLong(m_dwStyle, dwStyle);
	}
	m_dwStyle = dwStyle;
	
}
DWORD SWidget::GetStyle()
{
	return m_dwStyle;
}

POINT SWidget::GetPos()
{
	POINT pt{ m_nPosX, m_nPosY };
	if (m_Wnd.GetWnd()){
		RECT rt{ 0, 0, 0, 0 };
		m_Wnd.GetWindowRect(&rt); //���window����
		/**/
		pt.x = rt.left; pt.y = rt.top;
		m_Wnd.ScreenToClient(&pt); //ת��client
		/* //else
		pt.x = = rt.right - rt.left;
		l pt.y = rt.bottom - rt.top
		*/

	}
	return pt;
}
void SWidget::SetPos(POINT pt)
{
	SetPos(pt.x, pt.y);
}

void SWidget::SetPos(int x, int y)
{
	m_nPosX = x;
	m_nPosY = y;
	if (m_Wnd.GetWnd()){
		m_Wnd.SetWindowPos( NULL, m_nPosX, m_nPosY, m_nWidth, m_nHeight, 0);
	}
}

void SWidget::MovePos(int x, int y)
{
	m_nPosX = x;
	m_nPosY = y;
	if (m_Wnd.GetWnd()){
		m_Wnd.MoveWindow(x, y, m_nWidth, m_nHeight, FALSE);
	}
}
void SWidget::MovePos(POINT pt)
{
	MovePos(pt.x, pt.y);
}

int SWidget::GetWidth()
{
	return m_nWidth;
}
int SWidget::GetHeight()
{
	return m_nHeight;
}
void SWidget::SetWidth(int nWidth)
{
	m_nWidth = nWidth;
}
void SWidget::SetHeight(int nHeight)
{
	m_nHeight = nHeight;
}


RECT SWidget::GetRect()
{
	RECT rt;

	if (m_Wnd.GetWnd()){
		m_Wnd.GetWindowRect(&rt);
	}
	else{
		rt.left = m_nPosX;
		rt.top = m_nPosY;
		rt.right = m_nWidth + m_nPosX;
		rt.bottom = m_nHeight + m_nPosY;
	}

	return rt;
}
void SWidget::SetRect(RECT rt)
{
	m_nPosX = rt.left;
	m_nPosY = rt.top ;
	m_nWidth = rt.right - m_nPosX;
	m_nHeight = rt.bottom - m_nPosY;
}


BOOL SWidget::IsEnabled()
{
	return m_bEnabled;
}
void SWidget::SetEnabled(BOOL bEnabled)
{
	m_bEnabled = bEnabled;
}

BOOL SWidget::IsVisible()
{
	return m_bVisible;
}
void SWidget::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}


LPTSTR SWidget::GetTip()
{
	return m_szTip;
}
void SWidget::SetTip(LPTSTR str)
{
	lstrcpy(m_szTip, str);
}


/* �ö����� */
BOOL SWidget::SetForegroundWindow()
{
	return m_Wnd.SetForegroundWindow();
}

/* ȡ�ý��� */
HWND SWidget::SetFocus()
{
	return m_Wnd.SetFocus();
}
///

BOOL SWidget::IsCreated()
{
	return m_Wnd.GetWnd() ? TRUE : FALSE;
}

void SWidget::SetRunning(BOOL bRunning)
{
	m_bIsRunning = bRunning;
}

////////////////////////
//��ʾ�ؼ�
void SWidget::ShowWindow()
{
	ShowWindow(SW_SHOWNORMAL);
}
void SWidget::ShowWindow(int nCmdShow)
{
	m_Wnd.ShowWindow( nCmdShow);	//��ʾ�ؼ�
}

//���ؿؼ�
void SWidget::HideWindow()
{
	ShowWindow(SW_HIDE);
}

//���¿ؼ�
void SWidget::UpdateWindow()
{

	m_Wnd.InvalidateRect( NULL, FALSE);	//�����������һ������Ϊ��������,��Ҫ��������
	m_Wnd.UpdateWindow();					//ǿ��ˢ�´���
	
}
//��Ϸ��
void SWidget::UpdateWindow(int left, int top, int right, int bottom)
{
	RECT temp;
	temp.left = left;
	temp.top = top;
	temp.right = right;
	temp.bottom = bottom;
	m_Wnd.InvalidateRect(&temp, FALSE);	//�����������һ������,��Ҫ��������
	m_Wnd.UpdateWindow();					//ǿ��ˢ�´���,
	
}

//�ػ�ؼ�
void SWidget::ReDrawWindow()
{
	m_Wnd.InvalidateRect(NULL, FALSE);	//ǿ��ˢ�´���,��Ҫ��������
	m_Wnd.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:�������������ⲻ�Ǻܺ�
}
/////////////
BOOL SWidget::OnPreCreate()
{
	/* Ĭ�����е�SWidget����һ�������� */
	WNDCLASSEX wcApp;											//����������
	wcApp.cbSize = sizeof(wcApp);
	//���������Ը�ֵ
	//wcApp.lpszClassName = TEXT("swidget");					//���ô�������(�ṩ��CreateWindow()ʹ��)
	wcApp.style = CS_HREDRAW;									//���崰�ڷ��
	wcApp.hInstance = m_hInstance;								//ָ���崰��Ӧ�ó���ľ��
	wcApp.cbWndExtra = 0;										//ָ�򴰿ڹ��̺�����ָ��. ����ʹ�� CallWindowProc�������ô��ڹ���.
	wcApp.cbClsExtra = 0;										//ָ����������֮��ĸ����ڴ�ռ���ֽ���. ϵͳ��ʼ��Ϊ0.
	wcApp.hIconSm = LoadIcon(NULL, IDI_APPLICATION);			//���س���ͼ�꣨��
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���س���ͼ�꣨С��
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);				//���������ʽ
	wcApp.hbrBackground = (HBRUSH)(COLOR_WINDOW);				//���ô��ڱ���ɫ
	wcApp.lpszMenuName = NULL;									//���ô���û�в˵�

	return Register(TEXT("swidget"), &wcApp);
}

//�ؼ���Ϣ����
LRESULT CALLBACK SWidget::OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_NCCREATE:
		//TODO:�о��˴���hWnd������Create()���ص�hWnd��һ��
		m_Wnd.SetWnd(hWnd);
		//NOTE:���뷵��Ĭ�ϲ���
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:				//����������Ϣ
		PostQuitMessage(0);			//DOUBT:������,�������˳������,����ɽ��ղ���WM_QUIT��Ϣ
		break;
	default:
		return SMessageHandler::OnProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void SWidget::OnRun()
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
			OnRunning();								//����ϵͳ����
		}
	}
}

//�ؼ�ѭ���¼�
void SWidget::OnRunning()
{
	//TODO:��Ҫѭ�����¼�:�߼��¼�
	//NOTE:����ʱ��Ӧ�����߳�����,����CPUռ��
	SThread::Sleep(10);
}

//�ؼ��˳��¼�
void SWidget::OnRan()
{
	//TODO:����OnRun()��������
	Unsubclass(m_Wnd.GetWnd());									//�������Ϣ����
	SApplication::GetApp()->DestroyWidget(this);				//֪ͨ���߳�,�߳̽���
}
////////////

void SWidget::Run()
{
	if (Create()){
		ShowWindow();
		OnRun();
		OnRan();//����
	}

}

//ע��ؼ���
BOOL SWidget::Register(LPTSTR szName, WNDCLASSEX *wcApp)
{
	//ע�ᴰ����
	if (szName){
		BOOL result = TRUE;
		if (wcApp){
			m_bSysClass = FALSE;
			SetParam((SMessageHandler *)this);		//���ò���,����Ϣ˳������ȷִ�е�������Ϣ,�����������
			wcApp->lpszClassName = szName;
			wcApp->lpfnWndProc = m_pWndProc;		//ָ����Ϣ������
			result = RegisterClassEx(wcApp);
		}
		else m_bSysClass = TRUE;

		SetClassName(szName);
		return TRUE;
	}
	else return FALSE;
}


//�����ؼ�
BOOL SWidget::Create()
{
	//NOTE:����ע��ؼ�����
	if (!OnPreCreate())
		return FALSE;

	//IMPORTMENT:����ص�������û�ж�WM_NCCREATE��Ϣ���д���ᵼ�·��� NULL
	//TODO:m_szClassName��m_szTitle����������ؼ������������ͻ
	//���ú���CreateWindow��������

	HWND hWnd = ::CreateWindow(
		m_szClassName,								//������ע����
		m_szTitle,									//���ô��ڱ���-����Ψһ
		m_dwStyle,									//���ô��ڷ��
		m_nPosX,									//���ô������Ͻ�X����		
		m_nPosY,									//���ô������Ͻ�Y����	
		m_nWidth,									//���ô��ڿ��
		m_nHeight,									//���ô��ڸ߶�
		m_parentWnd,								//�����ھ��
		m_hMenu,									//�˵��ľ��
		m_hInstance,								//����ʵ�����
		m_lpParam);									//���ݸ���Ϣ������ָ��

	if (!hWnd){										//������ڽ���ʧ���򷵻�FALSE
		::MessageBox(NULL, TEXT("ע�ᴰ��ʧ��"), TEXT("error"), 0);
		SApplication::GetApp()->UnRegisterWidget(this);	//��ע��
		return FALSE;
	}else{
		m_Wnd.SetWnd(hWnd);								//���þ��

		//������Զ�����Ϣ,�򻹱���ע�ᵽ��Ϣ���������Ϣ
		if (!m_bSysClass)
			Subclass(hWnd);

		return TRUE;
	}
	
}

//���ٿؼ�
void SWidget::Destroy(){
	//���ٴ���
	DestroyWindow(m_Wnd.GetWnd());
}

//ģ̬��ʾ
int SWidget::DoModal()
{
	if (!IsCreated()){
		if (Create()){
			::EnableWindow(m_Wnd.GetParent(), FALSE);  //����������

			ShowWindow();
			OnRun();
			OnRan();	//����

			::EnableWindow(m_Wnd.GetParent(), TRUE);//�ͷŸ�����
			HideWindow();//�����Լ�
		}
	}
	else ShowWindow();

	return 0;
}

//��ģ̬��ʾ
void SWidget::Show()
{
	if (!IsCreated()){
		m_pThread->Start();	//�����߳�
	}
	else ShowWindow();

	return;
}
