#include "STime.h"

using namespace std;
STime::STime()
{
	gettimeofday(&_tv, NULL);
}

STime::STime(time_t stamp)
{
	set(stamp);
}

STime::STime(const SDate &date)
{
	set(date.stamp());
}

STime::STime(const STime &time)
{
	_tv = time._tv;
}

STime::~STime()
{
}

STime STime::clone() const
{
	return STime(*this);
}

SDate STime::toDate() const
{
	return SDate(*this);
}

SDate STime::utcDate() const
{
	return SDate(stamp(), true);
}


time_t STime::utcStamp() const
{
	return _tv.tv_sec - SDate::localTimeZoneOffset();
}

STime & STime::set(time_t seconds, long microSeconds)
{
	_tv.tv_sec = static_cast<long>(seconds);
	if (microSeconds < 0)
	{
		microSeconds = 0;
	}
	else if (microSeconds >= 1000000)
	{
		microSeconds = 1000000 - 1;
	}
	return *this;
}

STime & STime::setSeconds(time_t seconds)
{
	_tv.tv_sec = static_cast<long>(seconds);
	return *this;
}

STime & STime::setMicroSeconds(long microSeconds)
{
	if (microSeconds < 0)
	{
		microSeconds = 0;
	}
	else if (microSeconds >= 1000000)
	{
		microSeconds = 1000000 - 1;
	}

	_tv.tv_usec = microSeconds;
	return *this;
}

STime & STime::zeroSet(SDuration::Period period)
{
	switch (period)
	{
	case SDuration::MilliSecond:
		_tv.tv_usec = _tv.tv_usec * 1000 * 1000;
		break;
	case SDuration::Second:
		_tv.tv_usec = 0;
		break;
	case SDuration::Minute:
		_tv.tv_sec = _tv.tv_sec / 60 * 60;
		_tv.tv_usec = 0;
		break;
	case SDuration::Hour:
		_tv.tv_sec = _tv.tv_sec / 3600 * 3600;
		_tv.tv_usec = 0;
		break;
	case SDuration::Day:
	case SDuration::Week:
	case SDuration::Month:
	case SDuration::Year:
		setSeconds(toDate().zeroSet(period).stamp());
		break;
	default:
		break;
	}

	return *this;
}

STime & STime::add(int64 value, SDuration::Period period)
{
	//TODO:关于类型强转可能引发精度问题
	switch (period)
	{
	case SDuration::MicroSecond:
		addMicroSecond((int)value);
		break;
	case SDuration::MilliSecond:
		addMilliSecond((int)value);
		break;
	case SDuration::Second:
		addSecond((int)value);
		break;
	case SDuration::Minute:
		addMinute((int)value);
		break;
	case SDuration::Hour:
		addHour((int)value);
		break;
	case SDuration::Day:
		addDay((int)value);
		break;
	case SDuration::Week:
		addWeek((int)value);
		break;
	case SDuration::Month:
	case SDuration::Year:
		setSeconds(toDate().add(value, period).stamp());
		break;
	default:
		break;
	}

	return *this;
}

STime & STime::add(const SDuration & duration)
{
	return add(duration.value(), duration.period());
}

STime & STime::addWeek(int value)
{
	_tv.tv_sec += value * 3600 * 24 * 7;
	return *this;
}

STime & STime::addDay(int value)
{
	_tv.tv_sec += value * 3600 * 24;
	return *this;
}

STime & STime::addHour(int value)
{
	_tv.tv_sec += value * 3600;
	return *this;
}

STime & STime::addMinute(int value)
{
	_tv.tv_sec += value * 60;
	return *this;
}

STime & STime::addSecond(int value)
{
	_tv.tv_sec += value;
	return *this;
}

STime & STime::addMilliSecond(int value)
{
	_tv.tv_usec += value * 1000;
	_tv.tv_sec += _tv.tv_usec / 1000000;
	_tv.tv_usec %= 1000000;
	if (_tv.tv_usec < 0)
	{
		_tv.tv_sec -= 1;
		_tv.tv_usec += 1000000;
	}
	return *this;
}

STime & STime::addMicroSecond(int value)
{
	_tv.tv_usec += value;
	_tv.tv_sec += _tv.tv_usec / 1000000;
	_tv.tv_usec %= 1000000;
	if (_tv.tv_usec < 0)
	{
		_tv.tv_sec -= 1;
		_tv.tv_usec += 1000000;
	}
	return *this;
}

int64 STime::diff(const STime & other, SDuration::Period period)
{
	switch (period)
	{
	case SDuration::MicroSecond:
		return static_cast<int64>(microStamp() - other.microStamp());
	case SDuration::MilliSecond:
		return static_cast<int64>(milliStamp() - other.milliStamp());
	case SDuration::Second:
		return static_cast<int64>(stamp() - other.stamp());
	case SDuration::Minute:
		return static_cast<int64>(stamp() / 60 - other.stamp() / 60);
	case SDuration::Hour:
		return static_cast<int64>(stamp() / 3600 - other.stamp() / 3600);
	case SDuration::Day:
		return static_cast<int64>(getUTCFullDays() - other.getUTCFullDays());
	case SDuration::Week:
		return static_cast<int64>(getUTCFullWeeks() - other.getUTCFullWeeks());
	case SDuration::Month:
	case SDuration::Year:
		return toDate().diff(other.toDate(), period);
	default:
		return 0;
	}
}

int64 STime::getUTCFullMicroSeconds() const
{
	return microStamp() + SDate::localTimeZoneOffset() * 1000000;
}

int64 STime::getUTCFullMilliSeconds() const
{
	return milliStamp() + SDate::localTimeZoneOffset() * 1000;
}

time_t STime::getUTCFullSeconds() const
{
	return seconds();
}

int STime::getUTCFullMinutes() const
{
	return static_cast<int>((utcStamp() / 60));
}

int STime::getUTCFullHours() const
{
	return static_cast<int>((utcStamp() / 3600));
}

int STime::getUTCFullDays() const
{
	return static_cast<int>((utcStamp() / 86400));
}

int STime::getUTCFullWeeks() const
{
	int days = getUTCFullDays() + 4;
	int weeks = (days - 1) / 7;
	int weekDay = days % 7;
	if (weekDay < 0) {
		weeks -= 1;
	}
	return weeks;
}

STime STime::operator + (const SDuration & duration)
{
	return clone().add(duration.value(), duration.period());
}

STime STime::operator - (const SDuration & duration)
{
	return clone().add(-duration.value(), duration.period());
}

SDuration STime::operator - (const STime & other)
{
	return SDuration(static_cast<int64>(stamp() - other.stamp()));
}

STime & STime::operator += (const SDuration & duration)
{
	return add(duration.value(), duration.period());
}

STime & STime::operator -= (const SDuration & duration)
{
	return add(-duration.value(), duration.period());
}

bool STime::operator < (const STime & other)
{
	if (_tv.tv_sec != other._tv.tv_sec)
	{
		return _tv.tv_sec < other._tv.tv_sec;
	}

	return _tv.tv_usec < other._tv.tv_usec;

}

bool STime::operator = (const STime & other)
{
	return (_tv.tv_sec == other._tv.tv_sec) && (_tv.tv_usec == other._tv.tv_usec);
}
