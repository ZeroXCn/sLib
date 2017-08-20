#include "SBufferDc.h"

SBufferDc::SBufferDc(SDc sDC, int nWidth, int nHeight)
{
	m_outHdc = sDC.GetHandle();
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_hDC = ::CreateCompatibleDC(sDC.GetHandle());	//创建内存兼容设备环境

	//创建内存兼容位图
	m_newBitmap = ::CreateCompatibleBitmap(sDC.GetHandle(), nWidth, nHeight);
	m_oldBitmap = (HBITMAP)::SelectObject(m_hDC, m_newBitmap);

	//TODO:绘图操作
	m_fPaint = [=](SDc sdc){
		return ::BitBlt(m_outHdc, 0, 0, m_nWidth, m_nHeight, sdc.GetHandle(), 0, 0, SRCCOPY);
	};
	

}

SBufferDc::~SBufferDc()
{
	//释放资源
	::SelectObject(m_hDC, m_oldBitmap);
	::DeleteObject(m_newBitmap);
	::DeleteDC(m_hDC);
}

BOOL SBufferDc::OnPaint(SDc sdc)
{
	return m_fPaint(sdc);
}

void SBufferDc::OnPaint(std::function<BOOL(SDc)> fPaint)
{
	m_fPaint = fPaint;
}

BOOL SBufferDc::Paint(SDc sdc)
{
	//将内存设备环境中的内容绘制到物理设备环境
	return OnPaint(sdc);
}
BOOL SBufferDc::Paint()
{
	//将内存设备环境中的内容绘制到物理设备环境
	return OnPaint(SDc(m_hDC));

}


//
//设置获取来源DC
SDc SBufferDc::GetDcFrom()
{
	return m_outHdc;
}
void SBufferDc::SetDcFrom(SDc sDc)
{
	m_outHdc = sDc.GetHandle();
}