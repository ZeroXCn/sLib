/**
* SDuration��
* @brief ��ʾʱ���
* @author havesnag
* @link https://github.com/havesnag/date
*/

#if (defined _WIN32) || (defined WIN32) || (defined _WIN64) || (defined WIN64)
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#else
#include <sys/time.h>
#endif // PLATFORM_WINDOWS

#ifndef int64
#define int64 long long
#endif//int64

#include <limits.h>
#include <sstream>
#include <iomanip>
#include <string.h>

#ifdef PLATFORM_WINDOWS

#define localtime_r(t, tm) localtime_s(tm, t)
#define gmtime_r(t, tm) gmtime_s(tm, t)

int gettimeofday(struct timeval *tp, void *tzp);

#endif // PLATFORM_WINDOWS

#include "SObject.h"

#ifndef _SDURATION_H_
#define _SDURATION_H_

#include <time.h>
#include <string>

class SDuration :public SObject
{
public:
	/** @brief ʱ�����ͣ������������������������½� */
	enum Period
	{
		/** @brief ΢�� 1/1000000�� */
		MicroSecond = 5,
		/** @brief ���� 1/1000�� */
		MilliSecond = 6,
		/** @brief �� */
		Second = 11,
		/** @brief �� 60�� */
		Minute = 12,
		/** @brief Сʱ 3600�� */
		Hour = 13,
		/** @brief �� 86400�� */
		Day = 14,
		/** @brief �� 604800�� */
		Week = 15,
		/** @brief �� �������໥ת������Ϊ1:4 */
		Month = 22,
		/** @brief �� */
		Year = 23,
	};

	SDuration(int64 value = 1, Period period = Second);
	SDuration(const SDuration &SDuration);
	~SDuration();

	/** @brief ��¡��ǰ���� */
	SDuration clone() const;

	/** @brief ��ȡ��ֵ */
	inline int64 value() const
	{
		return _value;
	}

	/** @brief ��ȡ���� */
	inline Period period() const
	{
		return _period;
	}

	/** @brief ����ʱ��ε���ֵ������ */
	SDuration & set(int64 value, Period period = Second);
	/** @brief ����ʱ��ε���ֵ */
	SDuration & setValue(int64 value);
	/** @brief ����ʱ��ε����� */
	SDuration & setPeriod(Period period);

	/** @brief �������𣬽��;��ȣ�����ת����ʽ������׼ȷ�ģ�������ת��ʱ��1:4���� */
	SDuration & rase();
	/** @brief ���ͼ����������ȣ�����ת����ʽ������׼ȷ�ģ�������ת��ʱ��1:4���� */
	SDuration & down();
	/** @brief ת����ָ�����͵�ʱ��� */
	SDuration & as(Period period);
	/** @brief ��ȡֵת����ĳ�����ͺ��ֵ */
	int64 valueAs(Period period) const;

	SDuration operator + (const SDuration &other);
	SDuration operator + (int64 value);
	SDuration operator - (const SDuration &other);
	SDuration operator - (int64 value);
	SDuration & operator += (const SDuration &other);
	SDuration & operator += (int64 value);
	SDuration & operator -= (const SDuration &other);
	SDuration & operator -= (int64 value);
	bool operator > (const SDuration & other);
	bool operator >= (const SDuration & other);
	bool operator == (const SDuration & other);
	bool operator != (const SDuration & other);
	bool operator < (const SDuration & other);
	bool operator <= (const SDuration & other);
private:
	int64 _value;
	Period _period;
};

#endif