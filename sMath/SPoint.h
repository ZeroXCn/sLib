#ifndef SPOINT_H
#define SPOINT_H
#include <math.h>
class SPoint{
public:
	float x;
	float y;

	float GetDistance(const SPoint &pt)
	{
		float sx = pt.x - x;
		float sy = pt.y - y;
		return sqrt(sx*sx + sy*sy);
	}

	bool equals(SPoint pt){
		if (this->x == pt.x && this->y == pt.y) return true;
		else return false;
	}

	void SetPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void MovePoint(float x, float y)
	{
		this->x += x;
		this->y += y;
	}

	bool operator ==(const SPoint &pt)
	{
		if (this->x == pt.x && this->y == pt.y) return true;
		else return false;
	}
	//���帳ֵ�������
	SPoint  & operator   =(const SPoint &pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}

	//����ӷ��������
	SPoint  operator	+(const SPoint &pt)
	{
		SPoint ptTmp;
		ptTmp.x = x + pt.x;
		ptTmp.y = y + pt.y;
		return ptTmp;
	}

	//������������-
	SPoint  operator	-(const SPoint &pt)
	{
		SPoint ptTmp;
		ptTmp.x = x - pt.x;
		ptTmp.y = y - pt.y;
		return ptTmp;
	}

	SPoint  &operator	+=(const SPoint &pt)
	{
		x = x + pt.x;
		y = y + pt.y;
		return *this;
	}

	//������������-
	SPoint  &operator	-=(const SPoint &pt)
	{
		x = x - pt.x;
		y = y - pt.y;
		return *this;
	}

	SPoint(){}
	SPoint(float x, float y){ this->x = x; this->y = y; }
public:
	static float GetDistance(SPoint &a, SPoint &b)
	{
		return a.GetDistance(b);
	}

};

#endif
