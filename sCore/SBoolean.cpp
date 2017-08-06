#include "SBoolean.h"

SBoolean::SBoolean(bool bl):
SNumber(bl)
{

}

SBoolean SBoolean::ValueOf(bool i)
{
	return SBoolean(i);
}
SBoolean SBoolean::ValueOf(SString s)
{
	return SBoolean(s.toBool());
}
SString SBoolean::ToHexString(bool i, bool bIsUpper)
{
	if (bIsUpper)return SString::Format(_T("%X"), i);
	else return SString::Format(_T("%x"), i);
}
bool SBoolean::ParseBoolean(SString s)
{
	s.toUpper();
	if (s == _T("TRUE"))return true;
	else return false;
}