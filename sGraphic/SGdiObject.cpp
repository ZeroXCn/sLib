#include "SGdiObject.h"

SGdiObject::SGdiObject()
{
	m_hGdiObj = NULL;
}
SGdiObject::SGdiObject(HGDIOBJ hGdiObj)
{
	m_hGdiObj = hGdiObj;
}

SGdiObject::~SGdiObject()
{
	//DOUBT:Ӧ���ͷ���Щ��Create()�Ķ���
}

/////
HGDIOBJ SGdiObject::GetHandle()
{
	return m_hGdiObj;
}

void SGdiObject::SetHandle(HGDIOBJ hGdiObj)
{
	m_hGdiObj = hGdiObj;
}

int SGdiObject::GetObject(int cbBuffer, LPVOID lpvObject)
{
	return ::GetObject(m_hGdiObj, cbBuffer, lpvObject);
}

BOOL SGdiObject::Delete()
{
	//NOTE:���ָ���ľ����Ч�������ѱ�ѡ���豸�����Ļ������򷵻�ֵΪ�㡣
	BOOL result= ::DeleteObject(m_hGdiObj);
	m_hGdiObj = NULL;
	return result;
}