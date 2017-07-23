/**
*
*	SAsyncTask��
*	�첽��������
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

	//��������
	void PublicProgress(TProgress value);

	//�첽ִ��
	void Execute(TParam param);

	//��������
	bool Cancel(bool bCancle);

	//�����Ƿ�����
	bool IsCancelled();

	//ȡ�ý��
	TResult GetResult();
private:
	SThread *m_pThread;		//�߳���

	TParam m_param;			//��¼����
	TResult m_result;		//��¼���

	bool m_bCancel;			//�Ƿ�ȡ��
};

#endif