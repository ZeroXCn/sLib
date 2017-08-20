/**
* SMathHelper��
* @brief ��ѧ������
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
	//��ȡ��������
	int GetInteger(float  x)
	{
		return (int)x;
	}

	//��ȡС������
	float GetFloat(float  x)
	{
		return (float)((float)x - (int)x);
	}

	//�Ƚϸ�����
	bool EqualFloat(float a, float b, float fEpsilon = 1e-6f)
	{
		return (fabs(a - b) < fEpsilon);
	}

	//ȡ��λ��
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

		if (integer == 0 && !EqualFloat(flo,0.f))bit = 0;
		else if (integer != 0 && flo == 0)return bit;

		//TODO:���ھ������,���ܲ�׼
		do
		{
			flo *= radis;
			bit++;
		} while (!EqualFloat(flo - (int)flo, 0.f));
		return bit;
	}

	//ȡ�������
	int GetRandomNumber(int x, int y)
	{
		srand((unsigned)time(NULL));//��������ӣ���ʱ��Ϊ�仯��λ
		int ret = rand() % (y - x + 1) + x; //�������ΧX~Y
		return ret;
	}
	//ȡ�������,bitΪ��ȷλ��
	float GetRandomNumber(float x, float y,int bit)
	{
		srand((unsigned)time(NULL));//��������ӣ���ʱ��Ϊ�仯��λ
		int pre = (int)pow(10.0f, bit);
		int newx = (int)x*pre;
		int newy = (int)y*pre;
		int ret = rand() % (newy - newx + 1) + newx; //�������ΧX~Y
		float newret = (float)ret / pre;
		return newret;
	}
	//ȡ�������,bitΪ��ȷλ��
	float GetRandomNumber(float x, float y)
	{
		int bit = 0;
		int xbit= GetBitCount(GetFloat(x));
		int ybit = GetBitCount(GetFloat(y));
		bit = xbit > ybit ? xbit : ybit;
		return GetRandomNumber(x, y, bit);
	}

	//����֮��-�����-��������
	float InvSqrt(float x)
	{
		float xhalf = 0.5f * x;
		int i = *(int *)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(float *)&i;
		x = x * (1.5f - xhalf * x * x);
		return x;
	}

}

#endif