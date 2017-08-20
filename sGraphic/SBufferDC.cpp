#include "SBufferDc.h"

SBufferDc::SBufferDc(SDc sDC, int nWidth, int nHeight)
{
	m_outHdc = sDC.GetHandle();
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_hDC = ::CreateCompatibleDC(sDC.GetHandle());	//�����ڴ�����豸����

	//�����ڴ����λͼ
	m_newBitmap = ::CreateCompatibleBitmap(sDC.GetHandle(), nWidth, nHeight);
	m_oldBitmap = (HBITMAP)::SelectObject(m_hDC, m_newBitmap);

	//TODO:��ͼ����
	m_fPaint = [=](SDc sdc){
		return ::BitBlt(m_outHdc, 0, 0, m_nWidth, m_nHeight, sdc.GetHandle(), 0, 0, SRCCOPY);
	};
	

}

SBufferDc::~SBufferDc()
{
	//�ͷ���Դ
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
	//���ڴ��豸�����е����ݻ��Ƶ������豸����
	return OnPaint(sdc);
}
BOOL SBufferDc::Paint()
{
	//���ڴ��豸�����е����ݻ��Ƶ������豸����
	return OnPaint(SDc(m_hDC));

}


//
//���û�ȡ��ԴDC
SDc SBufferDc::GetDcFrom()
{
	return m_outHdc;
}
void SBufferDc::SetDcFrom(SDc sDc)
{
	m_outHdc = sDc.GetHandle();
}