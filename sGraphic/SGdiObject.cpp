#include "SGdiObject.h"

SGdiObject::SGdiObject()
{
	m_hGdiObj = NULL;
}
SGdiObject::SGdiObject(HGDIOBJ hGdiObj)
{
	m_hGdiObj = hGdiObj;
}

HGDIOBJ SGdiObject::Get()
{
	return m_hGdiObj;
}

int SGdiObject::GetObject(int cbBuffer, LPVOID lpvObject)
{
	return ::GetObject(m_hGdiObj, cbBuffer, lpvObject);
}

BOOL SGdiObject::Delete()
{
	BOOL result= ::DeleteObject(m_hGdiObj);
	m_hGdiObj = NULL;
	return result;
}