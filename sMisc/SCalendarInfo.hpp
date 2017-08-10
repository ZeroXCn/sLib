/**
*
*	SCalendarInfo��
*	���ڿ�-�鿴ʱ��,������
*	@author ZEROX
*	@version v1.0
*
*/
#ifndef SCALENDATINFO_H
#define SCALENDATINFO_H
#include <string>

#include <time.h> 
#include <stdio.h>
#include <cstdarg>

#include <windows.h> 


namespace SCalendarInfo{

	std::string GetLocalTime(){
		SYSTEMTIME sys;
		::GetLocalTime(&sys);
		char tmp[64];
		sprintf(tmp, "%02d:%02d:%02d", sys.wHour, sys.wMinute, sys.wSecond);
		return std::string(tmp);
		/*
		printf("%4d/%02d/%02d %02d:%02d:%02d.%03d ����%1d/n",
			sys.wYear,
			sys.wMonth,
			sys.wDay, 
			sys.wHour,
			sys.wMinute,
			sys.wSecond, 
			sys.wMilliseconds, 
			sys.wDayOfWeek);
		*/
	}


	std::string GetLocalDate(){
		time_t t = time(0);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y/%m/%d", ::localtime(&t));
		return std::string(tmp);
		/*
		strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A �����%j�� %z", localtime(&t));
		*/
	}

};

#endif