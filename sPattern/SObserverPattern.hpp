/**
*
*	SObserverPattern
*	@brief 观察者模式
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 2017-12-22
*	@update 2017-12-22
*/
#ifndef _SOBSERVERPATTERN_H_
#define _SOBSERVERPATTERN_H_
#include <vector>

class SSubject;			//主题
class SObserver;		//观察者

class SSubject
{

public:
	//添加,删除观察者
	void AddObserver(SObserver *pObserver);
	void DeleteObserver(SObserver *pObserver);

	//主题数据是否发生改变
	bool HasChanged();

	//通知观察者更新数据
	void NotifyObserver(void *data);
	void NotifyObservers();
protected:
	//设置主题变化标志
	void SetChanged(bool bChange = true);

	//清除主题变化变化标志
	void ClearChanged();
protected:
	SSubject();
	virtual~SSubject();
private:
	std::vector<SObserver *> m_Obs;
	bool m_bChanged;
};
void SSubject::AddObserver(SObserver *pObserver)
{
	if (pObserver)
		m_Obs.push_back(pObserver);
}
void SSubject::DeleteObserver(SObserver *pObserver)
{
	if (pObserver){
		for (auto it = m_Obs.begin(); it != m_Obs.end(); it++){
			if (*it == pObserver){
				m_Obs.erase(it);
				break;
			}
		}
	}
}

bool SSubject::HasChanged()
{
	return m_bChanged;
}

void SSubject::NotifyObserver(void *data)
{
	for (auto it : m_Obs){
		it->Update(this, data);
	}
}
void SSubject::NotifyObservers()
{
	for (auto it : m_Obs){
		it->Update(this, nullptr);
	}
}

void SSubject::SetChanged(bool bChange)
{
	m_bChanged = bChange;
}
void SSubject::ClearChanged()
{
	m_bChanged = false;
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

class SObserver
{
public:
	//观察者更新数据
	void Update(SSubject *pSubject, void *date);
};
void SObserver::Update(SSubject *pSubject, void *date)
{

}
#endif