/**
*
*	SAbstractClock类
*	延迟时钟,精度是三者一般
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"
#ifndef _SMEDIATIMER_H_
#define _SMEDIATIMER_H_


/**
*	媒体计时器
*/

class SMediaClock :public SAbstractClock
{
protected:

public:
	double GetTick();
	double GetElpased();
	void Pause();
	void Resume(); 
	void Reset();

public:
	SMediaClock();

	static double GetClockTick();
};

#endif