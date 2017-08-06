#include "SDebug.h"

void SDebug::Write(const TCHAR* pszFormat, ...)
{
	TCHAR str[256];
	va_list args;
	va_start(args, pszFormat);
	_vstprintf_s(str, pszFormat, args);
	OutputDebugString(str);
	va_end(args);

}

void SDebug::Write(SString str)
{
	OutputDebugString(str.c_str());
}

void SDebug::WriteLine(const TCHAR* pszFormat, ...)
{
	TCHAR str[256];
	va_list args;
	va_start(args, pszFormat);
	_vstprintf_s(str, pszFormat, args);
	OutputDebugString(str);
	OutputDebugString(TEXT("\n"));
	va_end(args);
}
void SDebug::WriteLine(SString str)
{
	Write(str);
	Write(TEXT("\n"));
}
