/*	���������ļ�,ȡ���ļ�·��,ȡ�ñ�����·����һϵ���ļ�����,
*	�����ļ��۴���
*	�ļ�����,ʱ���
*/
#include "../sCore/SString.h"
#ifndef SFILEINFO_H
#define SFILEINFO_H
#include <Windows.h>
namespace SFileInfo
{
	//��ȡ��ǰ�����Ѽ���ģ����ļ�������·��(exe�ļ�·��)
	static SString GetModuleFileName()
	{
		TCHAR exeFullPath[MAX_PATH];
		::GetModuleFileName(NULL, exeFullPath, MAX_PATH);
		
		return exeFullPath;
	}

	static SString GetModuleFilePath()
	{
		return GetModuleFileName();
	}

	static  SString GetModuleExtension()
	{
		SString filepath = GetModuleFilePath();
		SString result = filepath;
		if (!result.empty()){
			result = result.substr(result.find_last_of(TEXT(".")) + 1);
		}
		return TEXT("");
	}
	static  SString GetModuleName()
	{
		SString filepath = GetModuleFilePath();
		SString result = filepath;
		if (!result.empty()){
			result = result.substr(result.find_last_of(TEXT("\\")) + 1, result.find_last_of(TEXT(".")) - result.find_last_of(TEXT("\\")) - 1);
		}
		return TEXT("");
	}
	

	//��ȡ��ǰװ��Ŀ¼
	static SString GetCurrentDirectory()
	{
		TCHAR szPath[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, szPath);
		return szPath;
	}
	
};

#endif