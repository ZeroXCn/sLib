#include "SSubject.h"


////
void SSubject::AddObserver(SObserver *pObserver)
{
	if (pObserver)
		m_Obs.push_back(pObserver);
}
void SSubject::DeleteObserver(SObserver *pObserver)
{
	if (pObserver){
		for (auto it = m_Obs.begin(); it != m_Obs.end();it++){
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