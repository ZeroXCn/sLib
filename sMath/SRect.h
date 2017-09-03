/**
* SPoint2类
* 数学类型-Rect
* @author ZeroX
* @version v1.0 30/07/2017
*/
#ifndef SRECT_H
#define SRECT_H
#include <math.h>
template<class _T=float>
class SRect
{
public:
	_T x;
	_T y;
	_T width;
	_T height;

	SRect();
	SRect(const SRect &or);	//必须进行深拷贝,否则引用的值会发生错误
	SRect(_T left, _T top, _T right, _T bottom);

	_T GetX();
	_T GetY();
	_T GetWidth();
	_T GetHeight();

	_T Area();
	_T Perimeter();

	//
	bool Equals(const SRect &rt);
	bool EqualsSize(const SRect &rt);
	
	//复制矩形
	void CopyRect(const SRect &rt);
	//按向量移动矩形
	void MoveRect(_T x, _T y);
	//增缩矩形大小
	void ExpandRect(_T width, _T height);
	//设置矩形大小
	void SetSize(_T width, _T height);


	bool operator ==(const SRect &rt);
	//定义赋值运算符＝
	SRect  & operator   =(const SRect &rt);


};
#endif