/**
* SPoint2类
* 数学类型-Point
* @author ZeroX
* @version v1.0 30/07/2017
*/
#ifndef SPOINT_H
#define SPOINT_H
#include <math.h>
template<class _T=float>
class SPoint2{
public:
	_T x;
	_T y;

	/* 运算操作 */
	_T Distance(const SPoint2 &pt);		//取得距离
	bool Equals(SPoint2 pt);			//比较

	//属性操作
	_T GetPointX();
	_T GetPointY();
	void SetPoint(_T x, _T y);		//设置坐标
	void MovePoint(_T x, _T y);		//移动坐标

	bool operator ==(const SPoint2 &pt);//定义赋值运算符＝
	SPoint2  &operator   =(const SPoint2 &pt);
	SPoint2  operator	+(const SPoint2 &pt);

	//点减法运算结果应为向量
	SPoint2  operator	-(const SPoint2 &pt);

	SPoint2  &operator	+=(const SPoint2 &pt);
	SPoint2  &operator	-=(const SPoint2 &pt);//定义减法运算符-

	//乘法
	SPoint2  operator	*(const double k);
	SPoint2  &operator	*=(const double k);
	//除法
	SPoint2  operator	/(const double k);
	SPoint2  &operator	/=(const double k);

	SPoint2(_T x = 0, _T y = 0);
};

#endif
