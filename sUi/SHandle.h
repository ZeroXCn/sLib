/**
* SHandle��
* HANDLE��װ��
* @author ZeroX
* @version v1.0 18/08/2017
*/
/* ����ģ��-ֻ�ܽ�����ŵ�һ��д */
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
	//ȡ�þ��
	T GetHandle();

	//���þ��
	void SetHandle(T handle);
public:
	//���������
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
	/* �ɱ����Ա�ֶ��ͷ� */
}

//ȡ�þ��
template<class T>
T SHandle<T>::GetHandle()
{
	return m_handle;
}
//���þ��
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