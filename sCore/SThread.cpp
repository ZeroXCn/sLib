#include "SThread.h"  


SThread *SThread::Run(function<void(void)> callback)
{
	//TODO:执行线程,并在结束时释放自己-这里并不能做到自我释放,慎用
	SThread *temp = new SThread(new SRunnableImpl(callback));
	return temp;
}

SThread::SThread(void) :
m_pRunnable(NULL),
m_bRun(false)
{
}

SThread::~SThread(void)
{
}

SThread::SThread(SRunnable * pRunnable) :
m_ThreadName(TEXT("")),
m_pRunnable(pRunnable),
m_bRun(false)
{
}

SThread::SThread(const TCHAR * ThreadName, SRunnable *pRunnable) :
m_ThreadName(ThreadName),
m_pRunnable(pRunnable),
m_bRun(false)
{
}

SThread::SThread(SString ThreadName, SRunnable * pRunnable) :
m_ThreadName(ThreadName),
m_pRunnable(pRunnable),
m_bRun(false)
{
}

bool SThread::Start(bool bSuspend)
{
	if (m_bRun)
	{
		return true;
	}
	if (bSuspend)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StatiSThreadFunc, this, CREATE_SUSPENDED, &m_ThreadID);
	}
	else
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StatiSThreadFunc, this, 0, &m_ThreadID);
	}
	m_bRun = (NULL != m_handle);
	return m_bRun;
}

void SThread::Run()
{
	if (!m_bRun)
	{
		return;
	}
	if (NULL != m_pRunnable)
	{
		m_pRunnable->Run();
	}
	m_bRun = false;
}

void SThread::Join(int timeout)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	::WaitForSingleObject(m_handle, timeout);
}

void SThread::Resume()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::ResumeThread(m_handle);
}

void SThread::Suspend()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SuspendThread(m_handle);
}

bool SThread::Terminate(unsigned long ExitCode)
{
	if (NULL == m_handle || !m_bRun)
	{
		return true;
	}
	if (::TerminateThread(m_handle, ExitCode))
	{
		::CloseHandle(m_handle);
		return true;
	}
	return false;
}

unsigned int SThread::GetThreadID()
{
	return m_ThreadID;
}

SString SThread::GetThreadName()
{
	return m_ThreadName;
}

void SThread::SetThreadName(SString ThreadName)
{
	m_ThreadName = ThreadName;
}

void SThread::SetThreadName(const TCHAR* ThreadName)
{
	if (NULL == ThreadName)
	{
		m_ThreadName = TEXT("");
	}
	else
	{
		m_ThreadName = ThreadName;
	}
}

unsigned int SThread::StatiSThreadFunc(void * arg)
{
	SThread * pThread = (SThread *)arg;
	pThread->Run();
	return 0;
}

