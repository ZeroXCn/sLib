/**
* SSingleton��
* ����ģʽ������
* @author ZeroX
* @version v1.0 03/08/2017
*/
#ifndef _SSINGLETON_H_
#define _SSINGLETON_H_
class SSingleton
{
private:
	static SSingleton *g_pInstance;		//ȫ��Ψһ����
private:
	static void SetInstance(SSingleton *pInstance);
private:
	SSingleton();
	~SSingleton();
public:
	//��ȡȫ��ʵ��
	static SSingleton *GetInstance();
};
#endif