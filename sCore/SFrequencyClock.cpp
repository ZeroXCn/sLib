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
	//�������m_dFixAll�������ʵ��ʱ�����
	//���Ƶ�����ó�Ա����,�����m_dFixAll����,���·��ʳ�Ա����ʱ���ʵ�������ӳٳ�
	//���ʱ�Ӳ�������ͣ

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