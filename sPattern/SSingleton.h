/**
* SSingleton类
* 单例模式抽象类
* @author ZeroX
* @version v1.0 03/08/2017
*/
#ifndef _SSINGLETON_H_
#define _SSINGLETON_H_
class SSingleton
{
private:
	static SSingleton *g_pInstance;		//全局唯一单例
private:
	static void SetInstance(SSingleton *pInstance);
private:
	SSingleton();
	~SSingleton();
public:
	//获取全局实例
	static SSingleton *GetInstance();
};
#endif