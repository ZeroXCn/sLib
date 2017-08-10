#include "SDate.h"

using namespace std;
time_t SDate::localTimeZoneOffset()
{
	return localTimeZone() * -3600;
}

int SDate::localTimeZone()
{
	static int tz = SDate(0).hour();
	return tz;
}

bool SDate::isLeapYear(int year)
{
	return (year % 4 == 0 && ((year % 400 == 0) || (year % 100 != 0)));
}

int SDate::yearMonthDays(int year, int month)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		//Need to consider a leap year in February
		return isLeapYear(year) ? 29 : 28;
	default:
		return 0;
	}
}

SDate::SDate()
{
	_isUTC = false;
	_set(time(NULL));
}

SDate::SDate(time_t stamp, bool utc)
{
	_isUTC = utc;
	_set(stamp);
}

SDate::SDate(const STime &time)
{
	_isUTC = false;
	_set(time.stamp());
}

SDate::SDate(const SDate &other)
{
	_tm = other._tm;
	_isUTC = other._isUTC;
}

SDate::SDate(int year, int month, int day, int hour, int minute, int second)
{
	_isUTC = false;
	_set(time(NULL));

	_tm.tm_year = year - 1900;
	_tm.tm_mon = month - 1;
	_tm.tm_mday = day;
	_tm.tm_hour = hour;
	_tm.tm_min = minute;
	_tm.tm_sec = second;

	_update();
}

SDate::~SDate()
{
}

SDate SDate::clone() const
{
	return SDate(*this);
}

STime SDate::toTime() const
{
	return STime(*this);
}

std::string SDate::toString() const
{
	std::ostringstream oss;
	oss << setfill('0') << setw(4) << year()
		<< "-" << setw(2) << month()
		<< "-" << setw(2) << day()
		<< " " << setw(2) << hour()
		<< ":" << setw(2) << minute()
		<< ":" << setw(2) << second();
	return oss.str();
}

std::string SDate::format(const char * fmt) const
{
	char buf[256] = { 0 };
	if (0 == strftime(buf, 63, fmt, &_tm)) {
		buf[0] = '\0';
	}
	return std::string(buf);
}

time_t SDate::stamp() const
{
#ifdef PLATFORM_WINDOWS
	if (_tm.tm_year > 70) // > 1970
	{
		return mktime(const_cast<struct tm *>(&_tm));
	}
	else if (70 == _tm.tm_year)
	{
		return (0 != _tm.tm_mon) ?
			mktime(const_cast<struct tm *>(&_tm)) :
			(_tm.tm_mday - 1) * 86400 + _tm.tm_hour * 3600 + _tm.tm_min * 60 + _tm.tm_sec + SDate::localTimeZoneOffset();
	}
	else
	{
		return SDate::localTimeZoneOffset();
	}
#else
	return mktime(const_cast<struct tm *>(&_tm));
#endif // PLATFORM_WINDOWS
}

time_t SDate::utcStamp() const
{
	return stamp() - SDate::localTimeZoneOffset();
}

int SDate::timeZone() const
{
#ifdef PLATFORM_WINDOWS
	return _isUTC ? 0 : SDate::localTimeZone();
#else
# ifdef __USE_BSD
	return static_cast<int>(_tm.tm_gmtoff / 3600);
# else
	return static_cast<int>(_tm.__tm_gmtoff / 3600);
# endif//__USE_BSD
#endif // PLATFORM_WINDOWS
}

time_t SDate::timeZoneOffset() const
{
	return static_cast<time_t>(-3600 * timeZone());
}

SDate & SDate::setDate(int year, int month, int day)
{
	_tm.tm_year = year - 1900;

	month = (month - 1) % 12;
	_tm.tm_mon = (month > 0) ? month : 0;

	day = day % 32;
	_tm.tm_mon = (day > 1) ? day : 1;

	_update();
	return *this;
}

SDate & SDate::setYear(int year)
{
	_tm.tm_year = year - 1900;
	_update();
	return *this;
}

SDate & SDate::setMonth(int month)
{
	month = (month - 1) % 12;
	_tm.tm_mon = (month > 0) ? month : 0;
	_update();
	return *this;
}

SDate & SDate::setDay(int day)
{
	day = day % 32;
	_tm.tm_mon = (day > 1) ? day : 1;
	_update();
	return *this;
}

SDate & SDate::setHour(int hour)
{
	hour = hour % 24;
	_tm.tm_hour = (hour > 0) ? hour : 0;
	return *this;
}

SDate & SDate::setMinute(int minute)
{
	minute = minute % 60;
	_tm.tm_min = (minute > 0) ? minute : 0;
	return *this;
}

SDate & SDate::setSecond(int second)
{
	second = second % 60;
	_tm.tm_sec = (second > 0) ? second : 0;
	return *this;
}

SDate & SDate::zeroSet(SDuration::Period period)
{
	switch (period)
	{
	case SDuration::Minute:
		_tm.tm_sec = 0;
		break;
	case SDuration::Hour:
		_tm.tm_min = 0;
		_tm.tm_sec = 0;
		break;
	case SDuration::Day:
		_tm.tm_hour = 0;
		_tm.tm_min = 0;
		_tm.tm_sec = 0;
		break;
	case SDuration::Week:
		_set(toTime().zeroSet(period).stamp());
		break;
	case SDuration::Month:
		_tm.tm_mday = 1;
		_tm.tm_hour = 0;
		_tm.tm_min = 0;
		_tm.tm_sec = 0;
		break;
	case SDuration::Year:
		_tm.tm_mon = 0;
		_tm.tm_mday = 1;
		_tm.tm_hour = 0;
		_tm.tm_min = 0;
		_tm.tm_sec = 0;
		break;
	default:
		break;
	}

	return *this;
}

SDate & SDate::add(int64 value, SDuration::Period period)
{
	switch (period)
	{
	case SDuration::Second:
	case SDuration::Minute:
	case SDuration::Hour:
	case SDuration::Day:
	case SDuration::Week:
		_set(toTime().add(value, period).stamp());
		break;
	case SDuration::Month:
		addMonth((int)value);
		break;
	case SDuration::Year:
		addMonth((int)value);
		break;
	default:
		break;
	}

	return *this;
}

SDate & SDate::add(const SDuration & duration)
{
	return add(duration.value(), duration.period());
}

SDate & SDate::addYear(int value)
{
	_tm.tm_year += value;
	if (_tm.tm_year < 0)
	{
		_tm.tm_year = 0;
	}

	int monthDays = SDate::yearMonthDays(year(), month());
	if (_tm.tm_mday > monthDays)
	{
		_tm.tm_mday = monthDays;
	}

	return *this;
}

SDate & SDate::addMonth(int value)
{
	_tm.tm_mon += value;
	_tm.tm_year += _tm.tm_mon / 12;
	_tm.tm_mon = _tm.tm_mon % 12;
	if (_tm.tm_mon < 0)
	{
		_tm.tm_year -= 1;
		_tm.tm_mon += 12;
	}

	int monthDays = SDate::yearMonthDays(year(), month());
	if (_tm.tm_mday > monthDays)
	{
		_tm.tm_mday = monthDays;
	}

	return *this;
}

int64 SDate::diff(const SDate & other, SDuration::Period period)
{
	switch (period)
	{
	case SDuration::MicroSecond:
		return static_cast<int64>((stamp() - other.stamp()) * 1000000);
	case SDuration::MilliSecond:
		return static_cast<int64>((stamp() - other.stamp()) * 1000);
	case SDuration::Second:
		return static_cast<int64>(stamp() - other.stamp());
	case SDuration::Minute:
		return static_cast<int64>(stamp() / 60 - other.stamp() / 60);
	case SDuration::Hour:
		return static_cast<int64>(stamp() / 3600 - other.stamp() / 3600);
	case SDuration::Day:
	case SDuration::Week:
		return toTime().diff(other.toTime(), period);
	case SDuration::Month:
		return year() * 12 + month() - other.year() * 12 - other.month();
	case SDuration::Year:
		return year() - other.year();
	default:
		return 0;
	}
}

int SDate::getYearDay() const
{
	return _tm.tm_yday + 1;
}

int SDate::getUTCFullMonths() const
{
	return (year() - 1970) * 12 + month() - 1;
}

int SDate::getUTCFullYears() const
{
	return year() - 1970;
}

bool SDate::isLeapYear() const
{
	return SDate::isLeapYear(year());
}

bool SDate::isLastDayOfMonth() const
{
	return day() >= SDate::yearMonthDays(year(), month());
}

SDate SDate::operator + (const SDuration & duration)
{
	return clone().add(duration.value(), duration.period());
}

SDate SDate::operator - (const SDuration & duration)
{
	return clone().add(-duration.value(), duration.period());
}

SDuration SDate::operator - (const SDate & other)
{
	return SDuration(static_cast<int64>(stamp() - other.stamp()));
}

SDate & SDate::operator += (const SDuration & duration)
{
	return add(duration.value(), duration.period());
}

SDate & SDate::operator -= (const SDuration & duration)
{
	return add(-duration.value(), duration.period());
}

bool SDate::operator < (const SDate & other)
{
	if (_tm.tm_year != other._tm.tm_year)
	{
		return _tm.tm_year < other._tm.tm_year;
	}

	if (_tm.tm_mon != other._tm.tm_mon)
	{
		return _tm.tm_mon < other._tm.tm_mon;
	}

	if (_tm.tm_mday != other._tm.tm_mday)
	{
		return _tm.tm_mday < other._tm.tm_mday;
	}

	if (_tm.tm_hour != other._tm.tm_hour)
	{
		return _tm.tm_hour < other._tm.tm_hour;
	}

	if (_tm.tm_min != other._tm.tm_min)
	{
		return _tm.tm_min < other._tm.tm_min;
	}

	return _tm.tm_sec < other._tm.tm_sec;
}

bool SDate::operator = (const SDate & other)
{
	return (_tm.tm_year == other._tm.tm_year) &&
		(_tm.tm_mon == other._tm.tm_mon) &&
		(_tm.tm_mday == other._tm.tm_mday) &&
		(_tm.tm_hour == other._tm.tm_hour) &&
		(_tm.tm_min == other._tm.tm_min) &&
		(_tm.tm_sec == other._tm.tm_sec);
}

void SDate::_set(time_t stamp)
{
#ifdef PLATFORM_WINDOWS
	if (stamp >= 0)
	{
		_isUTC ? gmtime_r(&stamp, &_tm) : localtime_r(&stamp, &_tm);
	}
	else
	{
		if (_isUTC)
		{
			stamp = 0;
			gmtime_r(&stamp, &_tm);
		}
		else
		{
			time_t zoneOffset = SDate::timeZoneOffset();
			if (zoneOffset >= 0)
			{
				stamp = 0;
				localtime_r(&stamp, &_tm);
			}
			else
			{
				stamp = (stamp < zoneOffset) ? 0 : stamp - zoneOffset;
				localtime_r(&stamp, &_tm);
				int hour = static_cast<int>(zoneOffset / 3600);
				_tm.tm_hour += hour;
			}
		}
	}
#else
	_isUTC ? gmtime_r(&stamp, &_tm) : localtime_r(&stamp, &_tm);
#endif // PLATFORM_WINDOWS
}

void SDate::_update()
{
	int monthDays = SDate::yearMonthDays(year(), month());
	if (_tm.tm_mday > monthDays)
	{
		_tm.tm_mday = monthDays;
	}

	_set(stamp());
}