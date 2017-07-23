#include "SAsyncTask.h"

template <typename TParam, typename TProgress, typename TResult>
SAsyncTask<TParam, TProgress, TResult>::SAsyncTask()
{
	m_pThread = new Thread(this);
	m_bCancle = false;
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

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPreExecute()
{

}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnPostExecute(TResult result)
{

}


template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnProgressUpdate(TProgress value)
{

}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::OnCancelled(TResult result)
{

}


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
	}else{
		m_pThread->Suspend();
		OnCancelled(m_result);
	}
	m_bCancel=bCancle;
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