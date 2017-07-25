#include "SGdiObject.h"

SGdiObject::SGdiObject()
{
	m_hGdiObj = NULL;
}
SGdiObject::SGdiObject(HGDIOBJ hGdiObj)
{
	m_hGdiObj = hGdiObj;
}

HGDIOBJ SGdiObject::GetObject()
{
	return m_hGdiObj;
}