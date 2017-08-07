#include "SBoolean.h"
#include "SNumber.cpp"

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

bool SBoolean::ParseBoolean(SString s)
{
	s.toUpper();
	if (s == _T("TRUE"))return true;
	else return false;
}