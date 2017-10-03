#include "SGraphics2D.h"
SGraphics2D::SGraphics2D()
{

}

SGraphics2D::SGraphics2D(HWND hWnd, HDC hDc)
:SGraphics(hWnd,hDc)
{

}
SGraphics2D::~SGraphics2D()
{

}
//////////////
int SGraphics2D::SetWorldTransform(CONST XFORM *lpXform)
{
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	::SetWorldTransform(m_hDC, lpXform);
	return nGraphicsMode;
}

XFORM SGraphics2D::GetWorldTransform()
{
	XFORM Xform;
	::GetWorldTransform(m_hDC, &Xform);
	return Xform;
}

BOOL SGraphics2D::GetWorldTransform(LPXFORM lpXform)
{
	return ::GetWorldTransform(m_hDC, lpXform);
}

int SGraphics2D::RestoreWorldTransform(int nGraphicsMode)
{
	//��λ����,��ȱ仯
	XFORM xform;
	xform.eM11 = (float)1.0;
	xform.eM12 = (float)0;
	xform.eM21 = (float)0;
	xform.eM22 = (float)1.0;
	xform.eDx = (float)0;
	xform.eDy = (float)0;

	SetWorldTransform(&xform);
	return ::SetGraphicsMode(m_hDC,nGraphicsMode);
}

// ��DC��תһ���ĽǶ�  
int SGraphics2D::Rotate(double dTheta, int cx, int cy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;

	//��ת����
	double fangle = dTheta; //(double)iAngle / 180. * 3.1415926;

	xform.eM11 = (float)cos(fangle);
	xform.eM12 = (float)sin(fangle);
	xform.eM21 = (float)-sin(fangle);
	xform.eM22 = (float)cos(fangle);
	xform.eDx = (float)(cx - cos(fangle)*cx + sin(fangle)*cy);
	xform.eDy = (float)(cy - cos(fangle)*cy - sin(fangle)*cx);

	SetWorldTransform(&xform);

	return nGraphicsMode;
}
int SGraphics2D::Rotate(int iAngle, int cx, int cy)
{
	return Rotate((double)((double)iAngle / 180.f * 3.1415926), cx, cy);
}

int SGraphics2D::RotateFrom(int iAngle, int cx, int cy)
{
	return RotateFrom((double)((double)iAngle / 180.f * 3.1415926), cx, cy);
}
int SGraphics2D::RotateFrom(double dTheta, int cx, int cy)
{

	XFORM xOldform;
	double OldTheta;
	GetWorldTransform(&xOldform);
	OldTheta = acos(xOldform.eM11);	//ȡ��֮ǰDC��ԭ�Ƕ�
	return Rotate(OldTheta + dTheta, cx, cy);
}


int SGraphics2D::Scale(float sx, float sy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;
	//ƽ�ƾ���
	xform.eM11 = (float)sx;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)sy;
	xform.eDx = (float)0.f;
	xform.eDy = (float)0.f;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}
int SGraphics2D::ScaleFrom(float sx, float sy)
{
	XFORM xOldform;
	GetWorldTransform(&xOldform);
	sx *= xOldform.eM11; sy *= xOldform.eM22;
	return Scale(sx, sy);
}


int SGraphics2D::Offset(int cx, int cy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;
	//ƽ�ƾ���
	xform.eM11 = (float)1.f;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)1.f;
	xform.eDx = (float)cx;
	xform.eDy = (float)cy;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

int SGraphics2D::OffsetFrom(int cx, int cy)
{
	XFORM xOldform;
	GetWorldTransform(&xOldform);
	cx += (int)xOldform.eDx; cy += (int)xOldform.eDy;
	return Offset(cx, cy);
}

//����
int SGraphics2D::Shear(int sx, int sy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;
	//���о���
	xform.eM11 = (float)1.f;
	xform.eM12 = (float)sx;
	xform.eM21 = (float)sy;
	xform.eM22 = (float)1.f;
	xform.eDx = (float)0;
	xform.eDy = (float)0;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}

//����
int SGraphics2D::Reflect(int cx, int cy)
{
	return Scale((float)(cx >= 0 ? 1 : -1), (float)(cy >= 0 ? 1 : -1));
}

//����
int SGraphics2D::Mirror(int a, int b, int c)
{
	float nDen = (float)a*a + b*b;
	if (nDen == 0.f)
		return ::GetGraphicsMode(m_hDC);

	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;
	//�������
	xform.eM11 = (float)(nDen - 2 * a*a) / nDen;
	xform.eM12 = (float)(-2 * a * b) / nDen;
	xform.eM21 = (float)(-2 * a * b) / nDen;
	xform.eM22 = (float)(nDen - 2 * b*b) / nDen;
	xform.eDx = (float)(-2 * a * c) / nDen;
	xform.eDy = (float)(-2 * b * c) / nDen;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}


int SGraphics2D::MirrorX(int dX)
{
	return Mirror(1, 0, -dX);		//��Ϊ��׼ʽ�� c=-dx
}

int SGraphics2D::MirrorY(int dY)
{
	return Mirror(0, 1, -dY);
}

int SGraphics2D::Symmetry(int cx, int cy)
{
	//Ϊָ�����豸��������ͼ��ģʽ
	int nGraphicsMode = ::SetGraphicsMode(m_hDC, GM_ADVANCED);
	XFORM xform;
	//�Գƾ���
	xform.eM11 = (float)-1.f;
	xform.eM12 = (float)0.f;
	xform.eM21 = (float)0.f;
	xform.eM22 = (float)-1.f;
	xform.eDx = (float)2 * cx;
	xform.eDy = (float)2 * cy;

	SetWorldTransform(&xform);

	return nGraphicsMode;
}