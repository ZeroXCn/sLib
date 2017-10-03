/**
* SRgn��
* GDI����-������
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"

#ifndef _SRGN_H_
#define _SRGN_H_
class SRgn :public SGdiHandle<HRGN,void*>
{
public:
	SRgn(HRGN hRgn=NULL);
	SRgn(SGdiObj Obj);
	virtual ~SRgn();
private:
	//�������ú���
	using SGdiHandle<HRGN, void*>::GetHandleStruct;
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