#include "SNumber.h"

template<class _T>
SNumber<_T>::SNumber(_T data)
{
	m_data = data;
}

template<class _T>
SString SNumber<_T>::ToString()
{
	return SString(m_data);
}

template<class _T>
SString SNumber<_T>::ToHexString()
{
	return SString::Format(_T("%x"), m_data);
}
template<class _T>
SString SNumber<_T>::ToBinString()
{
	SString ret;
	int len = sizeof(m_data)* 8;
	TCHAR *str = new TCHAR[len + 1];
	str[len] = 0;
	unsigned long intnum = (unsigned long)m_data;								//取得整数部分
	double floatnum = (double)m_data - (unsigned long)m_data;					//取得小数部分

	for (int i = len - 1; i >= 0; i--)
	{
		str[i] = intnum % 2 + _T('0');
		intnum /= 2;
	}

	ret += str;
	ret += _T(".");

	for (int j = 0; j < len; j++)
	{
		str[j] = (int)(floatnum * 2);
		floatnum = floatnum * 2 - (int)str[j];

		str[j] += _T('0');
	}
	ret += str;


	delete[] str;

	return ret;
}

template<class _T>
SString SNumber<_T>::ToDecString()
{
	return SString::Format(_T("%d"), (int)m_data);
}


template<class _T>
int SNumber<_T>::IntValue(){
	return (int)m_data;
}

template<class _T>
double SNumber<_T>::DoubleValue(){
	return (double)m_data;
}

template<class _T>
float SNumber<_T>::FloatValue(){
	return (float)m_data;
}

template<class _T>
TCHAR SNumber<_T>::CharValue(){
	return (TCHAR)m_data;
}

template<class _T>
bool SNumber<_T>::BoolValue(){
	return m_data ? true : false;
}

template<class _T>
long SNumber<_T>::LongValue(){
	return (long)m_data;
}

template<class _T>
bool SNumber<_T>::operator >(SNumber num){
	return m_data > num;
}

template<class _T>
bool SNumber<_T>::operator <(SNumber num){
	return m_data < num;
}

template<class _T>
bool SNumber<_T>::operator ==(SNumber num){
	return m_data == num;
}