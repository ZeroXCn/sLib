/**
* tagSRECT结构体
* 矩形
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _STAGSRECT_H_
#define _STAGSRECT_H_

typedef struct tagSRECT
{
	int left, top, right, bottom;

	int GetX()
	{
		return left;
	}
	int GetY()
	{
		return right;
	}
	int GetWidth()
	{
		return right - left;
	}

	int GetHeight()
	{
		return bottom - top;
	}
	int Area()
	{
		return GetWidth() * GetHeight();
	}

	int Perimeter()
	{
		return 2 * (GetWidth() + GetHeight());
	}
}SRECT;

#endif