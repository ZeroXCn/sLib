#ifndef SVECTOR2_H
#define SVECTOR2_H
#include <math.h>
#include "SPoint.h"
class SVector2
{
public:
	float x;
	float y;

	float GetModule()
	{
		return hypot(this->x, this->y);
	}

	float GetModule(const SVector2 &vt)
	{
		SVector2 vtTep;
		vtTep.x = this->x + vt.x;
		vtTep.y = this->y + vt.y;

		return vtTep.GetModule();
	}

	void SetVector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	bool equals(SVector2 vt){
		if (*this == vt) return true;
		else return false;
	}

	float GetAngle()
	{
		return atan(this->y / this->x);
	}
	//两向量夹角
	float GetAngle(const SVector2 &vt)
	{
		float module = x*vt.x + y*vt.y;
		float lengthA = sqrt(x*x + y*y);
		float lengthB = sqrt(vt.x*vt.x + vt.y*vt.y);

		return acos(module / (lengthA*lengthB));
	}
	float GetSlope()
	{
		return (this->y / this->x);
	}
	bool operator ==(const SVector2 &vt)
	{
		if (this->x == vt.x && this->y == vt.y) return true;
		else return false;
	}
	//定义赋值运算符＝
	SVector2  & operator   =(const SVector2 &vt)
	{
		x = vt.x;
		y = vt.y;
		return *this;
	}
	//定义加法运算符＋
	SVector2  operator	+(const SVector2 &vt)
	{
		SVector2 vtTmp;
		vtTmp.x = x + vt.x;
		vtTmp.y = y + vt.y;
		return vtTmp;
	}
	//定义减法运算符-
	SVector2  operator	-(const SVector2 &vt)
	{
		SVector2 vtTmp;
		vtTmp.x = x - vt.x;
		vtTmp.y = y - vt.y;
		return vtTmp;
	}

	SVector2  &operator	+=(const SVector2 &vt)
	{
		x = x + vt.x;
		y = y + vt.y;
		return *this;
	}
	//定义减法运算符-
	SVector2  &operator	-=(const SVector2 &vt)
	{
		x = x - vt.x;
		y = y - vt.y;
		return *this;
	}

	//是否平行
	bool IsParallel(const SVector2 &vt)
	{
		if (x*vt.y - vt.x*y == 0) return true;
		else return false;
	}

	//是否垂直
	bool IsVertical(const SVector2 &vt)
	{
		if (x*vt.x + y*vt.y == 0)return true;
		else return false;
	}

	float DotProduct(const SVector2 &vt)
	{
		return x*vt.x + y*vt.y;
	}

	float  CrossProductModule(SVector2 &vt)
	{
		float moduleA = this->GetModule();
		float moduleB = vt.GetModule();

		float Angle = this->GetAngle(vt);

		return moduleA *moduleB *sin(Angle);

	}

	SVector2(){ ; }
	SVector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	SVector2(SPoint End, SPoint Start)
	{
		this->x = End.x - Start.x;
		this->y = End.y - Start.y;
	}

};

#endif