#include "SDouble.h"

const double SDouble::MAX_VALUE = DBL_MAX;
const double SDouble::MIN_VALUE = DBL_MIN;

const int SDouble::MAX_EXP_VALUE = DBL_MAX_EXP;
const int SDouble::MIN_EXP_VALUE = DBL_MIN_EXP;

const int SIZE=sizeof(double);
//
SDouble::SDouble(double num):
SNumber(num)
{

}

SDouble SDouble::ValueOf(double i)
{
	return SDouble(i);
}
SDouble SDouble::ValueOf(SString s)
{
	return SDouble(s.toDouble());
}


double SDouble::ParseDouble(SString s)
{
	return s.toDouble();
}
