/**
* SPen��
* GDI����-������
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "SGdiHandle.h"

#ifndef _SPEN_H_
#define _SPEN_H_

class SPen :public SGdiHandle<HPEN, LOGPEN>
{
public:
	SPen(HPEN hPen=NULL);
	SPen(SGdiObj Obj);
	virtual ~SPen();

public:
	//ָ������ʽ����Ⱥ���ɫ��������
	BOOL Create(int nPenStyle, int nWidth, COLORREF crColor);

	//����ָ����LOGPEN�ṹ����
	BOOL CreateIndirect(LOGPEN lPen);

	//����һ����չ���ʣ�װ�λ򼸺Σ�
	/*	iPenStyle�ǻ��ʵ����͡�
		cWidth�ǻ��ʵĿ�ȣ�������װ�λ���ʱ���һ��Ҫ����Ϊ1��
		plbrush�ǻ��ʵ����ԡ�
		cStyle�Ǻ����Զ�����ʽ����ĸ�����
		pstyle���Զ�����ʽ���顣
	*/
	BOOL CreateEx(DWORD iPenStyle, DWORD cWidth, CONST LOGBRUSH *plbrush, DWORD cStyle, CONST DWORD *pstyle);
public:

};
#endif