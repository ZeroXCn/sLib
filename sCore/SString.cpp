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

	TCHAR str[1024];
	_vstprintf_s(str, 1024, pszFormat, args);

	va_end(args);

	return SString(str);
}

rtstring SString::Parse(tstring OStr)
{
	rtstring result;
	size_t len = OStr.length() + 1;
	size_t converted = 0;
	setlocale(LC_CTYPE, "");     //必须调用此函数
	RTCHAR *RStr;
	RStr = new RTCHAR[len*sizeof(RTCHAR)];
	tcstortcs(&converted, RStr, len, OStr.c_str(), _TRUNCATE);
	result = RStr;
	delete[] RStr;
	return result;

}

tstring SString::Parse(rtstring OStr)
{
	tstring result;
	size_t len = OStr.length() + 1;
	size_t converted = 0;
	setlocale(LC_CTYPE, "");     //必须调用此函数
	TCHAR *RStr;
	RStr = new TCHAR[len*sizeof(TCHAR)];
	rtcstotcs(&converted, RStr, len, OStr.c_str(), _TRUNCATE);
	result = RStr;
	delete[] RStr;
	return result;
}


////
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

SString &SString::arg(SString str)
{
	//仿qt的string,这里采用查找,替换的方法
	//TODO:有待改进(04/08/2017)
	SString result;
	bool flag = false;
	int size = tstring::size();
	for (int i = 0; i < size; i++)
	{
		if ((*this)[i] != _T('%'))result += (*this)[i];
		else{
			if (!flag){
				TCHAR next = tstring::at(i + 1);
				try{
					switch (next){
						case _T('d'):
						case _T('s'):
						case _T('f'):
							result += str;
							flag = true;
							i++;
							break;
							/*
						case _T('%'):
							result += (*this)[i];
							i++;
							break;
							*/
						default:
							result += (*this)[i];
							break;
					}


				}
				catch (...){}
			}
			else{ result += (*this)[i]; }
		}
	}


	*this = result;
	return *this;
}

SString &SString::trim()
{
	SString &s = *this;
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
	while (index != tstring::npos)
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

void SString::split(SString &s, tregex expression, vector<SString> *ret)
{
	tsmatch what;
	tstring::const_iterator start = tstring::begin();
	tstring::const_iterator end = tstring::end();

	size_t last=0;
	size_t index=0;
	while (regex_search(start, end, what, expression))
	{
		index = (what[0].second - what[0].length() - tstring::begin());

		ret->push_back(s.substr(last, index - last));

		last = (what[0].second - tstring::begin());
		start = what[0].second;
	}
	if (last != 0)
	{
		ret->push_back(s.substr(last));
	}
	
}

vector<SString> SString::split(SString &s, tregex expression)
{
	vector<SString> ret;
	split(s, expression, &ret);
	return ret;
}


SString SString::toString()
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
////

size_t SString::indexOf(tregex expression, size_t pos , int *matchLength) const
{
	tsmatch what;
	tstring::const_iterator start = tstring::begin();
	tstring::const_iterator end = tstring::end();
	std::advance(start, pos);		//迭代器偏移
	if (regex_search(start, end, what, expression)){
		if (matchLength)*matchLength = what[0].length();
		return (what[0].second - what[0].length() - tstring::begin());	//second指向下一个位置
	}
	else
		return tstring::npos;

}

size_t SString::indexOf(tregex expression, size_t pos) const
{
	return indexOf(expression, pos, NULL);
}

SString &SString::replaceAll(tregex expression, SString des)
{
	regex_replace(*this, expression, des);
	return *this;
}


////
bool SString::equals(SString str)
{
	return (*this == str);
}
bool SString::equals(SString &str)
{
	return (*this == str);
}
bool SString::equals(tregex expression)
{
	return regex_match(*this, expression);
}

TCHAR *SString::str()
{
	return (TCHAR *)tstring::c_str();
}

////
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
