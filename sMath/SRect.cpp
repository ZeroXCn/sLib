#include "SRect.h"
template<class _T>
SRect<_T>::SRect():x(0), y(0), width(0), height(0)
{

}

template<class _T>
SRect<_T>::SRect(const SRect &or)
{
	this->x = or.x;
	this->y = or.y;
	this->width = or.widtj;
	this->height = or.height;
}

template<class _T>
SRect<_T>::SRect(_T x, _T y, _T width, _T height) :
x(x), y(y), width(width), height(height)
{

}

template<class _T>
_T SRect<_T>::GetX()
{
	return this->x;
}

template<class _T>
_T SRect<_T>::GetY()
{
	return this->y;
}

template<class _T>
_T SRect<_T>::GetWidth()
{
	return this->width;
}

template<class _T>
_T SRect<_T>::GetHeight()
{
	return this->height;
}

template<class _T>
_T SRect<_T>::Area()
{
	return width * height;
}

template<class _T>
_T SRect<_T>::Perimeter()
{
	return 2 * (width + height)
}

template<class _T>
bool SRect<_T>::Equals(const SRect &rt)
{
	if (this->width == rt.width && this->height == rt.height&&
		this->x == rt.x && this->y == rt.y) 
		return true;
	else return false;
}

template<class _T>
bool SRect<_T>::EqualsSize(const SRect &rt)
{
	if (this->width == rt.width && this->height == rt.height) return true;
	else return false;
}


//保存位置不变,复制矩形大小
template<class _T>
void SRect<_T>::CopyRect(const SRect &rt)
{

	this->x = rt.x;
	this->y = rt.y;
	this->width = rt.widtj;
	this->height = rt.height;


}
//按向量移动矩形
template<class _T>
void SRect<_T>::MoveRect(_T x, _T y)
{
	this->x += x;
	this->y += y;
}

//增缩矩形大小
template<class _T>
void SRect<_T>::ExpandRect(_T x, _T y)
{
	this->width += width;
	this->height += height;
}
//设置矩形大小
template<class _T>
void SRect<_T>::SetSize(_T width, _T height)
{
	this->width =  width;
	this->height =  height;
}

template<class _T>
bool SRect<_T>::operator ==(const SRect &rt)
{
	return this->Equals(rt);
}

//定义赋值运算符＝
template<class _T>
SRect<_T>  &SRect<_T>::operator   =(const SRect &rt)
{
	this->x = rt.x;
	this->y = rt.y;
	this->width = rt.widtj;
	this->height = rt.height;
	return *this;
}