/**
*
*	SCalendar��
*	���ڷ�װ��-�ṩ��ʱ�����
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
/* ������,ʱ��Ĳ���,���� */
#include "SObject.h"
#ifndef _SCALENDAR_H_
#define _SCALENDAR_H_
#include<iostream>

class SCalendar:public SObject
{
public:
	//���캯��
	SCalendar(int year = 1900, int month = 1, int day = 1);

	SCalendar operator+(int count);
	SCalendar operator-(int count);
	SCalendar& operator++();
	SCalendar operator++(int);
	SCalendar& operator--();
	SCalendar operator--(int);
	int operator-(const SCalendar &d);
	SCalendar& operator+=(int day);
	bool operator!=(const SCalendar &d);
	bool operator<(const SCalendar &d);
	bool operator>=(const SCalendar &d);
	bool operator>(const SCalendar &d);
	bool operator==(const SCalendar &d);

public:
	bool IsLeapYear(int year);

	int YearsOfMonth(int year, int month);

	SCalendar ToCorrect(SCalendar &d);

	bool isInvalidDate(int year, int month, int day);

	void Display();

	friend std::istream& operator>>(std::istream& is, SCalendar &d);
	friend std::ostream& operator<<(std::ostream& os, const SCalendar &d);
private:
	int _year;
	int _month;
	int _day;
};


#endif