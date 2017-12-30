/**
*
*	SSingletonPattern
*	@brief ����ģʽ
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 2017-12-22
*	@update 2017-12-22
*/
#ifndef _SSINGLETONPATTERN_H_
#define _SSINGLETONPATTERN_H_
/**
* SSingleton��
* ����ģʽ������
* @author ZeroX
* @version v1.0 03/08/2017
*/
template<class T>
class SSingleton
{
private:
	static T *g_pInstance;		//ȫ��Ψһ����
protected:
	SSingleton();
	virtual ~SSingleton();

public:
	//�½�ȫ��ʵ��
	static T *NewInstance();

	//��ȡȫ��ʵ��
	static T *GetInstance();

	//����ȫ��ʵ��
	static void SetInstance(T *pInstance);

	//�ݻ�ȫ��ʵ��
	static void DestroyInstance();
};
template<class T>
T *SSingleton<T>::g_pInstance = nullptr;		//ȫ��Ψһ����

/////
template<class T>
SSingleton<T>::SSingleton()
{

}
template<class T>
SSingleton<T>::~SSingleton()
{

}

template<class T>
T *SSingleton<T>::NewInstance()
{
	//TODO :��Ҫ����
	if (g_pInstance == nullptr)
		g_pInstance = new T();
	else DestroyInstance();
	return GetInstance();
}

template<class T>
void SSingleton<T>::SetInstance(T *pInstance)
{
	if (g_pInstance == nullptr)
		g_pInstance = pInstance;
}

template<class T>
T *SSingleton<T>::GetInstance()
{
	if (g_pInstance == nullptr)
		NewInstance();
	return g_pInstance;
}
template<class T>
void SSingleton<T>::DestroyInstance()
{
	delete g_pInstance;
	g_pInstance = nullptr;
}
#endif