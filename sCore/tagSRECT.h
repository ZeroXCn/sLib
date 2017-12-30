/**
* tagSRECT�ṹ��
* ����
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
	//ȡ�����
	int GetArea();
	//ȡ���ܳ�
	int GetPerimeter();
	//ȡ�ü�������
	POINT GetCenter();
	//�������ƶ�����
	void Move(int x, int y);
	//�ƶ���ָ�����ε�����
	void MoveToCenter(RECT rt);
	//�����Ƿ���ײ
	bool IsCollision(tagSRECT rt);
	bool IsCollision(RECT rt,RECT *out);

	//�Ƿ��ھ�����
	bool IsInRect(tagSRECT rt);

	bool operator ==(tagSRECT rt);
	tagSRECT &operator =(tagSRECT rt);
}SRECT;

#endif