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


//退出窗体
void SApplication::QuitWindow(SWindow *pWindow)
{
	//TODO:线程退出,资源不一定被回收,即Run()结束,不会调用析构
	UnRegisterWindow(pWindow);
}

void SApplication::DestroyWindow(SWindow *pWindow)
{
	//NOTE:如果窗体是临时变量会造成二次删除
	//delete pWindow;
	UnRegisterWindow(pWindow);
}
//取得窗口实例
HINSTANCE SApplication::GetInstance()
{
	return m_hInstance;
}

//取得父窗口实例
HINSTANCE SApplication::GetPrevInstance()
{
	return m_hPrevInstance;
}

//取得启动命令行
PSTR SApplication::GetCmdline()
{
	return m_lpCmdline;
}

//取得显示模式命令行
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
		
		//NOTE:不需要频繁检测,休眠10ms减少CPU使用
		::Sleep(10);
	}
	return 0;
}

