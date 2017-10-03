/**
* SGdiObject类
* GDI物件抽象类
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
	//取的封装内容
	using SGdiObj::GetHandle;		//不知为何不会造成调用不明确的问题
	TA GetHandle();
	//设置封装内容
	void SetHandle(TA hGdiObj);
	using SGdiObj::SetHandle;

public:	
	//获取位图结构
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
	//DOUBT:应该释放那些由Create()的对象
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

//获取位图结构
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