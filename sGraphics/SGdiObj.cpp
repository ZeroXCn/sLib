#include "SGdiObj.h"


SGdiObj::SGdiObj(HGDIOBJ hGdiObj)
:m_hGdiObj(hGdiObj)
{
	
}

SGdiObj::~SGdiObj()
{
	//DOUBT:Ӧ���ͷ���Щ��Create()�Ķ���
}

/////
HGDIOBJ SGdiObj::GetHandle()
{
	return m_hGdiObj;
}

void SGdiObj::SetHandle(HGDIOBJ hGdiObj)
{
	m_hGdiObj = hGdiObj;
}


BOOL SGdiObj::Delete()
{
	//NOTE:���ָ���ľ����Ч�������ѱ�ѡ���豸�����Ļ������򷵻�ֵΪ�㡣
	BOOL result = ::DeleteObject(m_hGdiObj);
	m_hGdiObj = NULL;
	return result;
}