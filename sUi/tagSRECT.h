/**
* tagSRECT结构体
* 矩形
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _TAGSRECT_H_
#define _TAGSRECT_H_
#include <Windows.h>
typedef struct tagSRECT:public RECT
{
	tagSRECT();
	tagSRECT(const RECT rt);
	tagSRECT(int left,int top,int right,int bottom);

	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	//取得面积
	int GetArea();
	//取得周长
	int GetPerimeter();
	//取得几何中心
	POINT GetCenter();
	//按向量移动矩形
	void Move(int x, int y);
	//移动到指定矩形的中心
	void MoveToCenter(RECT rt);
	//矩形是否碰撞
	bool IsCollision(tagSRECT rt);
	bool IsCollision(RECT rt,RECT *out);

	//是否在矩形内
	bool IsInRect(tagSRECT rt);

	bool operator ==(tagSRECT rt);
	tagSRECT &operator =(tagSRECT rt);
}SRECT;

#endif