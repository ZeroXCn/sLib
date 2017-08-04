/**
* SRegister��
* ��ϵͳע�����в���
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
	static LPTSTR DEFAULT_PATH;		//Ĭ��VC��ַ
private:
	PHKEY m_hOpen;			//����һ��ʵ��

	HKEY m_hKey;			//Ҫ�򿪼��ľ��
	TCHAR m_szAddress[MAX_PATH];	//Ҫ�򿪼��ľ���ĵ�ַ
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
	//�򿪾��
	bool Open(HKEY hKey, TCHAR *szAddress);

	//�򿪾��
	bool Open();

	//�رվ��
	void Close();
public:
	//��ȡ������
	SString Read(TCHAR *szName);

	//д������
	bool Write(TCHAR *szName, TCHAR *szValue);

	//��ȡ����
	unsigned long ReadInt(TCHAR *szName);

	//д����
	bool WriteInt(TCHAR *szName, unsigned long uValue);

	//��ȡ�ַ���
	SString ReadString(TCHAR *szName);

	//д�ַ���
	bool WriteString(TCHAR *szName, TCHAR *szValue);

	//���ɼ�
	bool CreateKey(TCHAR *szAddress);

	//ɾ����
	bool DeleteKey(TCHAR *szAddress);

	//ɾ��ֵ
	bool DeleteValue(TCHAR *szValueName);

};
#endif