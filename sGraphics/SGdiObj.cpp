#include "SGdiObj.h"


SGdiObj::SGdiObj(HGDIOBJ hGdiObj)
:m_hGdiObj(hGdiObj)
{
	
}

SGdiObj::~SGdiObj()
{
	//DOUBT:应该释放那些由Create()的对象
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
	//NOTE:如果指定的句柄无效或者它已被选入设备上下文环境，则返回值为零。
	BOOL result = ::DeleteObject(m_hGdiObj);
	m_hGdiObj = NULL;
	return result;
}