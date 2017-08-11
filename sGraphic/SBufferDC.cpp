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

	m_bEnabled = TRUE;
	//TODO:绘图操作

}

SBufferDc::~SBufferDc()
{
	//将内存设备环境中的内容绘制到物理设备环境
	if (m_bEnabled)::BitBlt(m_outHdc, 0, 0, m_nWidth, m_nHeight, m_hDC, 0, 0, SRCCOPY);
	//释放资源
	::SelectObject(m_hDC, m_oldBitmap);
	::DeleteObject(m_newBitmap);
	::DeleteDC(m_hDC);
}

void SBufferDc::SetEnabled(BOOL bEnable)
{
	m_bEnabled = bEnable;
}
BOOL SBufferDc::GetEnabled()
{
	return m_bEnabled;
}