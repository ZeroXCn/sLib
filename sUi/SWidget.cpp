#include "SWidget.h"

SWidget::SWidget(SWidget *parent)
{
	m_pParent = parent;

	m_hInstance = (HINSTANCE)GetWindowLong(NULL, GWL_HINSTANCE);//GetModuleHandle(NULL);  
	//m_hInstance = SApplication::GetApp()->GetInstance();

	m_hMenu = NULL;
	m_lpParam = NULL;

	m_nPosX = 0;
	m_nPosY = 0;
	m_nWidth = 480;
	m_nHeight = 480;
	m_bEnabled = TRUE;
	m_bVisible = TRUE;

	lstrcpy(m_szClassName, TEXT("Widget"));
	lstrcpy(m_szTitle, TEXT("Widget"));
	lstrcpy(m_szTip, TEXT(""));

}
SWidget::~SWidget()
{
	
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
		dc.SetDc(m_Wnd.GetDC());
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
////////////////////////
//��ʾ�ؼ�
void SWidget::Show()
{
	Show(SW_SHOWNORMAL);
}
void SWidget::Show(int nCmdShow)
{
	m_Wnd.ShowWindow( nCmdShow);	//��ʾ�ؼ�
}

//���ؿؼ�
void SWidget::Hide()
{
	Show(SW_HIDE);
}

//���¿ؼ�
void SWidget::Update()
{
	if (m_Wnd.GetWnd())
	{
		m_Wnd.InvalidateRect( NULL, FALSE);	//�����������һ������Ϊ��������,��Ҫ��������
		m_Wnd.UpdateWindow();					//ǿ��ˢ�´���
	}
}
void SWidget::Update(int left, int top, int right, int bottom)
{
	if (m_Wnd.GetWnd())
	{
		RECT temp;
		temp.left = left;
		temp.top = top;
		temp.right = right;
		temp.bottom = bottom;
		m_Wnd.InvalidateRect(&temp, FALSE);	//�����������һ������,��Ҫ��������
		m_Wnd.UpdateWindow();					//ǿ��ˢ�´���,
	}
}

//�ػ�ؼ�
void SWidget::RePaint()
{

	if (m_Wnd.GetWnd())
	{
		m_Wnd.InvalidateRect(NULL, FALSE);	//ǿ��ˢ�´���,��Ҫ��������
		m_Wnd.RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:�������������ⲻ�Ǻܺ�
	}
	
}


//�����ؼ�
BOOL SWidget::Create()
{
	//IMPORTMENT:����ص�������û�ж�WM_NCCREATE��Ϣ���д���ᵼ�·��� NULL
	//TODO:m_szClassName��m_szTitle����������ؼ������������ͻ
	//���ú���CreateWindow��������
	HWND hWnd = ::CreateWindow(
		m_szClassName,								//������ע����
		m_szTitle,									//���ô��ڱ���-����Ψһ
		m_dwStyle,									//���ô��ڷ��
		m_nPosX,									//���ô������Ͻ�X����		
		m_nPosY,									//���ô������Ͻ�Y����	
		m_nWidth,									//���ô��ڿ�� + 10��Ϊ����ʵ�ʴ�Сһ��
		m_nHeight,									//���ô��ڸ߶� + 8ԭ��ͬ��
		m_pParent ? m_pParent->GetWnd().GetWnd() : NULL,		//�����ھ��
		m_hMenu,									//�˵��ľ��
		m_hInstance,								//����ʵ�����
		m_lpParam);									//���ݸ���Ϣ������ָ��

	if (!hWnd){									//������ڽ���ʧ���򷵻�FALSE
		return FALSE;
	}

	m_Wnd.SetWnd(hWnd);


	Update();										//�����ػ���Ϣ

	return TRUE;
}

//���ٿؼ�
void SWidget::Destroy(){
	//TODO:���������ддʲô...
}