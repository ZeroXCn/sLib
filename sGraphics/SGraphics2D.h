/**
* SGraphics2D类
* 2D图形绘制类
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
	//二维的线性转变，此转换可用于输出缩放、旋转、倾斜变换或平移变换的图形。
	int SetWorldTransform(CONST XFORM *lpXform);
	XFORM GetWorldTransform();
	BOOL GetWorldTransform(LPXFORM lpXform);
	int RestoreWorldTransform(int nGraphicsMode = GM_COMPATIBLE);	//恢复正常DC

	//旋转和恢复旋转
	int Rotate(int iAngle, int cx = 0, int cy = 0);
	int Rotate(double dTheta, int cx = 0, int cy = 0);
	int RotateFrom(int iAngle, int cx = 0, int cy = 0);
	int RotateFrom(double dTheta, int cx = 0, int cy = 0);

	//缩放
	int Scale(float sx, float sy);
	int ScaleFrom(float sx, float sy);

	//平移
	int Offset(int cx, int cy);
	int OffsetFrom(int cx, int cy);

	//错切
	int Shear(int sx, int sy);

	//反射
	int Reflect(int cx, int cy);

	//镜像-关于某直线
	int Mirror(int a, int b, int c);
	int MirrorX(int dX);
	int MirrorY(int dY);
	//关于某点对称
	int Symmetry(int cx, int cy);
};

#endif