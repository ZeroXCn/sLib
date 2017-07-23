#ifndef SRECT_H
#define SRECT_H
#include <math.h>
class SRect
{
public:
	float left;
	float top;
	float right;
	float bottom;

	float &x = left, &y = top, &width = right, &height = bottom;

	SRect(){}

	//必须进行深拷贝,否则引用的值会发生错误
	SRect(const SRect &or)
	{
		this->left = or.left;
		this->top = or.top;
		this->right = or.right;
		this->bottom = or.bottom;
	}

	SRect(float left, float top, float right, float bottom){
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	float GetWidth()
	{
		return fabs(right - left);
	}
	float GetHeight()
	{
		return fabs(bottom - top);
	}

	float GetArea(){
		return fabs((right - left) * (bottom - top));
	}


	bool equals(SRect rt)
	{
		if (this->GetWidth() == rt.GetWidth() && this->GetHeight() == rt.GetHeight()) return true;
		else false;
	}

	SRect GetScopeRect(){
		return *this;
	}
	//保存位置不变,复制矩形大小
	void CopyRect(SRect &rt)
	{

		this->right = this->left + rt.GetWidth();
		this->bottom = this->top + rt.GetHeight();


	}
	//按向量移动矩形
	void MoveRect(float x, float y)
	{
		this->left += x;
		this->top += y;
		this->right += x;
		this->bottom += y;
	}

	//增缩矩形大小
	void ExpandRect(float width, float height)
	{
		this->right += width;
		this->bottom += height;
	}
	//设置矩形大小
	void SetSize(float width, float height)
	{
		this->right = this->left + width;
		this->bottom = this->top + height;
	}
	bool operator ==(const SRect &rt)
	{
		if (this->left == rt.left && this->top == rt.top && this->right == rt.right && this->bottom == rt.bottom) return true;
		else return false;
	}
	//定义赋值运算符＝
	SRect  & operator   =(const SRect &rt)
	{
		left = rt.left;
		top = rt.top;
		right = rt.right;
		bottom = rt.bottom;
		return *this;
	}

	void TransToXYRect()
	{
		SRect &a = *this;
		a.x = a.left;
		a.y = a.top;
		a.width = a.right - a.left;
		a.height = a.bottom - a.top;
	}

	void TransToLeftRightRect()
	{
		SRect &a = *this;
		a.left = a.x;
		a.top = a.y;
		a.right = a.x + a.width;
		a.bottom = a.y + a.height;
	}


};
#endif