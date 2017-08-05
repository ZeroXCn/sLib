/**
*
*	SString类
*	增强型字符串处理类
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/


#ifndef _SSTRING_H_
#define _SSTRING_H_

#include "SObject.h"

#include <iostream>
#include <tchar.h>
#include <locale.h>

#include <sstream>
#include <string>
#include <cstdarg>
#include <vector>

#include <regex>
using namespace std;

#ifndef _INC_TCHAR

#ifdef _UNICODE
typedef wchar_t TCHAR;
#define _tscanf        wscanf
#define _tprintf        wprintf
#define _stprintf       _swprintf
#define _stprintf_s       _swprintf

#define _tcscat         wcscat
#define _tcschr         wcschr
#define _tcscpy         wcscpy
#define _tcscpy_s         wcscpy
#define _tcscspn        wcscspn
#define _tcslen         wcslen
#define _tcsnlen        wcsnlen
#define _tcsncat        wcsncat
#define _tcsncpy        wcsncpy
#define _tcsstr         wcsstr
#define _tcstok         wcstok
#define _vstprintf      vswprintf
#define _vstprintf_s    vswprintf_s

#define _tcstod     wcstod
#define _tcstof     wcstof
#define _tcstol     wcstol
#define _tcstold    wcstold
#define _tcstoll    wcstoll
#define _tcstoul    wcstoul
#define _tcstoull   wcstoull
#define _tcstoimax  wcstoimax
#define _tcstoumax  wcstoumax

#define _ttof       _wtof
#define _tstof      _wtof
#define _tstol      _wtol
#define _tstoll     _wtoll
#define _tstoi      _wtoi
#define _ttoi       _wtoi
#define _ttol       _wtol
#define _ttoll      _wtoll
#define __T(x)  L##x 
#define _T(x) __T(x)
#else
typedef char TCHAR;
#define _tscanf        scanf
#define _tprintf        printf
#define _stprintf       sprintf
#define _stprintf_s     sprintf

#define _tcscat         strcat
#define _tcschr         strchr
#define _tcscpy         strcpy
#define _tcscpy_s        strcpy
#define _tcscspn        strcspn
#define _tcslen         strlen
#define _tcsnlen        strnlen
#define _tcsncat        strncat
#define _tcsncpy        strncpy
#define _tcsstr         strstr
#define _tcstok         strtok
#define _vstprintf      vsprintf
#define _vstprintf_s    vsprintf_s

#define _tcstod     strtod
#define _tcstof     strtof
#define _tcstol     strtol
#define _tcstold    strtold
#define _tcstoll    strtoll
#define _tcstoul    strtoul
#define _tcstoull   strtoull
#define _tcstoimax  strtoimax
#define _tcstoumax  strtoumax
#define _ttof       atof
#define _tstof      atof
#define _tstol      atol
#define _tstoll     atoll
#define _tstoi      atoi
#define _ttoi       atoi
#define _ttol       atol
#define _ttoll      atoll

#define __T(x)      x
#define _T(x) __T(x)
#endif

#endif

#ifdef _UNICODE
typedef string rtstring;
typedef wstring tstring;
typedef wostream tostream;
typedef wistream tistream;
typedef char RTCHAR;
typedef wregex tregex;
typedef wsmatch tsmatch;
#define tcout wcout
#define tcin win
#define rtcstotcs mbstowcs_s
#define tcstortcs wcstombs_s
#else
typedef wstring rtstring;
typedef string tstring;
typedef ostream tostream;
typedef istream tistream;
typedef wchar_t RTCHAR
typedef regex tregex;
typedef smatch tsmatch;
#define tcout cout
#define tcin cin
#define rtcstotcs wcstombs_s
#define tcstortcs mbstowcs_s
#endif

class SString:
	public SObject,
	public tstring{
public:
	friend tostream& operator <<(tostream&, SString&);
	friend tistream& operator >>(tistream&, SString&);
public:
	static SString Format(const TCHAR *pszFormat, ...);
	static rtstring Parse(tstring OStr);
	static tstring Parse(rtstring OStr);
public:
	//原构造函数
	SString() :tstring(){};
	SString(const tstring &str) :tstring(str){};
	SString(const tstring &str, size_t pos, size_t n = npos) :tstring(str,pos,n){};
	SString(const TCHAR *s, size_t n) :tstring(s,n){};
	SString(const TCHAR *s) :tstring(s){};
	SString(size_t n, char c) :tstring(n,c){};
	template<class InputIterator>SString(InputIterator begin, InputIterator end) :tstring(begin, end){};

	//新增构造函数
	SString(TCHAR ch);
	SString(int x);
	SString(float x);
	SString(double x);
	SString(bool x);


	virtual ~SString();
public:
	SString &arg(SString str);
	SString& trim();
	void split(SString &s, SString &delim, vector<SString> *ret);
	vector<SString> split(SString &s, SString &delim);
	void split(SString &s, tregex expression, vector<SString> *ret);
	vector<SString> split(SString &s, tregex expression);
public:
	float toFloat();
	int toInt();
	double toDouble();
	bool toBool();
	SString toString();
public:
	/*更新对正则表达式的支持*/
	/* 为了防止重载隐藏,不能与父类重载同名 */
	//查找
	size_t indexOf(tregex expression, size_t pos = 0) const;
	size_t indexOf(tregex expression, size_t pos,int *matchLength) const;	//返回匹配长度
	//替换
	SString &replaceAll(tregex expression, SString des);
public:
	//比较
	bool equals(SString str);
	bool equals(SString &str);
	bool equals(tregex expression);
public:
	//返回强制转换后的c_str(),前提是必须确保不被修改
	TCHAR *str();
};

typedef SString String;
#endif