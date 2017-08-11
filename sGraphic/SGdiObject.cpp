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
	//DOUBT:应该释放那些由Create()的对象
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
	//NOTE:如果指定的句柄无效或者它已被选入设备上下文环境，则返回值为零。
	BOOL result= ::DeleteObject(m_hGdiObj);
	m_hGdiObj = NULL;
	return result;
}