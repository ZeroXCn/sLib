/**
*
*	SSingletonPattern
*	@brief 单例模式
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 2017-12-22
*	@update 2017-12-22
*/
#ifndef _SSINGLETONPATTERN_H_
#define _SSINGLETONPATTERN_H_
/**
* SSingleton类
* 单例模式抽象类
* @author ZeroX
* @version v1.0 03/08/2017
*/
template<class T>
class SSingleton
{
private:
	static T *g_pInstance;		//全局唯一单例
protected:
	SSingleton();
	virtual ~SSingleton();

public:
	//新建全局实例
	static T *NewInstance();

	//获取全局实例
	static T *GetInstance();

	//设置全局实例
	static void SetInstance(T *pInstance);

	//摧毁全局实例
	static void DestroyInstance();
};
template<class T>
T *SSingleton<T>::g_pInstance = nullptr;		//全局唯一单例

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
	//TODO :需要加锁
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