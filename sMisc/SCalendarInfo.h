#ifndef SCALENDATINFO_H
#define SCALENDATINFO_H
#include <string>

#include <time.h> 
#include <stdio.h>

#include <windows.h> 

using namespace std;


namespace SCalendarInfo{

	string GetLocalTime(){
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		char tmp[64];
		sprintf(tmp, "%02d:%02d:%02d", sys.wHour, sys.wMinute, sys.wSecond);
		return string(tmp);
		/*
		printf("%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d/n",
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

	string GetLocalTime(){
	}


	string GetLocalDate(){
		time_t t = time(0);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y/%m/%d", localtime(&t));
		return string(tmp);
		/*
		strftime(tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z", localtime(&t));
		*/
	}

};

#endif