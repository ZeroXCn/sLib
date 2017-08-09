/**
*
*	SThread��
*	�߳���
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
	//�߳�����
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
	��ʼ�����߳�
	@arg bSuspend ��ʼ����ʱ�Ƿ����
	**/
	bool Start(bool bSuspend = false);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/
	virtual void Run();

	/**
	��ǰִ�д˺����̵߳ȴ��߳̽���
	@arg timeout �ȴ���ʱʱ�䣬���Ϊ�������ȴ�����ʱ��
	**/
	void Join(int timeout = -1);
	/**
	�ָ�������߳�
	**/
	void Resume();
	/**
	�����߳�
	**/
	void Suspend();
	/**
	��ֹ�̵߳�ִ��
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