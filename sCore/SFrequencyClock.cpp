#include "SFrequencyClock.h"
#include <Windows.h>

SFrequencyClock::SFrequencyClock()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_dFreq); 
	Reset();
}

double SFrequencyClock::GetClockTick()
{
	double lNow;
	double lFreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&lFreq);
	QueryPerformanceCounter((LARGE_INTEGER*)&lNow);
	return 1000.0*(lNow / lFreq);
}

double SFrequencyClock::GetTick()
{
	double lNow;
	QueryPerformanceCounter((LARGE_INTEGER*)&lNow);
	return lNow;
}

double SFrequencyClock::GetElpased()
{
	double lNow = GetTick();
	//如果加上m_dFixAll会造成与实际时间误差
	//如果频繁调用成员函数,会造成m_dFixAll积累,导致访问成员函数时间比实际所需延迟长
	//因此时钟不可以暂停

	return 1000.0*((double)(lNow - m_dLast - m_dFixAll)) / ((double)m_dFreq);	
	
}
void SFrequencyClock::Pause()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_dFixStart);
}
void SFrequencyClock::Resume()
{

	double lNow = GetTick();
	m_dFixAll += lNow - m_dFixStart;
}
void SFrequencyClock::Reset()
{

	m_dFixAll = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&m_dLast);
}