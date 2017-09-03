/**
* SPoint2��
* ��ѧ����-Rect
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
	SRect(const SRect &or);	//����������,�������õ�ֵ�ᷢ������
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
	
	//���ƾ���
	void CopyRect(const SRect &rt);
	//�������ƶ�����
	void MoveRect(_T x, _T y);
	//�������δ�С
	void ExpandRect(_T width, _T height);
	//���þ��δ�С
	void SetSize(_T width, _T height);


	bool operator ==(const SRect &rt);
	//���帳ֵ�������
	SRect  & operator   =(const SRect &rt);


};
#endif