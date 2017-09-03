#include "SPoint2.h"
template<class _T>
_T SPoint2<_T>::Distance(const SPoint2 &pt)
{
	_T sx = pt.x - x;
	_T sy = pt.y - y;
	return sqrt(sx*sx + sy*sy);
}

template<class _T>
bool SPoint2<_T>::Equals(SPoint2 pt){
	if (this->x == pt.x && this->y == pt.y) return true;
	else return false;
}
template<class _T>
_T SPoint2<_T>::GetPointX()
{
	return this->x;
}

template<class _T>
_T SPoint2<_T>::GetPointY()
{
	return this->y;
}

template<class _T>
void SPoint2<_T>::SetPoint(_T x, _T y)
{
	this->x = x;
	this->y = y;
}

template<class _T>
void SPoint2<_T>::MovePoint(_T x, _T y)
{
	this->x += x;
	this->y += y;
}

template<class _T>
bool SPoint2<_T>::operator ==(const SPoint2 &pt)
{
	return this->Equals(pt);
}

//定义赋值运算符＝
template<class _T>
SPoint2<_T>  & SPoint2<_T>::operator   =(const SPoint2 &pt)
{
	x = pt.x;
	y = pt.y;
	return *this;
}

//定义加法运算符＋
template<class _T>
SPoint2<_T>  SPoint2<_T>::operator	+(const SPoint2 &pt)
{
	SPoint2 ptTmp;
	ptTmp.x = x + pt.x;
	ptTmp.y = y + pt.y;
	return ptTmp;
}

//定义减法运算符-
template<class _T>
SPoint2<_T>  SPoint2<_T>::operator	-(const SPoint2 &pt)
{
	SPoint2 ptTmp;
	ptTmp.x = x - pt.x;
	ptTmp.y = y - pt.y;
	return ptTmp;
}

template<class _T>
SPoint2<_T>  &SPoint2<_T>::operator	+=(const SPoint2 &pt)
{
	x = x + pt.x;
	y = y + pt.y;
	return *this;
}

//定义减法运算符-
template<class _T>
SPoint2<_T>  &SPoint2<_T>::operator	-=(const SPoint2 &pt)
{
	x = x - pt.x;
	y = y - pt.y;
	return *this;
}


//乘法
template<class _T>
SPoint2<_T>  SPoint2<_T>::operator	*(const double k)
{
	SPoint2 ptTmp;
	ptTmp.x = this->x * k;
	ptTmp.y = this->y * k;
	return ptTmp;
}
template<class _T>
SPoint2<_T>  &SPoint2<_T>::operator	*=(const double k)
{
	this->x *= k;
	this->y *= k;
	return *this;
}
//除法
template<class _T>
SPoint2<_T>  SPoint2<_T>::operator	/(const double k)
{
	SPoint2 ptTmp;
	ptTmp.x = this->x / k;
	ptTmp.y = this->y / k;
	return ptTmp;
}
template<class _T>
SPoint2<_T>  &SPoint2<_T>::operator	/=(const double k)
{
	this->x /= k;
	this->y /= k;
	return *this;
}

template<class _T>
SPoint2<_T>::SPoint2(_T x, _T y) :x(x), y(y)
{

}
