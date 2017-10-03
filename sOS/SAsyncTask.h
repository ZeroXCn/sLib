/**
*
*	SAsyncTask类
*	异步任务处理类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SThread.h"

#ifndef _SASYNCTASK_H_
#define _SASYNCTASK_H_
#include <functional>

template <typename TParam,  typename TProgress, typename TResult>
class SAsyncTask :public SRunnable
{
private:
	//lambda表达式
	std::function<TResult(TParam param)> m_fDoInBackground;
	std::function<void()> m_fOnPreExecute;
	std::function<void(TResult result)> m_fOnPostExecute;
	std::function<void(TProgress value)> m_fOnProgressUpdate;
	std::function<void(TResult result)> m_fOnCancelled;
private:
	void Run() final; 
protected:
	//后台处理任务
	virtual TResult DoInBackground(TParam param);
	//执行前处理任务
	virtual void OnPreExecute();
	//结果返回处理
	virtual void OnPostExecute(TResult result);
	//进度处理
	virtual void OnProgressUpdate(TProgress value);
	//取消处理
	virtual void OnCancelled(TResult result);

public:
	TResult DoInBackground(std::function<TResult(TParam param)> fDoInBackground);
	void OnPreExecute(std::function<void()> fOnPreExecute);
	void OnPostExecute(std::function<void(TResult result)> fOnPostExecute);
	void OnProgressUpdate(std::function<void(TProgress value)> fOnProgressUpdate);
	void OnCancelled(std::function<void(TResult result)> fOnCancelled);

public:
	SAsyncTask();
	virtual ~SAsyncTask();

	//公布进度
	void PublicProgress(TProgress value);

	//异步执行
	void Execute(TParam param);

	//悬挂任务
	bool Cancel(bool bCancle);

	//任务是否被悬挂
	bool IsCancelled();

	//取得结果
	TResult GetResult();
private:
	SThread *m_pThread;		//线程类

	TParam m_param;			//记录参数
	TResult m_result;		//记录结果

	bool m_bCancel;			//是否被取消
};
template <typename TParam, typename TProgress, typename TResult>
SAsyncTask<TParam, TProgress, TResult>::SAsyncTask()
{
	m_pThread = new Thread(this);
	m_bCancle = false;

	m_fDoInBackground = [](TParam param){return NULL; };
	m_fOnPreExecute = [](){};
	m_fOnPostExecute = [](TResult result){};
	m_fOnProgressUpdate = [](TProgress value){};
	m_fOnCancelled = [](TResult result){};
}

template <typename TParam, typename TProgress, typename TResult>
SAsyncTask<TParam, TProgress, TResult>::~SAsyncTask()
{
	delete m_pThread;
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::Run()
{
	m_result = DoInBackground(m_param);
	OnPostExecute(m_result);

}
/////////////////
template <typename TParam, typename TProgress, typename TResult>
TResult SAsyncTask<TParam, TProgress, TResult>::DoInBackground(TParam param)
{
	//TODO:在这里公布执行进度
	return m_fDoInBackground(param);
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPreExecute()
{
	m_fOnPreExecute();
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPostExecute(TResult result)
{
	m_fOnPostExecute(result);
}


template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnProgressUpdate(TProgress value)
{
	m_fOnProgressUpdate(value);
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnCancelled(TResult result)
{
	m_fOnCancelled(result);
}

///////////////////////
template <typename TParam, typename TProgress, typename TResult>
TResult SAsyncTask<TParam, TProgress, TResult>::DoInBackground(std::function<TResult(TParam param)> fDoInBackground)
{
	m_fDoInBackground = fDoInBackground;
}
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPreExecute(std::function<void()> fOnPreExecute)
{
	m_fOnPreExecute = fOnPreExecute;
}
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPostExecute(std::function<void(TResult result)> fOnPostExecute)
{
	m_fOnPostExecute = fOnPostExecute;
}
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnProgressUpdate(std::function<void(TProgress value)> fOnProgressUpdate)
{
	m_fOnProgressUpdate = fOnProgressUpdate;
}
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnCancelled(std::function<void(TResult result)> fOnCancelled)
{
	m_fOnCancelled = fOnCancelled;
}


///////////////////////
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::PublicProgress(TProgress value)
{
	OnProgressUpdate(value);
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::Execute(TParam param)
{
	m_pParam = param;
	OnPreExecute();
	m_pThread->Start();
}

template <typename TParam, typename TProgress, typename TResult>
bool SAsyncTask<TParam, TProgress, TResult>::Cancel(bool bCancel)
{
	//DOUBT:貌似不应该这么写
	if (bCancle){
		m_pThread->Resume();
	}
	else{
		m_pThread->Suspend();
		OnCancelled(m_result);
	}
	m_bCancel = bCancle;
	return bCancle;

}

template <typename TParam, typename TProgress, typename TResult>
bool SAsyncTask<TParam, TProgress, TResult>::IsCancelled()
{
	return m_bCancel;
}

template <typename TParam, typename TProgress, typename TResult>
TResult SAsyncTask<TParam, TProgress, TResult>::GetResult()
{
	return m_result;
}
#endif