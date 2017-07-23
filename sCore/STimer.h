/**
*
*	STimer类
*	定时器类
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
	static const int LOW = 1,	//低进度
		MIDDLE = 2,				//中度
		HIGH = 3;				//高度
private:
	SAbstractClock *m_pClock;		//使用的时钟表
	int m_nInterval;				//时间间隔

	bool m_bStop;				//定时器是否停止

	bool m_bSuspend;			//是否被挂起
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