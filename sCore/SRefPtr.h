/**
* SRefPtr类
* @brief 智能指针-引用指针-查表
* @details 智能指针,实现垃圾自动回收
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

// 智能指针引用计数类
template <class T>
class REFPTRINFO :public SObject
{
	friend class SRefPtr<T>;
private:
	T* m_pTtr; // 实际的指针
	size_t m_RefCount; // 引用计数
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

// 智能指针对象
template <class T>
class SRefPtr
{
private:
	static std::map<T*, REFPTRINFO<T>*> g_PtrInfoMap;
	REFPTRINFO<T>* m_pRef; // 引用计数
public:
	SRefPtr();
	SRefPtr(T* p);
	virtual ~SRefPtr();
	// 重载运算=,将左对象引用计数-1,并判断是否delete;将右对象+1;
	SRefPtr<T> & operator = (SRefPtr& other);
	SRefPtr<T> & operator = (T* p);
	// 重载指针操作*,->
	T& operator *();
	T* operator ->();
	// 拷贝构造函数,引用计数+1
	SRefPtr(SRefPtr<T>& other);

	int GetRefCount();	//取得引用次数
	T* GetRefPtr();		//取得引用指针
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
	// 将右操作对象引用计数+1
	++(other.m_pRef->m_RefCount);

	// 由于左操作对象指向了新对象,需要将操作数-1;
	// 同时也防止了自赋值的方式.
	// 首先要判断这个对象是否已经指向了其他对象,这个很重要!防止左指针对象为null的情况.
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
		SRefPtr<T> temp; temp.m_pRef = it->second;	//组件一个临时对象
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