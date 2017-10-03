/**
*
*	SRunnable�ӿ���
*	SThread�Ľӿ�
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/

#ifndef _SRUNNABLE_H_
#define _SRUNNABLE_H_
#include <functional>

class SRunnable
{
public:
	virtual ~SRunnable() {};

	//�߼��¼�����,������д�˺���
	virtual void Run() = 0;
};

class SRunnableImpl :public SRunnable
{
private:
	std::function<void(void)> m_fCallback;

public:
	SRunnableImpl();
	SRunnableImpl(std::function<void(void)> fCallback);
	virtual ~SRunnableImpl();
public:
	void Run(std::function<void(void)> fCallback);

	virtual void Run();
};

#endif