#ifndef SVECTOR3_H
#define SVECTOR3_H
#include <math.h>

class SVector3
{
public:
	float x;
	float y;
	float z;

	float GetModule()
	{
		return sqrt(x*x + y*y + z*z);
	}

	void SetVector(float x, float y,float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	bool equals(SVector3 vt){
		if (*this == vt) return true;
		else return false;
	}

	
	bool operator ==(const SVector3 &vt)
	{
		if (this->x == vt.x && this->y == vt.y&& this->z == vt.z) return true;
		else return false;
	}
	//���帳ֵ�������
	SVector3  & operator   =(const SVector3 &vt)
	{
		x = vt.x;
		y = vt.y;
		z = vt.z;
		return *this;
	}
	//����ӷ��������
	SVector3  operator	+(const SVector3 &vt)
	{
		SVector3 vtTmp;
		vtTmp.x = x + vt.x;
		vtTmp.y = y + vt.y;
		vtTmp.z = z + vt.z;
		return vtTmp;
	}
	//������������-
	SVector3  operator	-(const SVector3 &vt)
	{
		SVector3 vtTmp;
		vtTmp.x = x - vt.x;
		vtTmp.y = y - vt.y;
		vtTmp.z = z - vt.z;
		return vtTmp;
	}

	SVector3  &operator	+=(const SVector3 &vt)
	{
		x = x + vt.x;
		y = y + vt.y;
		z = z + vt.z;
		return *this;
	}
	//������������-
	SVector3  &operator	-=(const SVector3 &vt)
	{
		x = x - vt.x;
		y = y - vt.y;
		z = z - vt.z;
		return *this;
	}

	////�Ƿ�ƽ��
	//bool IsParallel(const SVector3 &vt)
	//{
	//	if (x*vt.y - vt.x*y == 0) return true;
	//	else return false;
	//}

	////�Ƿ�ֱ
	//bool IsVertical(const SVector3 &vt)
	//{
	//	if (x*vt.x + y*vt.y == 0)return true;
	//	else return false;
	//}

	SVector3(){ }
	SVector3(float x, float y,float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
#endif