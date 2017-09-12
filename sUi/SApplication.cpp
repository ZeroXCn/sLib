#include "SApplication.h"
using namespace std;

SApplication *SApplication::g_pApp = nullptr;		//ȫ�ֶ���ָ��
HINSTANCE	SApplication::g_hInstance;				//��ǰ����ʵ�����
HINSTANCE	SApplication::g_hPrevInstance;			//������ʵ�����
PSTR SApplication::g_lpCmdline;						//�����ĸ�������
int SApplication::g_nCmdShow;						//����ģʽ

//////////////////
SApplication::SApplication(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow)
{
	if (!g_pApp){
		g_pApp = this;
		SetParam(hInstance, hPrevInstance, lpCmdline, nCmdShow);
	}
}
SApplication::~SApplication()
{
	
	g_pApp = nullptr;
}

//////
void SApplication::SetParam(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdline, int nCmdShow)
{
	g_hInstance = hInstance;
	g_hPrevInstance = hPrevInstance;
	g_lpCmdline = lpCmdline;
	g_nCmdShow = nCmdShow;
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
	return g_hInstance;
}

//ȡ�ø�����ʵ��
HINSTANCE SApplication::GetPrevInstance()
{
	return g_hPrevInstance;
}

//ȡ������������
PSTR SApplication::GetCmdline()
{
	return g_lpCmdline;
}

//ȡ����ʾģʽ������
int SApplication::GetCmdShow()
{
	return g_nCmdShow;
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

