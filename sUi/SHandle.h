/**
* SHandle类
* HANDLE封装类
* @author ZeroX
* @version v1.0 18/08/2017
*/
/* 泛型模板-只能将代码放到一块写 */
#include "../sCore/SObject.h"
#ifndef _SHANDLE_H_
#define _SHANDLE_H_
#include <Windows.h>

template<class T=HANDLE>
class SHandle :public SObject
{
protected:
	T m_handle;
public:
	SHandle(T handel=NULL);
	virtual ~SHandle();
public:
	//取得句柄
	T GetHandle();

	//设置句柄
	void SetHandle(T handle);
public:
	//运算符重载
	virtual BOOL operator !=(SHandle<T> &handle);
	virtual BOOL operator ==(SHandle<T> &handle);
};

template<class T>
SHandle<T>::SHandle(T handel)
{
	SetHandle(handel);
}
template<class T>
SHandle<T>::~SHandle()
{
	/* 由编程人员手动释放 */
}

//取得句柄
template<class T>
T SHandle<T>::GetHandle()
{
	return m_handle;
}
//设置句柄
template<class T>
void SHandle<T>::SetHandle(T handle)
{
	m_handle = handle;
}

//////
template<class T>
BOOL SHandle<T>::operator !=(SHandle<T> &handle)
{
	return (this->GetHandle() != handle.GetHandle()) ? TRUE : FALSE;
}

template<class T>
BOOL SHandle<T>::operator ==(SHandle<T> &handle)
{
	return (this->GetHandle() == handle.GetHandle()) ? TRUE : FALSE;
}

#endif