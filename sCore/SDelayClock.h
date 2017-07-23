/**
*
*	SDelayClock类
*	延迟时钟,精度是三者最差
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"

#ifndef _SDELAYTIMER_H_
#define _SDELAYTIMER_H_

class SDelayClock : public SAbstractClock
{
protected:

public:
	double GetTick();
	double GetElpased();
	void Pause();
	void Resume();
	void Reset();

public:
	SDelayClock();

	static double GetClockTick();
};

#endif