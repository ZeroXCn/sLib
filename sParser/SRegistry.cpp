#include "SRegistry.h"

LPTSTR SRegistry::DEFAULT_PATH = TEXT("SOFTWARE\\Visual C++\\SLIB\\");
///////////////
SRegistry::SRegistry()
{
}
SRegistry::SRegistry(HKEY hKey, TCHAR *szAddress)
{
	m_hKey = hKey;
	_tcscpy_s(m_szAddress, szAddress);
}

SRegistry::~SRegistry()
{
	Close();
}
//////////////

SString SRegistry::ReadString(HKEY hKey, TCHAR *szAddr, TCHAR *szName)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		TCHAR result[256] = { TEXT('\0') };
		DWORD dwcount = 255;
		::RegQueryValueEx(hOpen, szName, 0, 0, (BYTE*)&result, &dwcount);
		::RegCloseKey(hOpen);
		return SString(result);
	}
	else return TEXT("");
}

bool SRegistry::WriteString(HKEY hKey, TCHAR *szAddr, TCHAR *szName, TCHAR *szValue)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		size_t dwcount = _tcslen(szValue);
		::RegSetValueEx(hOpen, szName, 0, REG_SZ, (BYTE*)szValue, dwcount);
		::RegCloseKey(hOpen);
		return true;
	}
	else return false;
}

unsigned long SRegistry::ReadInt(HKEY hKey, TCHAR *szAddr, TCHAR *szName)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		int result = 0;
		DWORD dwcount = sizeof(int);
		::RegQueryValueEx(hOpen, szName, 0, 0, (BYTE*)&result, &dwcount);
		::RegCloseKey(hOpen);
		return result;
	}
	else return 0;
}

bool SRegistry::WriteInt(HKEY hKey, TCHAR *szAddr, TCHAR *szName, unsigned long szValue)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		DWORD dwcount = sizeof(int);;
		::RegSetValueEx(hOpen, szName, 0, REG_DWORD, (BYTE*)&szValue, dwcount);
		::RegCloseKey(hOpen);
		return true;
	}
	else return false;
}

bool SRegistry::CreatKey(HKEY hKey, TCHAR *szAddr)
{
	HKEY hOpen;
	if (!::RegCreateKey(hKey, szAddr, &hOpen)) { RegCloseKey(hOpen); return true; }
	::RegCloseKey(hOpen);
	return false;
}

bool SRegistry::DeleteKey(HKEY hKey, TCHAR *szAddr)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		::RegDeleteKey(hOpen, szAddr);
		::RegCloseKey(hOpen);
		return true;
	}
	else return false;
}

bool SRegistry::DeleteValue(HKEY hKey, TCHAR *szAddr, TCHAR *szValueName)
{
	HKEY hOpen;
	if (::RegOpenKey(hKey, szAddr, &hOpen) == ERROR_SUCCESS)
	{
		::RegDeleteValue(hOpen, szValueName);
		::RegCloseKey(hOpen);
		return true;
	}
	else return false;
}


bool SRegistry::IsExist(HKEY hKey, TCHAR *szAddr)
{
	HKEY hOpen;
	if (ERROR_SUCCESS == RegOpenKeyEx(hKey, szAddr, 0, KEY_ALL_ACCESS, &hOpen)){
		::RegCloseKey(hOpen);
		return true;
	}
	else return false;
}

///////////////

//´ò¿ª¾ä±ú
bool SRegistry::Open()
{
	if (::RegOpenKey(m_hKey, m_szAddress, m_hOpen) == ERROR_SUCCESS)return true;
	return false;

}
bool SRegistry::Open(HKEY hKey, TCHAR *szAddress)
{
	m_hKey = hKey;
	_tcscpy_s(m_szAddress, szAddress);
	return Open();
}


//¹Ø±Õ¾ä±ú
void SRegistry::Close()
{
	::RegCloseKey(*m_hOpen);
}


///////
//¶ÁÈ¡¼üÄÚÈÝ
SString SRegistry::Read(TCHAR *szName)
{
	return ReadString(szName);
}

//Ð´¼üÄÚÈÝ
bool SRegistry::Write(TCHAR *szName, TCHAR *szValue)
{
	return WriteString(szName, szValue);
}

//¶ÁÈ¡ÕûÐÍ
unsigned long SRegistry::ReadInt(TCHAR *szName)
{
	int result = 0;
	DWORD dwcount = sizeof(int);
	if (::RegQueryValueEx(*m_hOpen, szName, 0, 0, (BYTE*)&result, &dwcount) == ERROR_SUCCESS)return true;
	return false;
}

//Ð´ÕûÐÍ
bool SRegistry::WriteInt(TCHAR *szName, unsigned long szValue)
{
	DWORD dwcount = sizeof(int);;
	if (::RegSetValueEx(*m_hOpen, szName, 0, REG_DWORD, (BYTE*)&szValue, dwcount) == ERROR_SUCCESS)return true;
	return false;
}

//¶ÁÈ¡×Ö·û´®
SString SRegistry::ReadString(TCHAR *szName)
{
	TCHAR result[256] = { TEXT('\0') };
	DWORD dwcount = 255;
	if (::RegQueryValueEx(*m_hOpen, szName, 0, 0, (BYTE*)&result, &dwcount) == ERROR_SUCCESS)return SString(result);
	return TEXT("");
}

//Ð´×Ö·û´®
bool SRegistry::WriteString(TCHAR *szName, TCHAR *szValue)
{
	size_t dwcount = _tcslen(szValue);
	if (::RegSetValueEx(*m_hOpen, szName, 0, REG_SZ, (BYTE*)szValue, dwcount) == ERROR_SUCCESS)return true;
	return false;
}

//Éú³É¼ü
bool SRegistry::CreateKey(TCHAR *szAddress)
{
	return SRegistry::CreatKey(m_hKey, szAddress);
}

//É¾³ý¼ü
bool SRegistry::DeleteKey(TCHAR *szAddress)
{
	if (::RegDeleteKey(*m_hOpen, szAddress) == ERROR_SUCCESS)return true;
	return false;
}

//É¾³ýÖµ
bool SRegistry::DeleteValue(TCHAR *szValueName)
{
	if (::RegDeleteValue(*m_hOpen, szValueName) == ERROR_SUCCESS)return true;
	return false;
}
