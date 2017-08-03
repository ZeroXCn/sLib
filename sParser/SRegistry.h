/**
* SRegister类
* 对系统注册表进行操作
* @author ZeroX
* @version v1.0 03/08/2017(27/01/2016)
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#ifndef _SREGISTER_H_
#define _SREGISTER_H_
#include <Windows.h>
class SRegister :public SObject
{

private:

	SString _ReadStr(HKEY hKey, TCHAR *SubKey, TCHAR *Name)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			TCHAR result[256] = { '\0' };
			DWORD dwcount = 255;
			RegQueryValueEx(hOpen, Name, 0, 0, (BYTE*)&result[0], &dwcount);
			RegCloseKey(hOpen);
			return SString(result);
		}
		else return TEXT("");
	}
	bool _WriteStr(HKEY hKey, TCHAR *SubKey, TCHAR *Name, TCHAR *Value)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			size_t dwcount = _tcslen(Value);
			RegSetValueEx(hOpen, Name, 0, REG_SZ, (BYTE*)Value, dwcount);
			RegCloseKey(hOpen);
			return true;
		}
		else return false;
	}
	unsigned long _ReadInt(HKEY hKey, TCHAR *SubKey, TCHAR *Name)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			int result = 0;
			DWORD dwcount = sizeof(int);
			RegQueryValueEx(hOpen, Name, 0, 0, (BYTE*)&result, &dwcount);
			RegCloseKey(hOpen);
			return result;
		}
		else return 0;
	}
	bool _WriteInt(HKEY hKey, TCHAR *SubKey, TCHAR *Name, unsigned long Value)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			DWORD dwcount = sizeof(int);;
			RegSetValueEx(hOpen, Name, 0, REG_DWORD, (BYTE*)&Value, dwcount);
			RegCloseKey(hOpen);
			return true;
		}
		else return false;
	}
	bool _Creat(HKEY hKey, TCHAR *SubKey)
	{
		HKEY hOpen;
		if (!RegCreateKey(hKey, SubKey, &hOpen)) { RegCloseKey(hOpen); return true; }
		RegCloseKey(hOpen);
		return false;
	}
	bool _DeleteKey(HKEY hKey, TCHAR *SubKey)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			RegDeleteValue(hOpen, SubKey);
			RegCloseKey(hOpen);
			return true;
		}
		else return false;
	}
	bool _DeleteValue(HKEY hKey, TCHAR *SubKey, TCHAR *ValueName)
	{
		HKEY hOpen;
		if (RegOpenKey(hKey, SubKey, &hOpen) == ERROR_SUCCESS)
		{
			RegDeleteValue(hOpen, ValueName);
			RegCloseKey(hOpen);
			return true;
		}
		else return false;
	}
	HKEY DefaulthKey;
	SString DefaultSubKey;
public:
	SRegister(HKEY hKey, TCHAR *PjName)
	{
		DefaulthKey = hKey;
		DefaultSubKey = TEXT("SOFTWARE\\Visual C++") + SString(TEXT("\\")) + SString(PjName);
		//	_Creat(DefaulthKey,(TCHAR *)DefaultSubKey.c_str());
	}
	SRegister(TCHAR *PjName)
	{
		DefaulthKey = HKEY_LOCAL_MACHINE;
		DefaultSubKey = TEXT("SOFTWARE\\Visual C++") + SString(TEXT("\\")) + SString(PjName);
		_Creat(DefaulthKey, (TCHAR *)DefaultSubKey.c_str());
	}

	SRegister()
	{
		SString szTitle;
		TCHAR exeFullPath[MAX_PATH];
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);
		szTitle = exeFullPath; szTitle = szTitle.substr(szTitle.find_last_of(TEXT("\\")) + 1, szTitle.find_last_of(TEXT(".")) - szTitle.find_last_of(TEXT("\\")) - 1);
		DefaulthKey = HKEY_LOCAL_MACHINE;
		DefaultSubKey = TEXT("SOFTWARE\\Visual C++") + SString(TEXT("\\")) + szTitle;
		_Creat(DefaulthKey, (TCHAR *)DefaultSubKey.c_str());
	}
	bool Check(HKEY hKey, TCHAR *PjName)
	{
		HKEY hOpen;
		if (ERROR_SUCCESS == RegOpenKeyEx(hKey, (LPCTSTR)PjName, 0, KEY_ALL_ACCESS, &hOpen))
			return true;
		else return false;
	}
	bool Check()
	{
		HKEY hOpen;
		if (ERROR_SUCCESS == RegOpenKeyEx(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), 0, KEY_ALL_ACCESS, &hOpen))
			return true;
		else return false;
	}
	bool Creat()
	{
		_Creat(DefaulthKey, (TCHAR *)DefaultSubKey.c_str());
	}
	SString SRegister::Read(TCHAR *Name){ return _ReadStr(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name); }
	bool SRegister::Write(TCHAR *Name, TCHAR *Value){ return _WriteStr(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name, Value); }
	unsigned long SRegister::ReadInt(TCHAR *Name){ return _ReadInt(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name); }
	bool SRegister::WriteInt(TCHAR *Name, unsigned long Value){ return _WriteInt(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name, Value); }
	SString SRegister::ReadStr(TCHAR *Name){ return _ReadStr(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name); }
	bool SRegister::WriteStr(TCHAR *Name, TCHAR *Value){ return _WriteStr(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name, Value); }
	bool SRegister::DeleteKey(){ _DeleteKey(DefaulthKey, (TCHAR *)DefaultSubKey.c_str()); }
	bool SRegister::DeleteValue(TCHAR *Name){ _DeleteValue(DefaulthKey, (TCHAR *)DefaultSubKey.c_str(), Name); }


	SString SRegister::Read(HKEY hKey, TCHAR *SubKey, TCHAR *Name){ return _ReadStr(hKey, SubKey, Name); }
	bool SRegister::Write(HKEY hKey, TCHAR *SubKey, TCHAR *Name, TCHAR *Value){ return _WriteStr(hKey, SubKey, Name, Value); }
	unsigned long SRegister::ReadInt(HKEY hKey, TCHAR *SubKey, TCHAR *Name){ return _ReadInt(hKey, SubKey, Name); }
	bool SRegister::WriteInt(HKEY hKey, TCHAR *SubKey, TCHAR *Name, unsigned long Value){ return _WriteInt(hKey, SubKey, Name, Value); }
	SString SRegister::ReadStr(HKEY hKey, TCHAR *SubKey, TCHAR *Name){ return _ReadStr(hKey, SubKey, Name); }
	bool SRegister::WriteStr(HKEY hKey, TCHAR *SubKey, TCHAR *Name, TCHAR *Value){ return _WriteStr(hKey, SubKey, Name, Value); }
	bool SRegister::DeleteKey(HKEY hKey, TCHAR *SubKey){ _DeleteKey(hKey, SubKey); }
	bool SRegister::DeleteValue(HKEY hKey, TCHAR *SubKey, TCHAR *Name){ _DeleteValue(hKey, SubKey, Name); }


};
#endif