#include "SBufferDc.h"

SBufferDc::SBufferDc(HDC hDC, int nWidth, int nHeight)
{
	m_outHdc = hDC;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_hDC = ::CreateCompatibleDC(hDC);	//�����ڴ�����豸����

	//�����ڴ����λͼ
	m_newBitmap = ::CreateCompatibleBitmap(hDC, nWidth, nHeight);
	m_oldBitmap = (HBITMAP)::SelectObject(m_hDC, m_newBitmap);

	m_bEnabled = TRUE;
	//TODO:��ͼ����

}

SBufferDc::~SBufferDc()
{
	//���ڴ��豸�����е����ݻ��Ƶ������豸����
	if (m_bEnabled)::BitBlt(m_outHdc, 0, 0, m_nWidth, m_nHeight, m_hDC, 0, 0, SRCCOPY);
	//�ͷ���Դ
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