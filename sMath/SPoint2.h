/**
* SPoint2��
* ��ѧ����-Point
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

	/* ������� */
	_T Distance(const SPoint2 &pt);		//ȡ�þ���
	bool Equals(SPoint2 pt);			//�Ƚ�

	//���Բ���
	_T GetPointX();
	_T GetPointY();
	void SetPoint(_T x, _T y);		//��������
	void MovePoint(_T x, _T y);		//�ƶ�����

	bool operator ==(const SPoint2 &pt);//���帳ֵ�������
	SPoint2  &operator   =(const SPoint2 &pt);
	SPoint2  operator	+(const SPoint2 &pt);

	//�����������ӦΪ����
	SPoint2  operator	-(const SPoint2 &pt);

	SPoint2  &operator	+=(const SPoint2 &pt);
	SPoint2  &operator	-=(const SPoint2 &pt);//������������-

	//�˷�
	SPoint2  operator	*(const double k);
	SPoint2  &operator	*=(const double k);
	//����
	SPoint2  operator	/(const double k);
	SPoint2  &operator	/=(const double k);

	SPoint2(_T x = 0, _T y = 0);
};

#endif
