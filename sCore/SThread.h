/**
*
*	SThread类
*	线程类
*	@author ???
*	@version v1.0 22/07/2017()
*
*/

#include "SObject.h"
#include "SString.h"  
#include "SRunnable.h"

#ifndef _STHREAD_H_
#define _STHREAD_H_

#include <windows.h>  
#include <process.h>  

#include <functional>  

class SThread : 
	public SObject,
	public SRunnable
{
public:
	static SThread *Run(std::function<void(void)> callback);
public:
	//线程休眠
	static void Sleep(DWORD dwMilliseconds);
private:
	explicit SThread(const SThread & rhs);
private:
	
public:
	SThread();
	SThread(SRunnable * pRunnable);
	SThread(const TCHAR* ThreadName, SRunnable * pRunnable = NULL);
	SThread(SString ThreadName, SRunnable * pRunnable = NULL);
	~SThread(void);

	/**
	开始运行线程
	@arg bSuspend 开始运行时是否挂起
	**/
	bool Start(bool bSuspend = false);

	/**
	运行的线程函数，可以使用派生类重写此函数
	**/
	virtual void Run();

	/**
	当前执行此函数线程等待线程结束
	@arg timeout 等待超时时间，如果为负数，等待无限时长
	**/
	void Join(int timeout = -1);
	/**
	恢复挂起的线程
	**/
	void Resume();
	/**
	挂起线程
	**/
	void Suspend();
	/**
	终止线程的执行
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	SString GetThreadName();
	void SetThreadName(SString ThreadName);
	void SetThreadName(const TCHAR* ThreadName);

private:
	static unsigned int WINAPI StatiSThreadFunc(void * arg);

private:
	HANDLE m_handle;
	SRunnable * const m_pRunnable;
	unsigned int m_ThreadID;
	SString m_ThreadName;
	volatile bool m_bRun;

	bool m_bIsLambda;
};

#endif  