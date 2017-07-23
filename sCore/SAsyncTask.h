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

template <typename TParam,  typename TProgress, typename TResult>
class SAsyncTask :public SRunnable
{
private:
	void Run() final; 
protected:
	virtual TResult DoInBackground(TParam param)=0;

	virtual void OnPreExecute();

	virtual void OnPostExecute(TResult result);

	virtual void OnProgressUpdate(TProgress value);

	virtual void OnCancelled(TResult result);

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

#endif