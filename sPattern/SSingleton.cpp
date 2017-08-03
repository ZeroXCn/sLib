#include "SSingleton.h"


SSingleton *SSingleton::g_pInstance = nullptr;		//ȫ��Ψһ����

/////
SSingleton::SSingleton()
{
	//TODO:Ӧ�ò���ͬ������,ֻ�е��������˳��ǻ�����NEW�ĵ���
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