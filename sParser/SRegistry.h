/**
* SRegister类
* 对系统注册表进行操作
* @author ZeroX
* @version v1.1 03/08/2017(27/01/2016)
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SREGISTRY_H_
#define _SREGISTRY_H_
#include <Windows.h>
class SRegistry :public SObject
{
private:
	static LPTSTR DEFAULT_PATH;		//默认VC地址
private:
	PHKEY m_hOpen;			//保存一个实例

	HKEY m_hKey;			//要打开键的句柄
	TCHAR m_szAddress[MAX_PATH];	//要打开键的句柄的地址
public:
	static SString ReadString(HKEY hKey, TCHAR *szAddr, TCHAR *szName);

	static bool WriteString(HKEY hKey, TCHAR *szAddr, TCHAR *szName, TCHAR *szValue);

	static unsigned long ReadInt(HKEY hKey, TCHAR *szAddr, TCHAR *szName);

	static bool WriteInt(HKEY hKey, TCHAR *szAddr, TCHAR *szName, unsigned long szValue);

	static bool CreatKey(HKEY hKey, TCHAR *szAddr);

	static bool DeleteKey(HKEY hKey, TCHAR *szAddr);

	static bool DeleteValue(HKEY hKey, TCHAR *szAddr, TCHAR *szValueName);

	static bool IsExist(HKEY hKey, TCHAR *szAddr);
public:
	SRegistry();
	SRegistry(HKEY hKey, TCHAR *szAddress);

	~SRegistry();
public:
	//打开句柄
	bool Open(HKEY hKey, TCHAR *szAddress);

	//打开句柄
	bool Open();

	//关闭句柄
	void Close();
public:
	//读取键内容
	SString Read(TCHAR *szName);

	//写键内容
	bool Write(TCHAR *szName, TCHAR *szValue);

	//读取整型
	unsigned long ReadInt(TCHAR *szName);

	//写整型
	bool WriteInt(TCHAR *szName, unsigned long uValue);

	//读取字符串
	SString ReadString(TCHAR *szName);

	//写字符串
	bool WriteString(TCHAR *szName, TCHAR *szValue);

	//生成键
	bool CreateKey(TCHAR *szAddress);

	//删除键
	bool DeleteKey(TCHAR *szAddress);

	//删除值
	bool DeleteValue(TCHAR *szValueName);

};
#endif