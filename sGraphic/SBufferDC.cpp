#include "SBufferDc.h"

SBufferDc::SBufferDc(SDc sDC, int nWidth, int nHeight)
{
	m_outHdc = sDC.GetHandle();
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_hDC = ::CreateCompatibleDC(sDC.GetHandle());	//�����ڴ�����豸����

	//�����ڴ����λͼ
	/* TODO:�˴�������BITMAPĬ��Ϊ��ɫ */
	m_newBitmap = ::CreateCompatibleBitmap(sDC.GetHandle(), nWidth, nHeight);
	m_oldBitmap = (HBITMAP)::SelectObject(m_hDC, m_newBitmap);

	//TODO:��ͼ����
	m_fPaint = [=](SDc src, SDc from){
		return ::BitBlt(from.GetHandle(), 0, 0, m_nWidth, m_nHeight, src.GetHandle(), 0, 0, SRCCOPY);
	};
	

}

SBufferDc::~SBufferDc()
{
	//�ͷ���Դ
	::SelectObject(m_hDC, m_oldBitmap);
	::DeleteObject(m_newBitmap);
	::DeleteDC(m_hDC);
}

BOOL SBufferDc::OnPaint(SDc src, SDc from)
{
	return m_fPaint(src,from);
}

void SBufferDc::OnPaint(std::function<BOOL(SDc, SDc)> fPaint)
{
	m_fPaint = fPaint;
}

BOOL SBufferDc::Paint(SDc src, SDc from)
{
	//���ڴ��豸�����е����ݻ��Ƶ������豸����
	return OnPaint(src,from);
}
BOOL SBufferDc::Paint()
{
	//���ڴ��豸�����е����ݻ��Ƶ������豸����
	return OnPaint(SDc(m_hDC), SDc(m_outHdc));

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