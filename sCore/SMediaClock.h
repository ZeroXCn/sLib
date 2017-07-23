/**
*
*	SAbstractClock��
*	�ӳ�ʱ��,����������һ��
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"
#ifndef _SMEDIATIMER_H_
#define _SMEDIATIMER_H_


/**
*	ý���ʱ��
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