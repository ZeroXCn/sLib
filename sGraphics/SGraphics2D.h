/**
* SGraphics2D��
* 2Dͼ�λ�����
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGraphics.h"
#ifndef _SGRAPHICS2D_H_
#define _SGRAPHICS2D_H_
class SGraphics2D :public SGraphics
{
public:
	SGraphics2D();
	SGraphics2D(HWND hWnd, HDC hDc = NULL);
	virtual ~SGraphics2D();
public:
	//��ά������ת�䣬��ת��������������š���ת����б�任��ƽ�Ʊ任��ͼ�Ρ�
	int SetWorldTransform(CONST XFORM *lpXform);
	XFORM GetWorldTransform();
	BOOL GetWorldTransform(LPXFORM lpXform);
	int RestoreWorldTransform(int nGraphicsMode = GM_COMPATIBLE);	//�ָ�����DC

	//��ת�ͻָ���ת
	int Rotate(int iAngle, int cx = 0, int cy = 0);
	int Rotate(double dTheta, int cx = 0, int cy = 0);
	int RotateFrom(int iAngle, int cx = 0, int cy = 0);
	int RotateFrom(double dTheta, int cx = 0, int cy = 0);

	//����
	int Scale(float sx, float sy);
	int ScaleFrom(float sx, float sy);

	//ƽ��
	int Offset(int cx, int cy);
	int OffsetFrom(int cx, int cy);

	//����
	int Shear(int sx, int sy);

	//����
	int Reflect(int cx, int cy);

	//����-����ĳֱ��
	int Mirror(int a, int b, int c);
	int MirrorX(int dX);
	int MirrorY(int dY);
	//����ĳ��Գ�
	int Symmetry(int cx, int cy);
};

#endif