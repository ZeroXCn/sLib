#include "SApplication.h"
using namespace std;

SApplication *SApplication::g_pApp = nullptr;		//全局对象指针
HINSTANCE	SApplication::g_hInstance;				//当前程序实例句柄
HINSTANCE	SApplication::g_hPrevInstance;			//父程序实例句柄
PSTR SApplication::g_lpCmdline;						//启动的附加命令
int SApplication::g_nCmdShow;						//启动模式

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


//退出窗体
void SApplication::QuitWidget(SWidget *pWidget)
{
	//TODO:线程退出,资源不一定被回收,即Run()结束,不会调用析构
	UnRegisterWidget(pWidget);
}

void SApplication::DestroyWidget(SWidget *pWidget)
{
	//NOTE:如果窗体是临时变量会造成二次删除
	//delete pWidget;
	UnRegisterWidget(pWidget);
}
//取得窗口实例
HINSTANCE SApplication::GetInstance()
{
	return g_hInstance;
}

//取得父窗口实例
HINSTANCE SApplication::GetPrevInstance()
{
	return g_hPrevInstance;
}

//取得启动命令行
PSTR SApplication::GetCmdline()
{
	return g_lpCmdline;
}

//取得显示模式命令行
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
		
		//NOTE:不需要频繁检测,休眠10ms减少CPU使用
		::Sleep(10);
	}
	return 0;
}

