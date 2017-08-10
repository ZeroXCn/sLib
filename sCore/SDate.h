/**
* SDate��
* @brief ������
* @details ��ȷ���룬Windows�½��ܱ�ʾ1970-01-01 00:00:00֮ǰ�����ڣ�Linux���ܴ����ơ�
* @author havesnag
* @link https://github.com/havesnag/date
*/

#include "SObject.h"
#include "SDuration.h"
#include "STime.h"

#ifndef _SDATE_H_
#define _SDATE_H_
class STime;

class SDate :public SObject
{
public:
	/** @brief ���ص�ǰϵͳʱ��������UTC+8��ʱ��Ϊ8 */
	static int localTimeZone();
	/** @brief ���ص�ǰϵͳʱ��ƫ�ƣ�����Ϊ��λ������UTC+8��ʱ��Ϊ-28800 */
	static time_t localTimeZoneOffset();
	/** @brief �ж��Ƿ������� */
	static bool isLeapYear(int year);
	/** @brief ĳ��ĳ��һ���ж����� */
	static int yearMonthDays(int year, int month);

public:
	/** @brief �Ե�ǰʱ�乹�� */
	SDate();
	/**
	* @brief ��ʱ���(��)����
	* @param stamp ʱ���
	* @param utc �Ƿ�ΪUTC��׼ʱ�䣬Ϊfalse�򰴱�������ʱ�乹��
	*/
	SDate(time_t stamp, bool utc = false);
	/** @brief ��Time������ */
	SDate(const STime &time);
	/** @brief ��SDate������ */
	SDate(const SDate &other);

	/**
	* @brief ��ָ��ʱ�乹��
	* @note Windows����СΪ1970-01-01 00:00:00
	* @param year �꣬ȡֵ��Χ[1970, )
	* @param month �£�ȡֵ��Χ[1,12]
	* @param day �գ�ȡֵ��Χ[1,31]
	* @param hour ʱ��ȡֵ��Χ[0,23]��Ĭ��Ϊ0
	* @param minute �֣�ȡֵ��Χ[0,59]��Ĭ��Ϊ0
	* @param second �룬ȡֵ��Χ[0,60]��Ĭ��Ϊ0
	*/
	SDate(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

	~SDate();

	/** @brief ��¡��ǰ���� */
	SDate clone() const;

	/** @brief ת��ΪTime���� */
	STime toTime() const;
	/** @brief ת��Ϊ�ַ�������ʽΪ1970-01-01 00:00:00 */
	std::string toString() const;

	/**
	* @brief ��ʽ��Ϊ�ַ���
	* @param fmt ��ʽ
	* @details
	*     %Y ��CCYY��ʾ���꣨�磺2004��
	*     %m �·� (01-12)
	*     %d ���еĵڼ���(01-31)
	*     %H Сʱ, 24Сʱ��ʽ (00-23)
	*     %M ����(00-59)
	*     %S ����(00-59)
	*     %X��׼ʱ���ַ������磺23:01:59��
	*     %% �ٷֺ�
	*
	* @return ����������󷵻ؿ��ַ���
	*/
	std::string format(const char * fmt = "%Y-%m-%d %H:%M:%S") const;

	/** @brief �꣬[1970, ) */
	inline int year() const
	{
		return _tm.tm_year + 1900;
	}

	/** @brief �£�[1,12] */
	inline int month() const
	{
		return _tm.tm_mon + 1;
	}

	/** @brief �գ�[1,31] */
	inline int day() const
	{
		return _tm.tm_mday;
	}

	/** @brief ʱ��[0,23] */
	inline int hour() const
	{
		return _tm.tm_hour;
	}

	/** @brief �֣�[0,59] */
	inline int minute() const
	{
		return _tm.tm_min;
	}

	/** @brief �룬[0,60] */
	inline int second() const
	{
		return _tm.tm_sec;
	}

	/** @brief ���ڣ�[1,7] */
	inline int week() const
	{
		return (_tm.tm_wday > 0) ? _tm.tm_wday : 7;
	}

	/** @brief �Ƿ���UTC��׼ʱ�� */
	inline bool isUTC() const
	{
		return _isUTC;
	}

	/** @brief ת��Ϊʱ��� @note ������ʱ�䣨ʱ����ת���������ڶ�8��(UTC+8)ʱ1970-01-01 00:00:00Ϊ-28800 */
	time_t stamp() const;
	/** @brief ת��ΪUTCʱ��� @note ����1970-01-01 00:00:00Ϊ0 */
	time_t utcStamp() const;
	/** @brief ʱ��������UTC+8��ʱ��Ϊ8 */
	int timeZone() const;
	/** @brief ʱ��ƫ�ƣ�����Ϊ��λ������UTC+8��ʱ��Ϊ-28800 */
	time_t timeZoneOffset() const;

	/** @brief ͳһ���������� @note �ȵ���������/��/�ո���Ч */
	SDate & setDate(int year, int month, int day);
	/** @brief �����꣬[1970, ) @note ����ʹ��setSDateͳһ���������� @see setSDate */
	SDate & setYear(int year);
	/** @brief �����£�[1,12] @note ����ʹ��setSDateͳһ���������� @see setSDate */
	SDate & setMonth(int month);
	/** @brief �����գ�[1,31] @note ����ʹ��setSDateͳһ���������� @see setSDate*/
	SDate & setDay(int day);
	/** @brief ����ʱ��[0,23] */
	SDate & setHour(int hour);
	/** @brief ���÷֣�[0,59] */
	SDate & setMinute(int minute);
	/** @brief �����룬[0,60] */
	SDate & setSecond(int second);

	/**
	* @brief ����Ϊĳ��ʱ��Ŀ�ʼ
	* @param period ʱ�����ͣ�
	* @details
	*      ΪYearʱ����Ϊһ��Ŀ�ʼ��
	*      ΪMonthʱ����Ϊһ�µĿ�ʼ��
	*      ΪDayʱ����Ϊһ��Ŀ�ʼ��
	*      ΪHourʱ����ΪһСʱ�Ŀ�ʼ��
	*      ΪMinuteʱ����Ϊһ���ӵĿ�ʼ��
	*      ΪSecond/MilliSecond/MicroSecondʱ��Ч����
	*/
	SDate & zeroSet(SDuration::Period period);

	/** @brief ��/�� һ��ʱ�� */
	SDate & add(int64 value, SDuration::Period period);
	/** @brief ��/�� һ��ʱ�� */
	SDate & add(const SDuration & duration);
	/** @brief ��/�� �� */
	SDate & addYear(int value);
	/** @brief ��/�� �� */
	SDate & addMonth(int value);

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
	*     ΪMilliSecond��ʾ��������������SDate�ľ���Ϊ�룬����ֻ�ǽ��������*1000
	*     ΪMicroSecond��ʾ�������΢������SDate�ľ���Ϊ�룬����ֻ�ǽ��������*1000000
	* @return ����this - other����Ӧ��ֵ
	*/
	int64 diff(const SDate & other, SDuration::Period period = SDuration::Second);

	/** @brief ��ȡһ���е��죬[1,366] */
	int getYearDay() const;
	/** @brief ����1970-01-01 00:00:00������ */
	int getUTCFullMonths() const;
	/** @brief ����1970-01-01 00:00:00������ */
	int getUTCFullYears() const;

	/** @brief �Ƿ������� */
	bool isLeapYear() const;
	/** @brief �Ƿ���һ�µ����һ�� */
	bool isLastDayOfMonth() const;

	SDate operator + (const SDuration & duration);
	SDate operator - (const SDuration & duration);
	SDuration operator - (const SDate & other);
	SDate & operator += (const SDuration & duration);
	SDate & operator -= (const SDuration & duration);
	bool operator < (const SDate & other);
	bool operator = (const SDate & other);

protected:
	void _set(time_t stamp);
	void _update();

private:
	struct tm _tm;
	bool _isUTC;
};
#endif