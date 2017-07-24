#include "SWidget.h"

SWidget::SWidget(SWidget *parent)
{
	m_pParent = parent;
	m_hWnd = NULL;
	m_hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);//GetModuleHandle(NULL);  
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
void SWidget::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
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
HWND SWidget::GetWnd()
{
	return m_hWnd;
}

//��ȡ�豸������
HDC SWidget::GetDC()
{
	if (m_hWnd)
		return ::GetDC(m_hWnd);
	return NULL;
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
LPTSTR (SWidget::GetClassName)()
{
	return m_szClassName;
}

/* ���ÿؼ����� */
void SWidget::SetTitle(LPTSTR szTitle)
{
	lstrcpy(m_szTitle, szTitle);					//�����⸳��m_szTitle
	if (m_hWnd)
		::SetWindowText(m_hWnd, m_szTitle);
}
LPTSTR SWidget::GetTitle()
{
	return m_szTitle;
}
LPTSTR SWidget::GetTitle(LPTSTR szTitle, int iCount)
{
	if (m_hWnd){
		::GetWindowText(m_hWnd, szTitle, iCount);
		return szTitle;
	}
	else
		return m_szTitle;
}

/* ���ÿؼ���ʽ */
void SWidget::SetStyle(DWORD dwStyle)
{
	if (m_hWnd){
		::SetWindowLong(m_hWnd, m_dwStyle, dwStyle);
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
	if (m_hWnd){
		RECT rt{ 0, 0, 0, 0 };
		::GetWindowRect(m_hWnd, &rt); //���window����
		/**/
		pt.x = rt.left; pt.y = rt.top;
		::ScreenToClient(m_hWnd, &pt); //ת��client
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
	if (m_hWnd){
		::SetWindowPos(m_hWnd, NULL, m_nPosX, m_nPosY, m_nWidth, m_nHeight, 0);
	}
}

void SWidget::MovePos(int x, int y)
{
	m_nPosX = x;
	m_nPosY = y;
	if (m_hWnd){
		::MoveWindow(m_hWnd, x, y, m_nWidth, m_nHeight, FALSE);
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

	if (m_hWnd){
		::GetWindowRect(m_hWnd, &rt);
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

////////////////////////
//��ʾ�ؼ�
void SWidget::Show()
{
	Show(SW_SHOWNORMAL);
}
void SWidget::Show(int nCmdShow)
{
	::ShowWindow(m_hWnd,nCmdShow);	//��ʾ�ؼ�
}

//���ؿؼ�
void SWidget::Hide()
{
	Show(SW_HIDE);
}

//���¿ؼ�
void SWidget::Update()
{
	if (m_hWnd)
	{
		::InvalidateRect(m_hWnd, NULL, FALSE);	//�����������һ������Ϊ��������,��Ҫ��������
		::UpdateWindow(m_hWnd);					//ǿ��ˢ�´���
	}
}
void SWidget::Update(int left, int top, int right, int bottom)
{
	if (m_hWnd)
	{
		RECT temp;
		temp.left = left;
		temp.top = top;
		temp.right = right;
		temp.bottom = bottom;
		::InvalidateRect(m_hWnd, &temp, FALSE);	//�����������һ������,��Ҫ��������
		::UpdateWindow(m_hWnd);					//ǿ��ˢ�´���,
	}
}

//�ػ�ؼ�
void SWidget::RePaint()
{

	if (m_hWnd)
	{
		::InvalidateRect(m_hWnd, NULL, FALSE);	//ǿ��ˢ�´���,��Ҫ��������
		::RedrawWindow(m_hWnd, NULL,NULL,  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);	//DOUBT:�������������ⲻ�Ǻܺ�
	}
	
}


//�����ؼ�
BOOL SWidget::Create()
{
	//IMPORTMENT:����ص�������û�ж�WM_NCCREATE��Ϣ���д���ᵼ�·��� NULL
	//TODO:m_szClassName��m_szTitle����������ؼ������������ͻ
	//���ú���CreateWindow��������
	m_hWnd = ::CreateWindow(
		m_szClassName,								//������ע����
		m_szTitle,									//���ô��ڱ���-����Ψһ
		m_dwStyle,									//���ô��ڷ��
		m_nPosX,									//���ô������Ͻ�X����		
		m_nPosY,									//���ô������Ͻ�Y����	
		m_nWidth,									//���ô��ڿ�� + 10��Ϊ����ʵ�ʴ�Сһ��
		m_nHeight,									//���ô��ڸ߶� + 8ԭ��ͬ��
		m_pParent ? m_pParent->GetWnd() : NULL,		//�����ھ��
		m_hMenu,									//�˵��ľ��
		m_hInstance,								//����ʵ�����
		m_lpParam);									//���ݸ���Ϣ������ָ��

	if (!m_hWnd){									//������ڽ���ʧ���򷵻�FALSE
		return FALSE;
	}

	Update();										//�����ػ���Ϣ

	return TRUE;
}

//���ٿؼ�
void SWidget::Destroy(){
	//TODO:���������ддʲô...
}