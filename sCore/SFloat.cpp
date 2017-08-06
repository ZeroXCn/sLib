#include "SFloat.h"


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

SString SFloat::ToHexString(float i, bool bIsUpper)
{
	//TODO:����û�й涨����ĸ�ʽ,�������ʲô����Ҳ��֪��
	//NEED:���Ժ�Ľ�
	if (bIsUpper)return SString::Format(_T("%X"), i);
	else return SString::Format(_T("%x"), i);
}

float SFloat::ParseFloat(SString s)
{
	return s.toFloat();
}

//
SFloat::SFloat(float number) :SNumber(number)
{

}