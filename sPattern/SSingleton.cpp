#include "SSingleton.h"


SSingleton *SSingleton::g_pInstance = nullptr;		//全局唯一单例

/////
SSingleton::SSingleton()
{
	//TODO:应该采用同步机制,只有当本单例退出是唤醒欲NEW的单例
	SetInstance(this);
}

SSingleton::~SSingleton()
{
	g_pInstance = nullptr;
}
void SSingleton::SetInstance(SSingleton *pInstance)
{
	if (g_pInstance == nullptr)
		g_pInstance = pInstance;
}

SSingleton *SSingleton::GetInstance()
{
	return g_pInstance;
}