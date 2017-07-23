/**
*
*	SRunnable��
*	SThread�Ľӿ�
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/
#include "SObject.h"

#ifndef _SRUNNABLE_H_
#define _SRUNNABLE_H_
#include <functional>

class SRunnable :public SObject
{
public:
	virtual ~SRunnable() {};

	//�߼��¼�����,������д�˺���
	virtual void Run() = 0;
};

class SRunnableImpl :public SRunnable
{
public:
	function<void(void)> m_callback;
public:
	SRunnableImpl(function<void(void)> callback);
public:
	virtual void Run();
};

#endif