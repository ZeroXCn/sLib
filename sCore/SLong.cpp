#include "SLong.h"
#include "SNumber.cpp"

const int SLong::MAX_VALUE = LONG_MAX;
const int SLong::MIN_VALUE = LONG_MIN;
const int SLong::SIZE=sizeof(long);

///
SLong SLong::ValueOf(long i)
{
	return SLong(i);
}
SLong SLong::ValueOf(SString s)
{
	return SLong(s.toLong());
}


long SLong::ParseLong(SString s)
{
	return s.toLong();
}

//
SLong::SLong(long number) :SNumber(number)
{

}
