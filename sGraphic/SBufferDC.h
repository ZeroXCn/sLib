/**
* SBuffer类
* SDc缓冲类-开双缓存,
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
	HDC m_outHdc;			//外部HDC
	HBITMAP m_newBitmap;	//缓冲位图
	HBITMAP m_oldBitmap;	//旧位图
	int m_nWidth, m_nHeight;//宽高
	BOOL m_bEnabled;		//是否启用
public:
	void SetEnabled(BOOL bEnable);
	BOOL GetEnabled();
public:
	SBufferDc(SDc sdc,int nWidth,int nHeight);
	virtual ~SBufferDc();
};

#endif