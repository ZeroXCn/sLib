/**
* SRefPtr��
* @brief ����ָ��-����ָ��-���
* @details ����ָ��,ʵ�������Զ�����
* @author inzaghihalo
* @link http://blog.csdn.net/superinzaghi747/article/details/52638709
* @version v1.0
* @date 2016-09-23
* @update 2017-09-25
*/
#include "SObject.h"

#ifndef _SREFPTR_H
#define _SREFPTR_H

#include <map>
template <class T>
class SRefPtr;

// ����ָ�����ü�����
template <class T>
class REFPTRINFO :public SObject
{
	friend class SRefPtr<T>;
private:
	T* m_pTtr; // ʵ�ʵ�ָ��
	size_t m_RefCount; // ���ü���
	REFPTRINFO(T* p);
	virtual ~REFPTRINFO();
};

template <class T>
REFPTRINFO<T>::REFPTRINFO(T* p)
{
	m_pTtr = p;
	m_RefCount = 1;
}

template <class T>
REFPTRINFO<T>::~REFPTRINFO()
{
	if (m_pTtr)
	{
		delete m_pTtr;
		m_RefCount = 0;
	}
	m_pTtr = NULL;
}

// ����ָ�����
template <class T>
class SRefPtr
{
private:
	static std::map<T*, REFPTRINFO<T>*> g_PtrInfoMap;
	REFPTRINFO<T>* m_pRef; // ���ü���
public:
	SRefPtr();
	SRefPtr(T* p);
	virtual ~SRefPtr();
	// ��������=,����������ü���-1,���ж��Ƿ�delete;���Ҷ���+1;
	SRefPtr<T> & operator = (SRefPtr& other);
	SRefPtr<T> & operator = (T* p);
	// ����ָ�����*,->
	T& operator *();
	T* operator ->();
	// �������캯��,���ü���+1
	SRefPtr(SRefPtr<T>& other);

	int GetRefCount();	//ȡ�����ô���
	T* GetRefPtr();		//ȡ������ָ��
};
template <class T>
std::map<T*, REFPTRINFO<T>*> SRefPtr<T>::g_PtrInfoMap;

///
template <class T>
SRefPtr<T>::SRefPtr()
{
	m_pRef = NULL;
}

template<class T>
SRefPtr<T>::SRefPtr(T* p)
{
	*this = p;
}

template <class T>
SRefPtr<T>::SRefPtr(SRefPtr<T>& other)
{
	this->m_pRef = other.m_pRef;
	++(m_pRef->m_RefCount);
}

template <class T>
SRefPtr<T>& SRefPtr<T>::operator=(SRefPtr& other)
{
	// ���Ҳ����������ü���+1
	++(other.m_pRef->m_RefCount);

	// �������������ָ�����¶���,��Ҫ��������-1;
	// ͬʱҲ��ֹ���Ը�ֵ�ķ�ʽ.
	// ����Ҫ�ж���������Ƿ��Ѿ�ָ������������,�������Ҫ!��ֹ��ָ�����Ϊnull�����.
	if (this->m_pRef)
	{
		if (--(this->m_pRef->m_RefCount) == 0)
		{
			g_PtrInfoMap.erase(this->m_pRef->m_pTtr);
			delete this->m_pRef;
		}
	}

	this->m_pRef = other.m_pRef;
	return *this;
}


template <class T>
SRefPtr<T> &SRefPtr<T>::operator = (T* p)
{
	std::map<T*, REFPTRINFO<T>*>::iterator it = g_PtrInfoMap.find(p);
	if (it != g_PtrInfoMap.end())
	{
		SRefPtr<T> temp; temp.m_pRef = it->second;	//���һ����ʱ����
		*this = temp;
		temp.m_pRef = NULL;
	}
	else
	{
		m_pRef = new REFPTRINFO<T>(p);
		g_PtrInfoMap.insert(std::pair<T*, REFPTRINFO<T>*>(p, m_pRef));
	}
	return *this;
}


template <class T>
T& SRefPtr<T>::operator *()
{
	return *(m_pRef->m_pTtr);
}

template <class T>
T* SRefPtr<T>::operator->()
{
	return (m_pRef->m_pTtr);
}

template <class T>
SRefPtr<T>::~SRefPtr()
{
	if (m_pRef)
	{
		if ((--m_pRef->m_RefCount) == 0)
		{
			g_PtrInfoMap.erase(this->m_pRef->m_pTtr);
			delete m_pRef;
			m_pRef = NULL;
		}
	}
}

template <class T>
int SRefPtr<T>::GetRefCount()
{
	if (m_pRef)
		return m_pRef->m_RefCount;
	return 0;
}
template <class T>
T* SRefPtr<T>::GetRefPtr()
{
	if (m_pRef)
		return (m_pRef->m_pTtr);
	return NULL;
}
#endif