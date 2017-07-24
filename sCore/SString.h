/**
*
*	SString��
*	��ǿ���ַ���������
*	@author ZeroX
*	@version v1.0 22/07/2017(22/07/2017)
*
*/


#ifndef _SSTRING_H_
#define _SSTRING_H_

#include "SObject.h"

#include <iostream>
#include <tchar.h>

#include <sstream>
#include <string>
#include <cstdarg>
#include <vector>
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
typedef wstring tstring;
typedef wostream tostream;
typedef wistream tistream;
#define tcout wcout
#define tcin win
#else
typedef string tstring;
typedef ostream tostream;
typedef istream tistream;
#define tcout cout
#define tcin cin
#endif

class SString:
	public SObject,
	public tstring{
public:
	friend tostream& operator <<(tostream&, SString&);
	friend tistream& operator >>(tistream&, SString&);
public:
	static SString Format(const TCHAR *pszFormat, ...);
public:
	//ԭ���캯��
	SString() :tstring(){};
	SString(const tstring &str) :tstring(str){};
	SString(const tstring &str, size_t pos, size_t n = npos) :tstring(str,pos,n){};
	SString(const TCHAR *s, size_t n) :tstring(s,n){};
	SString(const TCHAR *s) :tstring(s){};
	SString(size_t n, char c) :tstring(n,c){};
	template<class InputIterator>SString(InputIterator begin, InputIterator end) :tstring(begin, end){};

	//�������캯��
	SString(TCHAR ch);
	SString(int x);
	SString(float x);
	SString(double x);
	SString(bool x);

	virtual ~SString();
public:
	SString &arg(SString &str);
	SString& trim(SString &s);
	void split(SString &s, SString &delim, vector<SString> *ret);
	vector<SString> split(SString &s, SString &delim);

	SString ToString();
public:
	float toFloat();
	int toInt();
	double toDouble();
	bool toBool();
};

typedef SString String;
#endif