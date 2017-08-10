#include "SCalendar.h"
using namespace std;

SCalendar::SCalendar(int year = 1900, int month = 1, int day = 1)   //构造
:_year(year)
, _month(month)
, _day(day)
{
	if (!isInvalidDate(_year, _month, _day))
	{
		_year = 1900;
		_month = 1;
		_day = 1;
	}
}

SCalendar SCalendar::operator+(int count)
{
	SCalendar tmp(*this);
	tmp._day += count;
	ToCorrect(tmp);
	return tmp;
}
SCalendar SCalendar::operator-(int count)
{
	SCalendar tmp(*this);
	tmp._day -= count;
	ToCorrect(tmp);
	return tmp;
}

SCalendar& SCalendar::operator++()   //前置++
{
	(*this)++;
	return *this;
}
SCalendar SCalendar::operator++(int)    //后置++
{
	SCalendar tmp(*this);
	(*this) += 1;
	return tmp;
}
SCalendar& SCalendar::operator--()
{
	(*this)--;
	return *this;
}
SCalendar SCalendar::operator--(int)
{
	SCalendar tmp(*this);
	(*this)--;
	return tmp;
}
int SCalendar::operator-(const SCalendar &d)
{
	int flag = 1;
	SCalendar max = *this;
	SCalendar min = d;
	if (*this<d)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int count = 0;
	while (min != max)
	{
		++min;
		count++;
	}
	return count*flag;
}
SCalendar& SCalendar::operator+=(int day)
{
	*this = *this + day;
	return *this;
}
bool SCalendar::operator!=(const SCalendar &d)
{
	return !(*this == d);
}
bool SCalendar::operator<(const SCalendar &d)
{
	return !((*this>d) || (*this == d));
}
bool SCalendar::operator>=(const SCalendar &d)
{
	return !(*this<d);
}
bool SCalendar::operator>(const SCalendar &d)
{
	return (_year > d._year
		|| (_year == d._year && _month > d._month)
		|| (_year == d._year && _month == d._month && _day > d._day));
}
bool SCalendar::operator==(const SCalendar &d)
{
	return ((_year == d._year) && (_month == d._month) && (_day == d._day));
}

bool SCalendar::IsLeapYear(int year)
{
	if (year % 400 || (year % 4 && year % 100))
		return true;
	return false;
}
int SCalendar::YearsOfMonth(int year, int month)
{
	int day;
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	day = days[month];
	if (month == 2)
		day += IsLeapYear(year);
	return day;
}

SCalendar SCalendar::ToCorrect(SCalendar &d)
{
	if (d._day>YearsOfMonth(d._year, d._month))
	{
		while (d._day > YearsOfMonth(d._year, d._month))
		{
			d._day -= YearsOfMonth(d._year, d._month);

			if (d._month == 12)
			{
				d._year++;
				d._month = 1;
			}
			else
			{
				++d._month;
			}
		}
	}
	else
	{
		while (d._day <= 0)
		{
			if (d._month == 1)
			{
				d._year--;
				d._month = 12;
			}
			else
			{
				--d._month;
			}
			d._day += YearsOfMonth(d._year, d._month);
		}
	}
	return d;
}


bool SCalendar::isInvalidDate(int year, int month, int day)
{
	if ((year < 1) || (month<0 || month>12) || (day<0 || day>YearsOfMonth(year, month)))
		return false;
	return true;
}
void SCalendar::Display()
{
	cout << _year << "-" << _month << "-" << _day << endl;
}

istream& operator>>(istream& is, SCalendar& d)
{
	is >> d._year >> d._month >> d._day;
	return is;
}

ostream& operator<<(ostream& os, const SCalendar &d)
{
	cout << d._year << "-" << d._month << "-" << d._day << endl;
	return os;
}