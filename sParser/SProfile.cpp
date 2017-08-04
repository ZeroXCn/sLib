#include "SProfile.h"

DWORD SProfile::GetValue(
	LPCTSTR lpAppName, //配置文件的section名
	LPCTSTR lpKeyName, //配置文件的key名
	LPCTSTR lpDefault, //返回的默认值
	LPTSTR lpReturnedString,//返回的结构指针
	DWORD nSize,//返回的结构指针长度
	LPCTSTR lpFileName)//文件名
{
	return ::GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName);
}

BOOL SProfile::SetValue(
	LPCTSTR lpAppName, //配置文件的section名
	LPCTSTR lpKeyName,//配置文件的key名
	LPCTSTR lpString,//值
	LPCTSTR lpFileName//文件名
	)
{
	return ::WritePrivateProfileString(lpAppName, lpKeyName, lpString, lpFileName);
}
/////
SProfile::SProfile(SString szFileName)
{
	m_szlpFileName = szFileName;
}

SString SProfile::GetValue(SString szSection, SString szKey)
{
	TCHAR result[1024];
	::GetPrivateProfileString((LPTSTR)szSection.c_str(), (LPTSTR)szKey.c_str(), TEXT(""), result, sizeof(result), (LPTSTR)m_szlpFileName.c_str());
	return result;
}
void SProfile::SetValue(SString szSection, SString szKey, SString szValue)
{
	::WritePrivateProfileString((LPTSTR)szSection.c_str(), (LPTSTR)szKey.c_str(), (LPTSTR)szValue.c_str(), (LPTSTR)m_szlpFileName.c_str());
}