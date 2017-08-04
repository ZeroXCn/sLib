/**
* SProfile域
* 封装API-GetPrivateProfileString和WritePrivateProfileString
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
		LPCTSTR lpAppName, //配置文件的section名
		LPCTSTR lpKeyName, //配置文件的key名
		LPCTSTR lpDefault, //返回的默认值
		LPTSTR lpReturnedString,//返回的结构指针
		DWORD nSize,//返回的结构指针长度
		LPCTSTR lpFileName);//文件名

	static BOOL SetValue(
		LPCTSTR lpAppName, //配置文件的section名
		LPCTSTR lpKeyName,//配置文件的key名
		LPCTSTR lpString,//值
		LPCTSTR lpFileName//文件名
		);
private:
	SString m_szlpFileName;
public:
	SProfile(SString szFileName);
public:
	//取得键值
	SString GetValue(SString szSection, SString szKey);

	//设置键值
	void SetValue(SString szSection, SString szKey, SString szValue);
};

#endif