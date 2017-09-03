#include "SVector2.h"

/* ���������� */
template<class _T>
_T SVector2<_T>::Module()
{
	return (_T)hypot(this->x, this->y);
}
template<class _T>
_T SVector2<_T>::Slope()
{
	return (-y / x);
}

/* ���������� */
template<class _T>
_T SVector2<_T>::Angle(const SVector2 &vt)
{
	return acos(this->Dot(vt) / this->Module() * vt.Module());
}

//�������
template<class _T>
_T SVector2<_T>::Dot(const SVector2 &vt)
{
	return x*vt.x + y*vt.y;
}
//���ֵ
template<class _T>
_T SVector2<_T>::Cross(const SVector2 &vt)
{
	return x*vt.y - y*vt.x;
}

//�������-ƽ��������˽��Ϊ��ֱƽ���һ������,�ڶ�ά�б���Ϊ(0,0)
template<class _T>
SVector2<_T> SVector2<_T>::CrossVec(const SVector2 &vt)
{
	SVector2 vtTmp;
	vtTmp.x = 0;
	vtTmp.y = 0;
	return vtTmp;
}

//�Ƿ�ƽ��
template<class _T>
bool SVector2<_T>::IsParallel(const SVector2 &vt)
{
	if (Cross(vt) == (_T)0) return true;
	else return false;
}

//�Ƿ�ֱ
template<class _T>
bool SVector2<_T>::IsVertical(const SVector2 &vt)
{
	if (Dot(vt) == (_T)0)return true;
	else return false;
}
/* �������Բ��� */
template<class _T>
void SVector2<_T>::SetVector(_T x, _T y)
{
	this->x = x;
	this->y = y;
}
template<class _T>
bool SVector2<_T>::Equals(SVector2 &vt)
{
	if (*this == vt) return true;
	else return false;
}

template<class _T>
bool SVector2<_T>::operator ==(const SVector2 &vt)
{
	if (this->x == vt.x && this->y == vt.y) return true;
	else return false;
}
//���帳ֵ�������
template<class _T>
SVector2<_T> &SVector2<_T>::operator   =(const SVector2 &vt)
{
	x = vt.x;
	y = vt.y;
	return *this;
}
//����ӷ��������
template<class _T>
SVector2<_T> SVector2<_T>::operator	+(const SVector2 &vt)
{
	SVector2 vtTmp;
	vtTmp.x = x + vt.x;
	vtTmp.y = y + vt.y;
	return vtTmp;
}
//������������-
template<class _T>
SVector2<_T> SVector2<_T>::operator	-(const SVector2 &vt)
{
	SVector2 vtTmp;
	vtTmp.x = x - vt.x;
	vtTmp.y = y - vt.y;
	return vtTmp;
}

template<class _T>
SVector2<_T> &SVector2<_T>::operator	+=(const SVector2 &vt)
{
	x = x + vt.x;
	y = y + vt.y;
	return *this;
}
//������������-
template<class _T>
SVector2<_T> &SVector2<_T>::operator	-=(const SVector2 &vt)
{
	x = x - vt.x;
	y = y - vt.y;
	return *this;
}

template<class _T>
SVector2<_T>::SVector2(_T x, _T y)
{
	this->x = x;
	this->y = y;
}
