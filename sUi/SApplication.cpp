#include "SApplication.h"

SApplication *SApplication::g_pApp = NULL;


SApplication::SApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow)
{
	m_hInstance = hInstance;
	m_hPrevInstance = hPrevInstance;
	m_lpCmdline = lpCmdline;
	m_nCmdShow = nCmdShow;

	g_pApp = this;
}
SApplication::~SApplication()
{

}

SApplication *SApplication::GetApp()
{
	
	return g_pApp;
}

///
BOOL SApplication::RegisterWindow(SWindow *pWindow)
{

	if (m_winset.find(pWindow) == m_winset.end()){
		m_winset.insert(pWindow);
		return TRUE;
	}
	return FALSE;
	
}

BOOL SApplication::UnRegisterWindow(SWindow *pWindow)
{
	auto itr = m_winset.find(pWindow);
	if (itr != m_winset.end())m_winset.erase(itr);
	else return FALSE;
	return TRUE;

}


//�˳�����
void SApplication::QuitWindow(SWindow *pWindow)
{
	//TODO:�߳��˳�,��Դ��һ��������,��Run()����,�����������
	UnRegisterWindow(pWindow);
}

void SApplication::DestroyWindow(SWindow *pWindow)
{
	//NOTE:�����������ʱ��������ɶ���ɾ��
	//delete pWindow;
	UnRegisterWindow(pWindow);
}
//ȡ�ô���ʵ��
HINSTANCE SApplication::GetInstance()
{
	return m_hInstance;
}

//ȡ�ø�����ʵ��
HINSTANCE SApplication::GetPrevInstance()
{
	return m_hPrevInstance;
}

//ȡ������������
PSTR SApplication::GetCmdline()
{
	return m_lpCmdline;
}

//ȡ����ʾģʽ������
int SApplication::GetCmdShow()
{
	return m_nCmdShow;
}


set<SWindow *> *SApplication::GetWindowSet()
{
	return &m_winset;
}


//////////
int SApplication::Exec()
{
	while (true)
	{
		if (m_winset.empty())
		{

			break;
		}
		
		//NOTE:����ҪƵ�����,����10ms����CPUʹ��
		::Sleep(10);
	}
	return 0;
}

