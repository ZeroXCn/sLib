/**
* SProfile��
* ��װAPI-GetPrivateProfileString��WritePrivateProfileString
* @author ZeroX
* @version v1.0 04/08/2017
*/
#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SPROFILE_H_
#define _SPROFILE_H_
#include <Windows.h>

class SProfile:public SObject
{
public:
	static DWORD GetValue(
		LPCTSTR lpAppName, //�����ļ���section��
		LPCTSTR lpKeyName, //�����ļ���key��
		LPCTSTR lpDefault, //���ص�Ĭ��ֵ
		LPTSTR lpReturnedString,//���صĽṹָ��
		DWORD nSize,//���صĽṹָ�볤��
		LPCTSTR lpFileName);//�ļ���

	static BOOL SetValue(
		LPCTSTR lpAppName, //�����ļ���section��
		LPCTSTR lpKeyName,//�����ļ���key��
		LPCTSTR lpString,//ֵ
		LPCTSTR lpFileName//�ļ���
		);
private:
	SString m_szlpFileName;
public:
	SProfile(SString szFileName);
public:
	//ȡ�ü�ֵ
	SString GetValue(SString szSection, SString szKey);

	//���ü�ֵ
	void SetValue(SString szSection, SString szKey, SString szValue);
};

#endif