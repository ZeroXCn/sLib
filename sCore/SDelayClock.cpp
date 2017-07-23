#include "SDelayClock.h"
#include "windows.h"
SDelayClock::SDelayClock()
{
	Reset();
}

double SDelayClock::GetClockTick()
{
	return GetTickCount();
}

double SDelayClock::GetTick()
{
	return SDelayClock::GetClockTick();
}
double SDelayClock::GetElpased()
{
	double lNow = GetTick();
	return (double)(lNow - m_dLast - m_dFixAll);
}
void SDelayClock::Pause()
{
	m_dFixStart = GetTick();
}
void SDelayClock::Resume()
{
	double lNow = GetTick();
	m_dFixAll += lNow - m_dFixStart;
}
void SDelayClock::Reset()
{
	m_dFixAll = 0;
	m_dLast = GetTick();
}

