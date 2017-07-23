#include "SException.h"
#include "stdarg.h"
#include "windows.h"

SException::SException(){
	m_nTime = GetTickCount();
	m_strOri = TEXT("Unknown Origin");
	m_strDesc = TEXT("Unknown Error");
}

SException::SException(SString strDesc){
	m_nTime = GetTickCount();
	m_strOri = TEXT("Unknown Origin");
	m_strDesc = strDesc;
}
SException::SException(SString strOri, const TCHAR* pszFormat, ...){
	
	m_nTime = GetTickCount();
	m_strOri = strOri;

	TCHAR str[512];
	va_list args;
	va_start(args, pszFormat);
	_vtprintf_s(pszFormat, args);
	va_end(args);

	m_strDesc = str;
}
int SException::GetTime(){
	return m_nTime;
}
SString SException::GetDesc(){
	return m_strDesc;
}
SString SException::GetOri(){
	return m_strOri;
}

void SException::PrintException(){

	TCHAR str[256];
	wsprintf(str, TEXT("\nTime:%d\nOrigin:%s\nDescription:%s\n\n"), m_nTime, m_strOri, m_strDesc);
	OutputDebugString(str);
}

void SException::Print(){
	SException::PrintException();
}