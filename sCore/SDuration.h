/**
* SDuration类
* @brief 表示时间段
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
	/** @brief 时间类型，级别依次上升，精度依次下降 */
	enum Period
	{
		/** @brief 微秒 1/1000000秒 */
		MicroSecond = 5,
		/** @brief 毫秒 1/1000秒 */
		MilliSecond = 6,
		/** @brief 秒 */
		Second = 11,
		/** @brief 分 60秒 */
		Minute = 12,
		/** @brief 小时 3600秒 */
		Hour = 13,
		/** @brief 天 86400秒 */
		Day = 14,
		/** @brief 周 604800秒 */
		Week = 15,
		/** @brief 月 周与月相互转换比例为1:4 */
		Month = 22,
		/** @brief 年 */
		Year = 23,
	};

	SDuration(int64 value = 1, Period period = Second);
	SDuration(const SDuration &SDuration);
	~SDuration();

	/** @brief 克隆当前对象 */
	SDuration clone() const;

	/** @brief 获取数值 */
	inline int64 value() const
	{
		return _value;
	}

	/** @brief 获取周期 */
	inline Period period() const
	{
		return _period;
	}

	/** @brief 设置时间段的数值和周期 */
	SDuration & set(int64 value, Period period = Second);
	/** @brief 设置时间段的数值 */
	SDuration & setValue(int64 value);
	/** @brief 设置时间段的周期 */
	SDuration & setPeriod(Period period);

	/** @brief 提升级别，降低精度，这种转换方式并不是准确的，周与月转换时换1:4换算 */
	SDuration & rase();
	/** @brief 降低级别，提升精度，这种转换方式并不是准确的，周与月转换时换1:4换算 */
	SDuration & down();
	/** @brief 转换成指定类型的时间段 */
	SDuration & as(Period period);
	/** @brief 获取值转换成某种类型后的值 */
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