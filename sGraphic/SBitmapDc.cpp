#include "SBitmapDc.h"
SBitmapDc::SBitmapDc()
{
	m_pBits = NULL;
}

SBitmapDc::~SBitmapDc()
{
	Delete();
}
////////////////////
HDC SBitmapDc::GetSafeHdc()
{
	return SDc::GetHandle();
}
HBITMAP SBitmapDc::GetBmpHandle()
{
	return SBitmap::GetHandle();
}

DWORD *SBitmapDc::GetBits()
{
	return (DWORD*)m_pBits;
}

/////////////////
void SBitmapDc::Create(int nWidth, int nHeight)
{
	BITMAPINFOHEADER bih;
	memset(&bih, 0, sizeof(BITMAPINFOHEADER));
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = ((((int)nWidth * 8) + 31) & ~31) >> 3;
	bih.biHeight = nHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 32;
	bih.biCompression = BI_RGB;
	SBitmap::SetHandle(NULL);
	SDc::CreateCompatibleDC(NULL);
	SBitmap::CreateDIBSection(
		GetSafeHdc(), (BITMAPINFO*)&bih,
		DIB_RGB_COLORS, (void**)(&m_pBits), NULL, 0);
	SDc::SelectObject((*(SBitmapDc *)this));

}

void SBitmapDc::Delete()
{
	if (SBitmap::GetHandle())
		SBitmap::Delete();
	if (SDc::GetHandle())
		SDc::DeleteDC();
}