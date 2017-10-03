/**
* SPoint2类
* 数学类型-Vector
* @author ZeroX
* @version v1.0 30/07/2017
*/
#ifndef SVECTOR2_H
#define SVECTOR2_H
#include <math.h>
template<class _T=float>
class SVector2
{
public:
	_T x;
	_T y;

	/* 单向量操作 */
	//取得向量模
	_T Module();
	_T Length();
	//取得向量斜率
	_T Slope();
	//规范化
	SVector2 &Normalize();

	/* 二向量操作 */
	//两向量夹角
	_T Angle(const SVector2 &vt);


	//向量点乘
	_T Dot(const SVector2 &vt);
	//叉乘值
	_T Cross(const SVector2 &vt);
	
	//向量叉乘-平面向量叉乘结果为垂直平面的一个向量,在二维中表现为(0,0)
	SVector2 CrossVec(const SVector2 &vt);

	//是否平行
	bool IsParallel(const SVector2 &vt);
	//是否垂直
	bool IsVertical(const SVector2 &vt);


	/* 向量属性操作 */
	void SetVector(_T x, _T y);
	bool Equals(SVector2 &vt);
	
	bool operator ==(const SVector2 &vt);
	//定义赋值运算符＝
	SVector2  & operator   =(const SVector2 &vt);
	//定义加法运算符＋
	SVector2  operator	+(const SVector2 &vt);
	//定义减法运算符-
	SVector2  operator	-(const SVector2 &vt);

	SVector2  &operator	+=(const SVector2 &vt);
	//定义减法运算符-
	SVector2  &operator	-=(const SVector2 &vt);

	//定义减法运算符*
	SVector2  operator	*(const _T s);
	SVector2  &operator	*=(const _T s);

	//定义减法运算符/
	SVector2  operator	/(const _T s);
	SVector2  &operator	/=(const _T s);

	SVector2(_T x = 0, _T y = 0);

};

#endif