/**
*
*	SException类
*	抽象计时器,定时器
*	@author ZeroX
*	@version v1.0 22/07/2017(03/02/2017)
*
*/
#include "SObject.h"
#ifndef _SABSTRACTCLOCK_H
#define _SABSTRACTCLOCK_H

/*以下时钟默认以毫秒为单位*/
class SAbstractClock :public SObject
{
protected:
	double m_dLast;					//用于记录计时器启动时间
	double m_dFixStart;				//记录暂停开始时间
	double m_dFixAll;				//记录访问函数所花时间

	bool	m_bEnable;				//是否启用计时器
public:
	virtual double GetTick() = 0;		//时间Tick
	virtual double GetElpased() = 0;	//取得流逝的时间
	virtual void Pause() = 0;        // 暂停
	virtual void Resume() = 0;       // 继续
	virtual void Reset() = 0;        // 归零

public:
	void SetEnable(bool bEnable){
		m_bEnable = bEnable;
		if (bEnable)Reset();
		else Pause();
	}

	bool GetEnable(){
		return m_bEnable;
	}

	SAbstractClock(bool bEnable=true){
		m_bEnable = bEnable;
	}

	virtual ~SAbstractClock(){};
};

#endif