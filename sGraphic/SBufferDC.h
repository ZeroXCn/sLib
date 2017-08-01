/**
* SBuffer��
* SDc������-��˫����,
* @author ZeroX
* @version v1.0 25/07/2017
*/

#ifndef _SBUFFERDC_H_
#define _SBUFFERDC_H_
#include "SDc.h"

class SBufferDc:public SDc
{
	friend class SDc;
protected:
	HDC m_outHdc;			//�ⲿHDC
	HBITMAP m_newBitmap;	//����λͼ
	HBITMAP m_oldBitmap;	//��λͼ
	int m_nWidth, m_nHeight;//���
	BOOL m_bEnabled;		//�Ƿ�����
public:
	void SetEnabled(BOOL bEnable);
	BOOL GetEnabled();
public:
	SBufferDc(SDc sdc,int nWidth,int nHeight);
	virtual ~SBufferDc();
};

#endif