/**
*
*	SFrequencyClock��
*	�ӳ�ʱ��,�����������
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SAbstractClock.h"
#ifndef SFREQUENCYTIMER_H
#define SFREQUENCYTIMER_H

/**
*	�߾��ȼ�ʱ��
*	���Ƚϸߵ�ʱ����
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