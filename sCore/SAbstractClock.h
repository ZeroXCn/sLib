/**
*
*	SException��
*	�����ʱ��,��ʱ��
*	@author ZeroX
*	@version v1.0 22/07/2017(03/02/2017)
*
*/
#include "SObject.h"
#ifndef _SABSTRACTCLOCK_H
#define _SABSTRACTCLOCK_H

/*����ʱ��Ĭ���Ժ���Ϊ��λ*/
class SAbstractClock :public SObject
{
protected:
	double m_dLast;					//���ڼ�¼��ʱ������ʱ��
	double m_dFixStart;				//��¼��ͣ��ʼʱ��
	double m_dFixAll;				//��¼���ʺ�������ʱ��

	bool	m_bEnable;				//�Ƿ����ü�ʱ��
public:
	virtual double GetTick() = 0;		//ʱ��Tick
	virtual double GetElpased() = 0;	//ȡ�����ŵ�ʱ��
	virtual void Pause() = 0;        // ��ͣ
	virtual void Resume() = 0;       // ����
	virtual void Reset() = 0;        // ����

public:
	void SetEnable(bool bEnable){
		m_bEnable = bEnable;
		if (bEnable)Reset();
		else Pause();
	}

	bool GetEnable(){
		return m_bEnable;
	}

	SAbstractClock(bool bEnable=true){
		m_bEnable = bEnable;
	}

	virtual ~SAbstractClock(){};
};

#endif