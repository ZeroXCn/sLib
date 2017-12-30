/*	用来分析文件,取得文件路径,取得本程序路径等一系列文件操作,
*	包括文件价创建
*	文件日期,时间等
*/
#include "../sCore/SString.h"
#ifndef SFILEINFO_H
#define SFILEINFO_H
#include <Windows.h>
namespace SFileInfo
{
	//获取当前进程已加载模块的文件的完整路径(exe文件路径)
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
	

	//获取当前装载目录
	static SString GetCurrentDirectory()
	{
		TCHAR szPath[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, szPath);
		return szPath;
	}
	
};

#endif