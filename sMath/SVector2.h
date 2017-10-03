/**
* SPoint2��
* ��ѧ����-Vector
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

	/* ���������� */
	//ȡ������ģ
	_T Module();
	_T Length();
	//ȡ������б��
	_T Slope();
	//�淶��
	SVector2 &Normalize();

	/* ���������� */
	//�������н�
	_T Angle(const SVector2 &vt);


	//�������
	_T Dot(const SVector2 &vt);
	//���ֵ
	_T Cross(const SVector2 &vt);
	
	//�������-ƽ��������˽��Ϊ��ֱƽ���һ������,�ڶ�ά�б���Ϊ(0,0)
	SVector2 CrossVec(const SVector2 &vt);

	//�Ƿ�ƽ��
	bool IsParallel(const SVector2 &vt);
	//�Ƿ�ֱ
	bool IsVertical(const SVector2 &vt);


	/* �������Բ��� */
	void SetVector(_T x, _T y);
	bool Equals(SVector2 &vt);
	
	bool operator ==(const SVector2 &vt);
	//���帳ֵ�������
	SVector2  & operator   =(const SVector2 &vt);
	//����ӷ��������
	SVector2  operator	+(const SVector2 &vt);
	//������������-
	SVector2  operator	-(const SVector2 &vt);

	SVector2  &operator	+=(const SVector2 &vt);
	//������������-
	SVector2  &operator	-=(const SVector2 &vt);

	//������������*
	SVector2  operator	*(const _T s);
	SVector2  &operator	*=(const _T s);

	//������������/
	SVector2  operator	/(const _T s);
	SVector2  &operator	/=(const _T s);

	SVector2(_T x = 0, _T y = 0);

};

#endif