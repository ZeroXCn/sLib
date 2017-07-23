/*************************************
* 窗口类头文件 SString.h
* 增强型String类,支持宽字
* @author ZeroX
* @version v1.0 21/07/2017
*************************************/
#include "SString.h"

SString SString::Format(const TCHAR *pszFormat, ...)
{
	va_list args;
	va_start(args, pszFormat);

	TCHAR str[256];
	_vstprintf_s(str, 256,pszFormat, args);

	va_end(args);

	return SString(str);
}


SString::SString(TCHAR ch)
{
	*this += ch;
}

SString::SString(int x)
{
	TCHAR str[10];
	_stprintf_s(str, _T("%d"), x);
	*this = str;
}
SString::SString(float x)
{
	TCHAR str[10];
	_stprintf_s(str, _T("%f"), x);
	*this = str;
}
SString::SString(double x)
{
	TCHAR str[10];
	_stprintf_s(str, _T("%lf"), x);
	*this = str;
}

SString::SString(bool x)
{
	TCHAR str[6];
	if (x) _tcscpy_s(str, _T("true"));
	else _tcscpy_s(str, _T("false"));
	*this = str;
}

SString::~SString()
{

}
///

SString &SString::arg(SString &str)
{
	//仿qt的string
	return *this;
}

SString &SString::trim(SString &s)
{
	if (s.empty())
		return s;

	s.erase(0, s.find_first_not_of(_T(" ")));
	s.erase(s.find_last_not_of(_T(" ")) + 1);
	return s;
}

void SString::split(SString &s, SString &delim, vector<SString> *ret)
{
	size_t last = 0;
	size_t index = s.find_first_of(delim, last);
	while (index != SString::npos)
	{
		ret->push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(delim, last);
	}
	if (index - last>0)
	{
		ret->push_back(s.substr(last, index - last));
	}
}

vector<SString> SString::split(SString &s, SString &delim)
{
	vector<SString> ret;
	split(s, delim, &ret);
	return ret;
}

SString SString::ToString()
{
	return *this;
}
//
float SString::toFloat()
{
	float result = _tcstof(c_str(),NULL);
	return result;
}
int SString::toInt()
{
	int result = _ttoi(c_str());
	return result;
}
double SString::toDouble()
{
	double result = _tcstod(c_str(), NULL);
	return result;
}

tostream &operator << (tostream& os, SString &str)
{
	os <<(tstring&) str << endl;
	return os;
}

tistream &operator >> (tistream& is, SString &str)
{
	is >> (tstring&)str;
	return is;
}
