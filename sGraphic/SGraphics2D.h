/**
* SGraphics2D��
* ͼ����Ⱦ����ǿ��
* @author ZeroX
* @version v1.0 21/07/2017
*/
#include "SGraphics.h"

#ifndef _SGRAPHIC2D_H_
#define _SGRAPHIC2D_H_


class SGraphics2D :public SGraphics
{
public:
	//��ת����ϵ
	void Rotate(double theta);
	void Rotate(double theta, double x, double y);
};

#endif