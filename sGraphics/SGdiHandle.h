/**
* SGdiObject��
* GDI���������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObj.h"
#ifndef _SGDIHANDLE_H_
#define _SGDIHANDLE_H_

template <class TA,class TB>
class SGdiHandle :public SGdiObj
{
public:
	SGdiHandle(TA hGdiObj = NULL);
	virtual ~SGdiHandle();
public:
	//ȡ�ķ�װ����
	using SGdiObj::GetHandle;		//��֪Ϊ�β�����ɵ��ò���ȷ������
	TA GetHandle();
	//���÷�װ����
	void SetHandle(TA hGdiObj);
	using SGdiObj::SetHandle;

public:	
	//��ȡλͼ�ṹ
	int GetHandleStruct(int cbBuffer, LPVOID lpvObject);
	TB GetHandleStruct();

};

template <class TA, class TB>
SGdiHandle<TA, TB>::SGdiHandle(TA hGdiObj)
:SGdiObj(hGdiObj)
{

}
template <class TA, class TB>
SGdiHandle<TA, TB>::~SGdiHandle()
{
	//DOUBT:Ӧ���ͷ���Щ��Create()�Ķ���
}

/////
template <class TA, class TB>
TA SGdiHandle<TA,TB>::GetHandle()
{
	return (TA)m_hGdiObj;
}
template <class TA, class TB>
void SGdiHandle<TA, TB>::SetHandle(TA hGdiObj)
{
	m_hGdiObj = (TA)hGdiObj;
}

//��ȡλͼ�ṹ
template <class TA, class TB>
TB SGdiHandle<TA, TB>::GetHandleStruct()
{
	TB  bm;
	GetHandleStruct(sizeof(TB), &bm);
	return bm;
}

template <class TA, class TB>
int SGdiHandle<TA, TB>::GetHandleStruct(int cbBuffer, LPVOID lpvObject)
{
	return ::GetObject(m_hGdiObj, cbBuffer, lpvObject);
}

#endif