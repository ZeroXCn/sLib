/**
*
*	SFrequencyClock类
*	延迟时钟,精度是三者最精
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"
#ifndef SFREQUENCYTIMER_H
#define SFREQUENCYTIMER_H

/**
*	高精度计时器
*	精度较高的时候用
*/
class SFrequencyClock :public SAbstractClock
{
protected:
	double m_dFreq;

public:
	SFrequencyClock();

public:
	double GetTick();
	double GetElpased();
	void Pause();
	void Resume();
	void Reset();
public:
	static double GetClockTick();
};

#endif