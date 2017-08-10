/**
* STime类
* @brief 时间类
* @details 精确到微秒，可与Date相互转换，转换为Date将损失精度到秒
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
	/** @brief 以时间戳构造 */
	STime(time_t stamp);
	/** @brief 以Date对象构造 */
	STime(const SDate &date);
	/** @brief 以STime对象复制 */
	STime(const STime &time);
	~STime();

	/** @brief 克隆当前对象 */
	STime clone() const;

	/** @brief 转换成本地日历时间的Date对象 */
	SDate toDate() const;
	/** @brief 转换成UTC基准时间的Date对象 */
	SDate utcDate() const;

	/** @brief 获取秒数，等同于时间戳 */
	inline time_t seconds() const
	{
		return _tv.tv_sec;
	}

	/** @brief 获取微秒数, [0,1000000) @details 微秒部分小于一秒 */
	inline long microSeconds() const
	{
		return _tv.tv_sec;
	}

	/** @brief 获取毫秒时间戳 */
	inline int64 milliStamp() const
	{
		return _tv.tv_sec * 1000 + _tv.tv_usec / 1000;
	}

	/** @brief 获取微秒时间戳 */
	inline int64 microStamp() const
	{
		return _tv.tv_sec * 1000000 + _tv.tv_usec;
	}

	/** @brief 获取时间戳 */
	inline time_t stamp() const
	{
		return _tv.tv_sec;
	}

	/** @brief 获取UTC时间戳 */
	time_t utcStamp() const;

	/** @brief 设置秒数和微秒数 */
	STime & set(time_t seconds, long microSeconds = 0);
	/** @brief 获取微秒数, [0,1000) */
	STime & setSeconds(time_t seconds);
	/** @brief 获取微秒数, [0,1000000) */
	STime & setMicroSeconds(long microSeconds);

	/**
	* @brief 设置为某个时间的开始
	* @param period 时间类型，
	* @details
	*     为Year时置零为一年的开始，
	*	   为Month时置零为一月的开始，
	*	   为Day时置零为一天的开始，
	*	   为Hour时置零为一小时的开始，
	*	   为Minute时置零为一分钟的开始，
	*	   为Second时置零为一秒的开始，
	*	   为MilliSecond时置零为一毫秒的开始，
	*	   为MicroSecond时置零为一微秒的开始
	*/
	STime & zeroSet(SDuration::Period period);

	/** @brief 加/减 一段时间 */
	STime & add(int64 value, SDuration::Period period);
	/** @brief 加/减 一段时间 */
	STime & add(const SDuration & duration);
	/** @brief 加/减 周 */
	STime & addWeek(int value);
	/** @brief 加/减 天 */
	STime & addDay(int value);
	/** @brief 加/减 时 */
	STime & addHour(int value);
	/** @brief 加/减 分 */
	STime & addMinute(int value);
	/** @brief 加/减 秒 */
	STime & addSecond(int value);
	/** @brief 加/减 毫秒 */
	STime & addMilliSecond(int value);
	/** @brief 加/减 微秒 */
	STime & addMicroSecond(int value);

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
	*     为MilliSecond表示两者相差毫秒数
	*     为MicroSecond表示两者相差微秒数
	* @return 返回this - other的相应差值
	*/
	int64 diff(const STime & other, SDuration::Period period = SDuration::Second);

	/** @brief 距离1970-01-01 00:00:00的微秒数 */
	int64 getUTCFullMicroSeconds() const;
	/** @brief 距离1970-01-01 00:00:00的毫秒数 */
	int64 getUTCFullMilliSeconds() const;
	/** @brief 距离1970-01-01 00:00:00的秒数 @note 与getUTCStamp()含义相同 @see getUTCStamp */
	time_t getUTCFullSeconds() const;
	/** @brief 距离1970-01-01 00:00:00的分钟 */
	int getUTCFullMinutes() const;
	/** @brief 距离1970-01-01 00:00:00的小时 */
	int getUTCFullHours() const;
	/** @brief 距离1970-01-01 00:00:00的天数 */
	int getUTCFullDays() const;
	/** @brief 距离1970-01-01 00:00:00的周数 @note 从0开始，1970-01-01 00:00:00为第0周星期4 */
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