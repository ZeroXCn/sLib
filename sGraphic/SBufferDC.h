/**
* SBuffer��
* SDc������-��˫����,
* @author ZeroX
* @version v1.0 25/07/2017
*/

#ifndef _SBUFFERDC_H_
#define _SBUFFERDC_H_
#include "SDc.h"
#include <functional>

class SBufferDc:public SDc
{
	friend class SDc;
protected:
	HDC m_outHdc;			//�ⲿHDC
	HBITMAP m_newBitmap;	//����λͼ
	HBITMAP m_oldBitmap;	//��λͼ
	int m_nWidth, m_nHeight;//���

	std::function<BOOL(SDc,SDc)> m_fPaint;

protected:
	//��д����
	virtual BOOL OnPaint(SDc src, SDc from);
public:
	//����
	void OnPaint(std::function<BOOL(SDc, SDc)> fPaint);
	BOOL Paint(SDc src, SDc from);
	BOOL Paint();
public:
	//���û�ȡ��ԴDC
	SDc GetDcFrom();
	void SetDcFrom(SDc sDc);

public:
	SBufferDc(SDc sdc,int nWidth,int nHeight);
	virtual ~SBufferDc();
};

#endif