#include "SProfile.h"

DWORD SProfile::GetValue(
	LPCTSTR lpAppName, //�����ļ���section��
	LPCTSTR lpKeyName, //�����ļ���key��
	LPCTSTR lpDefault, //���ص�Ĭ��ֵ
	LPTSTR lpReturnedString,//���صĽṹָ��
	DWORD nSize,//���صĽṹָ�볤��
	LPCTSTR lpFileName)//�ļ���
{
	return ::GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName);
}

BOOL SProfile::SetValue(
	LPCTSTR lpAppName, //�����ļ���section��
	LPCTSTR lpKeyName,//�����ļ���key��
	LPCTSTR lpString,//ֵ
	LPCTSTR lpFileName//�ļ���
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