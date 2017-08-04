/*************************************
* 窗口类头文件 SString.h
* 增强型String类,支持宽字
* @author ZeroX
* @version v1.0 21/07/2017
*************************************/
#include "SString.h"

wstring SString::StringToWstring(const string str)
{
	unsigned len = str.size() * 2;// 预留字节数
	size_t converted = 0;
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs_s(&converted, p, len, str.c_str(), _TRUNCATE);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}
string SString::WStringToString(const wstring str)
{
	unsigned len = str.size() * 4;
	size_t converted = 0;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	wcstombs_s(&converted, p, len, str.c_str(), _TRUNCATE);
	std::string str1(p);
	delete[] p;
	return str1;
}

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
	RTCHAR *RStr;
	RStr = new RTCHAR(len*sizeof(RTCHAR));
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
	TCHAR *RStr;
	RStr = new TCHAR(len*sizeof(TCHAR));
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
	int size = this->size();
	for (int i = 0; i < size; i++)
	{
		if ((*this)[i] != _T('%'))result += (*this)[i];
		else{
			if (!flag){
				TCHAR next = this->at(i + 1);
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
