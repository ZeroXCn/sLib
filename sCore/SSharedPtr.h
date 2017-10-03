/**
* SSharedPtr类
* @brief 智能指针-分享指针
* @details 智能指针,实现垃圾自动回收
* @author inzaghihalo
* @link http://blog.csdn.net/superinzaghi747/article/details/52638709
* @version v1.0
* @date 2016-09-23
* @update 2017-09-25
*/
#include "SObject.h"

#ifndef _SSHAREDPTR_H
#define _SSHAREDPTR_H

template <class T>
class SSharedPtr;

// 智能指针引用计数类
template <class T>
class SHAREDPTRINFO
{
	friend class SSharedPtr<T>;
private:
	T* m_pTtr; // 实际的指针
	size_t m_RefCount; // 引用计数
	SHAREDPTRINFO(T* p);
	virtual ~SHAREDPTRINFO();
};

template <class T>
SHAREDPTRINFO<T>::SHAREDPTRINFO(T* p)
{
	m_pTtr = p;
	m_RefCount = 1;
}

template <class T>
SHAREDPTRINFO<T>::~SHAREDPTRINFO()
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
class SSharedPtr:public SObject
{
private:
	SHAREDPTRINFO<T>* m_pShread; // 引用计数
public:
	SSharedPtr();
	SSharedPtr(T* p);
	SSharedPtr(SSharedPtr<T>& other);// 拷贝构造函数,引用计数+1
	~SSharedPtr();

	// 重载运算=,将左对象引用计数-1,并判断是否delete;将右对象+1;
	SSharedPtr<T> & operator = (SSharedPtr& other);
	// 重载指针操作*,->
	T& operator *();
	T* operator ->();

	int GetRefCount();	//取得引用次数
	T* GetRefPtr();		//取得引用指针
};

template <class T>
SSharedPtr<T>::SSharedPtr()
{
	m_pShread = NULL;
}

template<class T>
SSharedPtr<T>::SSharedPtr(T* p)
{
	//为每一个新指针new一个
	m_pShread = new SHAREDPTRINFO<T>(p);
}

template <class T>
SSharedPtr<T>::SSharedPtr(SSharedPtr<T>& other)
{
	this->m_pShread = other.m_pShread;
	++(m_pShread->m_RefCount);
}

template <class T>
SSharedPtr<T>& SSharedPtr<T>::operator=(SSharedPtr& other)
{
	// 将右操作对象引用计数+1
	++(other.m_pShread->m_RefCount);

	// 由于左操作对象指向了新对象,需要将操作数-1;
	// 同时也防止了自赋值的方式.
	// 首先要判断这个对象是否已经指向了其他对象,这个很重要!防止左指针对象为null的情况.
	if (this->m_pShread)
	{
		if (--(this->m_pShread->m_RefCount) == 0)
		{
			delete this->m_pShread;
		}
	}

	this->m_pShread = other.m_pShread;
	return *this;
}

template <class T>
T& SSharedPtr<T>::operator *()
{
	return *(m_pShread->m_pTtr);
}

template <class T>
T* SSharedPtr<T>::operator->()
{
	return (m_pShread->m_pTtr);
}

template <class T>
SSharedPtr<T>::~SSharedPtr()
{
	if (m_pShread)
	{
		if ((--m_pShread->m_RefCount) == 0)
		{
			delete m_pShread;
			m_pShread = NULL;
		}
	}
}

template <class T>
int SSharedPtr<T>::GetRefCount()
{
	if (m_pShread)
		return m_pShread->m_RefCount;
	return 0;
}
template <class T>
T* SSharedPtr<T>::GetRefPtr()
{
	if (m_pShread)
		return (m_pShread->m_pTtr);
	return NULL;
}
#endif