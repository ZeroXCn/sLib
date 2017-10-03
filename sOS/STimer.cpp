#include "STimer.h"

#include "../sCore/SDelayClock.h"
#include "../sCore/SMediaClock.h"
#include "../sCore/SFrequencyClock.h"


STimer::STimer(int nType)
{
	m_nInterval = 1000;
	m_bStop = false;
	m_bSuspend = true;
	switch (nType)
	{
	case LOW:
		m_pClock = new SDelayClock();
		break;
	case MIDDLE:
		m_pClock = new SMediaClock();
		break;
	case HIGH:
		m_pClock = new SFrequencyClock();
		break;
	default:
		m_pClock = new SMediaClock();
		break;

	}
}

STimer::~STimer()
{
	m_bStop = true;
	delete m_pClock;
}

void STimer::Run()
{
	while (true)
	{
		if (m_pClock->GetElpased() >= m_nInterval)
		{
			OnEvent();
			m_pClock->Reset();
		}

		if (m_bStop)break;
	}
}

void STimer::OnEvent()
{
	//TODO:为空时当作时钟使用
}

void STimer::Start(int nInterval,bool bSuspend)
{
	m_nInterval = nInterval;
	m_bSuspend = bSuspend;
	if (bSuspend)m_pClock->Pause();
	SThread::Start(bSuspend);
	
}

void STimer::Stop()
{
	m_bStop = true;
}


void STimer::Suspend()
{	
	if (m_bSuspend)return;
	m_bSuspend = true;
	m_pClock->Pause();
	SThread::Suspend();
}
void STimer::Resume()
{
	if (!m_bSuspend)return;
	m_bSuspend = false;
	m_pClock->Resume();
	SThread::Resume();
	
}

bool STimer::IsSupend(){
	return m_bSuspend;
}
bool STimer::IsStop(){
	return m_bStop;
}

double STimer::GetElpased()
{
	return m_pClock->GetElpased();
}