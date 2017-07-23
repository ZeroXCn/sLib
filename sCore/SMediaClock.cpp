#include "SMediaClock.h"

#include <windows.h>
#include <mmsystem.h>
#pragma   comment(lib,"winmm.lib")

SMediaClock::SMediaClock()
{
	Reset();
}

double SMediaClock::GetClockTick()
{
	return (double)timeGetTime();
}

double SMediaClock::GetTick()
{
	return SMediaClock::GetClockTick();
}
double SMediaClock::GetElpased()
{
	double lNow = GetTick();
	return (double)(lNow - m_dLast - m_dFixAll);
	
}
void SMediaClock::Pause()
{
	m_dFixStart = GetTick();
}
void SMediaClock::Resume()
{
	double lNow = GetTick();
	m_dFixAll += lNow - m_dFixStart;
}
void SMediaClock::Reset()
{
	m_dFixAll = 0;
	m_dLast = GetTick();
}