/**
* SMathHelper类
* @brief 数学辅助类
* @author ZeroX
* @version v1.0
* @date 16/08/2017
* @update 16/08/2017
*/

#ifndef _SMATHHELPER_H
#define _SMATHHELPER_H
#include <math.h>
#include <time.h>
#include <stdlib.h>
namespace SMathHelper
{	
	//提取整数部分
	int GetInteger(float  x)
	{
		return (int)x;
	}

	//提取小数部分
	float GetFloat(float  x)
	{
		return (float)((float)x - (int)x);
	}

	//取得位数
	int GetBitCount(int num,int radis = 10)
	{
		int bit = 0;
		do
		{
			num /= radis;
			bit++;
		} while (num != 0);
		return bit;
	}
	int GetBitCount(float num, int radis = 10)
	{
		int integer = GetInteger(num);
		int bit = GetBitCount(integer, radis);
		float flo = GetFloat(num);

		if (integer == 0 && flo!=0)bit = 0;
		else if (integer != 0 && flo == 0)return bit;

		//TODO:存在精度误差,可能不准
		do
		{
			flo *= radis;
			bit++;
		} while (flo - (int)flo != 0.f);
		return bit;
	}

	//取得随机数
	int GetRandomNumber(int x, int y)
	{
		srand((unsigned)time(NULL));//随机数种子，以时间为变化单位
		int ret = rand() % (y - x + 1) + x; //随机数范围X~Y
		return ret;
	}
	//取得随机数,bit为精确位数
	float GetRandomNumber(float x, float y,int bit)
	{
		srand((unsigned)time(NULL));//随机数种子，以时间为变化单位
		int pre = (int)pow(10.0f, bit);
		int newx = (int)x*pre;
		int newy = (int)y*pre;
		int ret = rand() % (newy - newx + 1) + newx; //随机数范围X~Y
		float newret = (float)ret / pre;
		return newret;
	}
	//取得随机数,bit为精确位数
	float GetRandomNumber(float x, float y)
	{
		int bit = 0;
		int xbit= GetBitCount(GetFloat(x));
		int ybit = GetBitCount(GetFloat(y));
		bit = xbit > ybit ? xbit : ybit;
		return GetRandomNumber(x, y, bit);
	}



}

#endif