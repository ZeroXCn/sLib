/**
*
*	STimer��
*	��ʱ����
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"
#include "SThread.h"

#ifndef _STIMER_H_
#define _STIMER_H_

class STimer :
	public SThread
{
public:
	static const int LOW = 1,	//�ͽ���
		MIDDLE = 2,				//�ж�
		HIGH = 3;				//�߶�
private:
	SAbstractClock *m_pClock;		//ʹ�õ�ʱ�ӱ�
	int m_nInterval;				//ʱ����

	bool m_bStop;				//��ʱ���Ƿ�ֹͣ

	bool m_bSuspend;			//�Ƿ񱻹���
private:
	void Run() ;
protected:
	virtual void OnEvent();
public:
	void Start(int nInterval=1000,bool bSuspend = false);
	void Stop();

	void Suspend();
	void Resume();

	bool IsSupend();
	bool IsStop();
public:
	void SetInterval(int nInterval);
	int GetInterval();

	double GetElpased();
	
public:
	STimer(int nType = 2);
	~STimer();
};

#endif