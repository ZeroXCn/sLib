/**
* STime��
* @brief ʱ����
* @details ��ȷ��΢�룬����Date�໥ת����ת��ΪDate����ʧ���ȵ���
* @see Date
* @author havesnag
* @link https://github.com/havesnag/date
*/
#include "SObject.h"
#include "SDuration.h"

#ifndef _STIME_H_
#define _STIME_H_
#include "SDate.h"

class STime :public SObject
{
public:
	STime();
	/** @brief ��ʱ������� */
	STime(time_t stamp);
	/** @brief ��Date������ */
	STime(const SDate &date);
	/** @brief ��STime������ */
	STime(const STime &time);
	~STime();

	/** @brief ��¡��ǰ���� */
	STime clone() const;

	/** @brief ת���ɱ�������ʱ���Date���� */
	SDate toDate() const;
	/** @brief ת����UTC��׼ʱ���Date���� */
	SDate utcDate() const;

	/** @brief ��ȡ��������ͬ��ʱ��� */
	inline time_t seconds() const
	{
		return _tv.tv_sec;
	}

	/** @brief ��ȡ΢����, [0,1000000) @details ΢�벿��С��һ�� */
	inline long microSeconds() const
	{
		return _tv.tv_sec;
	}

	/** @brief ��ȡ����ʱ��� */
	inline int64 milliStamp() const
	{
		return _tv.tv_sec * 1000 + _tv.tv_usec / 1000;
	}

	/** @brief ��ȡ΢��ʱ��� */
	inline int64 microStamp() const
	{
		return _tv.tv_sec * 1000000 + _tv.tv_usec;
	}

	/** @brief ��ȡʱ��� */
	inline time_t stamp() const
	{
		return _tv.tv_sec;
	}

	/** @brief ��ȡUTCʱ��� */
	time_t utcStamp() const;

	/** @brief ����������΢���� */
	STime & set(time_t seconds, long microSeconds = 0);
	/** @brief ��ȡ΢����, [0,1000) */
	STime & setSeconds(time_t seconds);
	/** @brief ��ȡ΢����, [0,1000000) */
	STime & setMicroSeconds(long microSeconds);

	/**
	* @brief ����Ϊĳ��ʱ��Ŀ�ʼ
	* @param period ʱ�����ͣ�
	* @details
	*     ΪYearʱ����Ϊһ��Ŀ�ʼ��
	*	   ΪMonthʱ����Ϊһ�µĿ�ʼ��
	*	   ΪDayʱ����Ϊһ��Ŀ�ʼ��
	*	   ΪHourʱ����ΪһСʱ�Ŀ�ʼ��
	*	   ΪMinuteʱ����Ϊһ���ӵĿ�ʼ��
	*	   ΪSecondʱ����Ϊһ��Ŀ�ʼ��
	*	   ΪMilliSecondʱ����Ϊһ����Ŀ�ʼ��
	*	   ΪMicroSecondʱ����Ϊһ΢��Ŀ�ʼ
	*/
	STime & zeroSet(SDuration::Period period);

	/** @brief ��/�� һ��ʱ�� */
	STime & add(int64 value, SDuration::Period period);
	/** @brief ��/�� һ��ʱ�� */
	STime & add(const SDuration & duration);
	/** @brief ��/�� �� */
	STime & addWeek(int value);
	/** @brief ��/�� �� */
	STime & addDay(int value);
	/** @brief ��/�� ʱ */
	STime & addHour(int value);
	/** @brief ��/�� �� */
	STime & addMinute(int value);
	/** @brief ��/�� �� */
	STime & addSecond(int value);
	/** @brief ��/�� ���� */
	STime & addMilliSecond(int value);
	/** @brief ��/�� ΢�� */
	STime & addMicroSecond(int value);

	/**
	* @brief �Ƚ���ʱ��֮��Ĳ���
	* @param period ���ʱ������
	* @param other Ҫ�ȽϵĶ���
	* @details
	*     ΪYear��ʾ���������ݣ����Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
	*     ΪMonth��ʾ�������˵�������Ǿ��Բ�ֵ��2015-01-01��2014-12-30���1��
	*     ΪDay��ʾ����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1��
	*     ΪHour��ʾ�������Сʱ�������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1Сʱ
	*     ΪMinute��ʾ�����������������Ǿ��Բ�ֵ��2015-01-01 23:59:59��2015-01-02 00:00:00���1����
	*     ΪSecond��ʾ�����������
	*     ΪMilliSecond��ʾ������������
	*     ΪMicroSecond��ʾ�������΢����
	* @return ����this - other����Ӧ��ֵ
	*/
	int64 diff(const STime & other, SDuration::Period period = SDuration::Second);

	/** @brief ����1970-01-01 00:00:00��΢���� */
	int64 getUTCFullMicroSeconds() const;
	/** @brief ����1970-01-01 00:00:00�ĺ����� */
	int64 getUTCFullMilliSeconds() const;
	/** @brief ����1970-01-01 00:00:00������ @note ��getUTCStamp()������ͬ @see getUTCStamp */
	time_t getUTCFullSeconds() const;
	/** @brief ����1970-01-01 00:00:00�ķ��� */
	int getUTCFullMinutes() const;
	/** @brief ����1970-01-01 00:00:00��Сʱ */
	int getUTCFullHours() const;
	/** @brief ����1970-01-01 00:00:00������ */
	int getUTCFullDays() const;
	/** @brief ����1970-01-01 00:00:00������ @note ��0��ʼ��1970-01-01 00:00:00Ϊ��0������4 */
	int getUTCFullWeeks() const;

	STime operator + (const SDuration & duration);
	STime operator - (const SDuration & duration);
	SDuration operator - (const STime & other);
	STime & operator += (const SDuration & duration);
	STime & operator -= (const SDuration & duration);
	bool operator < (const STime & other);
	bool operator = (const STime & other);

private:
	struct timeval _tv;
};
#endif