/**
* SPOINT结构体
* 标签部件
* @author ZeroX
* @version v1.0 03/09/2017
*/
#ifndef _TAGSPOINT_H_
#define _TAGSPOINT_H_
#include <Windows.h>
typedef struct tagSPOINT:public POINT
{
	tagSPOINT();
	tagSPOINT(const POINT pt);
	tagSPOINT(int x, int y);

	//是否与矩形碰撞
	bool IsCollsion(tagSPOINT pt);
	bool IsCollsion(RECT rt);
	//是否在矩形内
	bool IsInRect(RECT rt);
	bool IsOnRect(RECT rt);

	bool operator == (const POINT pt);
	tagSPOINT &operator =(const tagSPOINT pt);
}SPOINT;

#endif