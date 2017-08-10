/**
* SDate类
* @brief 日期类
* @details 精确到秒，Windows下仅能表示1970-01-01 00:00:00之前的日期，Linux不受此限制。
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
	/** @brief 返回当前系统时区，比如UTC+8的时区为8 */
	static int localTimeZone();
	/** @brief 返回当前系统时区偏移，以秒为单位，比如UTC+8的时区为-28800 */
	static time_t localTimeZoneOffset();
	/** @brief 判断是否是闰年 */
	static bool isLeapYear(int year);
	/** @brief 某年某月一共有多少天 */
	static int yearMonthDays(int year, int month);

public:
	/** @brief 以当前时间构造 */
	SDate();
	/**
	* @brief 以时间戳(秒)构造
	* @param stamp 时间戳
	* @param utc 是否为UTC基准时间，为false则按本地日历时间构造
	*/
	SDate(time_t stamp, bool utc = false);
	/** @brief 以Time对象构造 */
	SDate(const STime &time);
	/** @brief 以SDate对象复制 */
	SDate(const SDate &other);

	/**
	* @brief 以指定时间构造
	* @note Windows下最小为1970-01-01 00:00:00
	* @param year 年，取值范围[1970, )
	* @param month 月，取值范围[1,12]
	* @param day 日，取值范围[1,31]
	* @param hour 时，取值范围[0,23]，默认为0
	* @param minute 分，取值范围[0,59]，默认为0
	* @param second 秒，取值范围[0,60]，默认为0
	*/
	SDate(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

	~SDate();

	/** @brief 克隆当前对象 */
	SDate clone() const;

	/** @brief 转换为Time对象 */
	STime toTime() const;
	/** @brief 转换为字符串，格式为1970-01-01 00:00:00 */
	std::string toString() const;

	/**
	* @brief 格式化为字符串
	* @param fmt 格式
	* @details
	*     %Y 用CCYY表示的年（如：2004）
	*     %m 月份 (01-12)
	*     %d 月中的第几天(01-31)
	*     %H 小时, 24小时格式 (00-23)
	*     %M 分钟(00-59)
	*     %S 秒钟(00-59)
	*     %X标准时间字符串（如：23:01:59）
	*     %% 百分号
	*
	* @return 如果发生错误返回空字符串
	*/
	std::string format(const char * fmt = "%Y-%m-%d %H:%M:%S") const;

	/** @brief 年，[1970, ) */
	inline int year() const
	{
		return _tm.tm_year + 1900;
	}

	/** @brief 月，[1,12] */
	inline int month() const
	{
		return _tm.tm_mon + 1;
	}

	/** @brief 日，[1,31] */
	inline int day() const
	{
		return _tm.tm_mday;
	}

	/** @brief 时，[0,23] */
	inline int hour() const
	{
		return _tm.tm_hour;
	}

	/** @brief 分，[0,59] */
	inline int minute() const
	{
		return _tm.tm_min;
	}

	/** @brief 秒，[0,60] */
	inline int second() const
	{
		return _tm.tm_sec;
	}

	/** @brief 星期，[1,7] */
	inline int week() const
	{
		return (_tm.tm_wday > 0) ? _tm.tm_wday : 7;
	}

	/** @brief 是否是UTC基准时间 */
	inline bool isUTC() const
	{
		return _isUTC;
	}

	/** @brief 转换为时间戳 @note 按本地时间（时区）转换，比如在东8区(UTC+8)时1970-01-01 00:00:00为-28800 */
	time_t stamp() const;
	/** @brief 转换为UTC时间戳 @note 比如1970-01-01 00:00:00为0 */
	time_t utcStamp() const;
	/** @brief 时区，比如UTC+8的时区为8 */
	int timeZone() const;
	/** @brief 时区偏移，以秒为单位，比如UTC+8的时区为-28800 */
	time_t timeZoneOffset() const;

	/** @brief 统一设置年月日 @note 比单独设置年/月/日更高效 */
	SDate & setDate(int year, int month, int day);
	/** @brief 设置年，[1970, ) @note 建议使用setSDate统一设置年月日 @see setSDate */
	SDate & setYear(int year);
	/** @brief 设置月，[1,12] @note 建议使用setSDate统一设置年月日 @see setSDate */
	SDate & setMonth(int month);
	/** @brief 设置日，[1,31] @note 建议使用setSDate统一设置年月日 @see setSDate*/
	SDate & setDay(int day);
	/** @brief 设置时，[0,23] */
	SDate & setHour(int hour);
	/** @brief 设置分，[0,59] */
	SDate & setMinute(int minute);
	/** @brief 设置秒，[0,60] */
	SDate & setSecond(int second);

	/**
	* @brief 设置为某个时间的开始
	* @param period 时间类型，
	* @details
	*      为Year时置零为一年的开始，
	*      为Month时置零为一月的开始，
	*      为Day时置零为一天的开始，
	*      为Hour时置零为一小时的开始，
	*      为Minute时置零为一分钟的开始，
	*      为Second/MilliSecond/MicroSecond时无效果，
	*/
	SDate & zeroSet(SDuration::Period period);

	/** @brief 加/减 一段时间 */
	SDate & add(int64 value, SDuration::Period period);
	/** @brief 加/减 一段时间 */
	SDate & add(const SDuration & duration);
	/** @brief 加/减 年 */
	SDate & addYear(int value);
	/** @brief 加/减 月 */
	SDate & addMonth(int value);

	/**
	* @brief 比较两时间之间的差异
	* @param period 结果时间类型
	* @param other 要比较的对象
	* @details
	*     为Year表示两者相差年份，不是绝对差值，2015-01-01与2014-12-30相差1年
	*     为Month表示两者相差说数，不是绝对差值，2015-01-01与2014-12-30相差1月
	*     为Day表示两者相差天数，不是绝对差值，2015-01-01 23:59:59与2015-01-02 00:00:00相差1天
	*     为Hour表示两者相差小时数，不是绝对差值，2015-01-01 23:59:59与2015-01-02 00:00:00相差1小时
	*     为Minute表示两者相差分钟数，不是绝对差值，2015-01-01 23:59:59与2015-01-02 00:00:00相差1分钟
	*     为Second表示两者相差秒数
	*     为MilliSecond表示两者相差毫秒数，SDate的精度为秒，所以只是将相差秒数*1000
	*     为MicroSecond表示两者相差微秒数，SDate的精度为秒，所以只是将相差秒数*1000000
	* @return 返回this - other的相应差值
	*/
	int64 diff(const SDate & other, SDuration::Period period = SDuration::Second);

	/** @brief 获取一年中的天，[1,366] */
	int getYearDay() const;
	/** @brief 距离1970-01-01 00:00:00的月数 */
	int getUTCFullMonths() const;
	/** @brief 距离1970-01-01 00:00:00的年数 */
	int getUTCFullYears() const;

	/** @brief 是否是闰年 */
	bool isLeapYear() const;
	/** @brief 是否是一月的最后一天 */
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