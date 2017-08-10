#include "SDuration.h"
using namespace std;

int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = static_cast<long>(clock);
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}

////
SDuration::SDuration(int64 value, Period period)
{
	_value = value;
	_period = period;
}

SDuration::SDuration(const SDuration &SDuration)
{
	_value = SDuration._value;
	_period = SDuration._period;
}

SDuration::~SDuration()
{
}

SDuration SDuration::clone() const
{
	return SDuration(*this);
}

SDuration & SDuration::set(int64 value, Period period)
{
	_value = value;
	_period = period;
	return *this;
}

SDuration & SDuration::setValue(int64 value)
{
	_value = value;
	return *this;
}

SDuration & SDuration::setPeriod(Period period)
{
	_period = period;
	return *this;
}

SDuration & SDuration::rase()
{
	switch (_period)
	{
	case SDuration::MicroSecond:
		_period = SDuration::MilliSecond;
		_value /= 1000;
		break;
	case SDuration::MilliSecond:
		_period = SDuration::Second;
		_value /= 1000;
		break;
	case SDuration::Second:
		_period = SDuration::Minute;
		_value /= 60;
		break;
	case SDuration::Minute:
		_period = SDuration::Hour;
		_value /= 60;
		break;
	case SDuration::Hour:
		_period = SDuration::Day;
		_value /= 24;
		break;
	case SDuration::Day:
		_period = SDuration::Week;
		_value /= 7;
		break;
	case SDuration::Week:
		_period = SDuration::Month;
		_value /= 4;
		break;
	case SDuration::Month:
		_period = SDuration::Year;
		_value /= 12;
		break;
	default:
		break;
	}
	return *this;
}

SDuration & SDuration::down()
{
	switch (_period)
	{
	case SDuration::MilliSecond:
		_period = SDuration::MicroSecond;
		_value *= 1000;
		break;
	case SDuration::Second:
		_period = SDuration::MilliSecond;
		_value *= 1000;
		break;
	case SDuration::Minute:
		_period = SDuration::Second;
		_value *= 60;
		break;
	case SDuration::Hour:
		_period = SDuration::Minute;
		_value *= 60;
		break;
	case SDuration::Day:
		_period = SDuration::Hour;
		_value *= 24;
		break;
	case SDuration::Week:
		_period = SDuration::Day;
		_value *= 7;
		break;
	case SDuration::Month:
		_period = SDuration::Week;
		_value *= 4;
		break;
	case SDuration::Year:
		_period = SDuration::Month;
		_value *= 12;
		break;
	default:
		break;
	}
	return *this;
}

SDuration & SDuration::as(Period period)
{
	if (_period < period)
	{
		for (; _period < period;)
		{
			rase();
		}
	}
	else if (_period > period)
	{
		for (; _period > period;)
		{
			down();
		}
	}
	return *this;
}

int64 SDuration::valueAs(Period period) const
{
	return clone().as(period).value();
}

SDuration SDuration::operator + (const SDuration &other)
{
	return SDuration(_value + other.valueAs(_period), _period);
}

SDuration SDuration::operator + (int64 value)
{
	return SDuration(_value + value, _period);
}

SDuration SDuration::operator - (const SDuration &other)
{
	return SDuration(_value - other.valueAs(_period), _period);
}

SDuration SDuration::operator - (int64 value)
{
	return SDuration(_value - value, _period);
}

SDuration & SDuration::operator += (const SDuration &other)
{
	_value += other.valueAs(_period);
	return *this;
}

SDuration & SDuration::operator += (int64 value)
{
	_value += value;
	return *this;
}

SDuration & SDuration::operator -= (const SDuration &other)
{
	_value -= other.valueAs(_period);
	return *this;
}

SDuration & SDuration::operator -= (int64 value)
{
	_value -= value;
	return *this;
}

bool SDuration::operator > (const SDuration & other)
{
	return (_period == other._period) ? (_value > other._value) : (_period > other._period);
}

bool SDuration::operator >= (const SDuration & other)
{
	return (_period == other._period) ? (_value >= other._value) : (_period > other._period);
}

bool SDuration::operator == (const SDuration & other)
{
	return (_period == other._period) && (_value == other._value);
}

bool SDuration::operator != (const SDuration & other)
{
	return (_period != other._period) && (_value != other._value);
}

bool SDuration::operator < (const SDuration & other)
{
	return (_period == other._period) ? (_value < other._value) : (_period < other._period);
}

bool SDuration::operator <= (const SDuration & other)
{
	return (_period == other._period) ? (_value <= other._value) : (_period < other._period);
}