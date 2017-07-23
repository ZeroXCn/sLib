/**
*
*	SCalendar类
*	日期封装类
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SObject.h"
#ifndef _SCALENDAR_H_
#define _SCALENDAR_H_

class SCalendar :public SObject
{
private:
	int Year;
	int Month;
	int Day;
	int Minute;
	int Second;
	int Milliseconds;
	int DayOfWeek;

public:
	int GetYear();

public:
	virtual void Print();
};

#endif