/**
* SPOINT�ṹ��
* ��ǩ����
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

	//�Ƿ��������ײ
	bool IsCollsion(tagSPOINT pt);
	bool IsCollsion(RECT rt);
	//�Ƿ��ھ�����
	bool IsInRect(RECT rt);
	bool IsOnRect(RECT rt);

	bool operator == (const POINT pt);
	tagSPOINT &operator =(const tagSPOINT pt);
}SPOINT;

#endif