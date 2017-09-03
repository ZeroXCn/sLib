/**
* SBuffer类
* SDc缓冲类-开双缓存,
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
	HDC m_outHdc;			//外部HDC
	HBITMAP m_newBitmap;	//缓冲位图
	HBITMAP m_oldBitmap;	//旧位图
	int m_nWidth, m_nHeight;//宽高

	std::function<BOOL(SDc,SDc)> m_fPaint;

protected:
	//重写绘制
	virtual BOOL OnPaint(SDc src, SDc from);
public:
	//绘制
	void OnPaint(std::function<BOOL(SDc, SDc)> fPaint);
	BOOL Paint(SDc src, SDc from);
	BOOL Paint();
public:
	//设置获取来源DC
	SDc GetDcFrom();
	void SetDcFrom(SDc sDc);

public:
	SBufferDc(SDc sdc,int nWidth,int nHeight);
	virtual ~SBufferDc();
};

#endif