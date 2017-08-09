#include "SApplication.h"
using namespace std;

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
BOOL SApplication::RegisterWidget(SWidget *pWidget)
{

	if (m_winset.find(pWidget) == m_winset.end()){
		m_winset.insert(pWidget);
		return TRUE;
	}
	return FALSE;
	
}

BOOL SApplication::UnRegisterWidget(SWidget *pWidget)
{
	auto itr = m_winset.find(pWidget);
	if (itr != m_winset.end())m_winset.erase(itr);
	else return FALSE;
	return TRUE;

}


//�˳�����
void SApplication::QuitWidget(SWidget *pWidget)
{
	//TODO:�߳��˳�,��Դ��һ��������,��Run()����,�����������
	UnRegisterWidget(pWidget);
}

void SApplication::DestroyWidget(SWidget *pWidget)
{
	//NOTE:�����������ʱ��������ɶ���ɾ��
	//delete pWidget;
	UnRegisterWidget(pWidget);
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


set<SWidget *> *SApplication::GetWidgetSet()
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

