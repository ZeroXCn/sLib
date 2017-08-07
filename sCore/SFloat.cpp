#include "SFloat.h"
#include "SNumber.cpp"

const float SFloat::MAX_VALUE = FLT_MAX;
const float SFloat::MIN_VALUE = FLT_MIN;
const int SFloat::MAX_EXP_VALUE = FLT_MAX_EXP;
const int SFloat::MIN_EXP_VALUE = FLT_MIN_EXP;
const int SFloat::SIZE = sizeof(float);

///
SFloat SFloat::ValueOf(float i)
{
	return SFloat(i);
}
SFloat SFloat::ValueOf(SString s)
{
	return SFloat(s.toFloat());
}


float SFloat::ParseFloat(SString s)
{
	return s.toFloat();
}

//
SFloat::SFloat(float number) :SNumber(number)
{

}
