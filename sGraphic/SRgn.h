/**
* SRgn��
* GDI����-������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiObject.h"
#ifndef _SRGN_H_
#define _SRGN_H_
class SRgn :public SGdiObject
{
public:
	SRgn();
	SRgn(SGdiObject Obj);
	SRgn(HRGN hRgn);
	virtual ~SRgn();
public:
	void SetHandle(HRGN hRgn);
	HRGN GetHandle();
public:
	//������Բ����
	BOOL CreateElliptic( int nLeft,  int nTop,  int nRight,  int nBottom);

	//����һ�������ض����ε���Բ����
	BOOL CreateElliptieIndirect(RECT lRect);

	//����һ����һϵ�е�Χ�ɵ�����
	BOOL CreatePolygon(POINT lPoints, int nCount, int nMode);

	//����һ�����ζ���
	BOOL CreateRect(int nLeft, int nTop, int nRight, int nBottom);

	//����һ�����ζ���
	BOOL CreateRectIndirect(RECT lRect);

public:
	//�������������Ϊһ��������
	int Combine(HRGN hrgnSrc1, HRGN hrgnSrc2, int nMode);

};

#endif