#include "SBitmap.h"

SBitmap::SBitmap(SGdiObj Obj)
{
	m_hGdiObj = (HBITMAP)Obj.GetHandle();
}

SBitmap::SBitmap(HBITMAP hBitmap)
:SGdiHandle<HBITMAP, BITMAP>(hBitmap)
{
	
}
SBitmap::~SBitmap()
{
	
}

////////////
//ȡ��,����λͼ��
int SBitmap::GetWidth()
{
	return GetSize().cx;
}


//ȡ��,����λͼ��
int SBitmap::GetHeight()
{
	return GetSize().cy;
}

SIZE SBitmap::GetSize()
{
	SIZE size{ 0, 0 };

	BITMAP bit = GetHandleStruct();
	size.cx = bit.bmWidth;
	size.cy = bit.bmHeight;
	
	return size;
}
void SBitmap::SetSize(int nWidth, int nHeight)
{
	::SetBitmapDimensionEx((HBITMAP)m_hGdiObj, nWidth, nHeight,NULL);
}
////////////
BOOL SBitmap::Create(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPeral, CONST VOID *lpvBits)
{
	m_hGdiObj = (HBITMAP)::CreateBitmap(nWidth, nHeight, cPlanes, cBitsPeral, lpvBits);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBitmap::CreateCompatible(HDC hdc, int nWidth, int nHeight)
{
	m_hGdiObj = (HBITMAP)::CreateCompatibleBitmap(hdc, nWidth, nHeight);
	return (m_hGdiObj ? TRUE : FALSE);
}

BOOL SBitmap::CreateIndirect(CONST BITMAP *lpbm)
{
	m_hGdiObj = (HBITMAP)::CreateBitmapIndirect(lpbm);
	return (m_hGdiObj ? TRUE : FALSE);
}


BOOL SBitmap::CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT iUsage, VOID** ppvBits, HANDLE hSection, DWORD dwOffset)
{
	m_hGdiObj = (HBITMAP)::CreateDIBSection(hdc, pbmi, iUsage, ppvBits, hSection, dwOffset);
	return (m_hGdiObj ? TRUE : FALSE);
}

//����Դ�м���λͼ
BOOL SBitmap::Load(UINT uRcid, HINSTANCE hInstance)
{
	
	m_hGdiObj = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(uRcid), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	 return m_hGdiObj ? TRUE : FALSE;
}

//���ļ��м���λͼ
BOOL SBitmap::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	m_hGdiObj = (HBITMAP)::LoadImage(hInstance, lpFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	return m_hGdiObj ? TRUE : FALSE;
}

//���ڴ��м���
BOOL SBitmap::Load(void *pMemory, int nLength)
{
	//ժ��http://blog.csdn.net/ccd1230102/article/details/2845646
	BITMAPFILEHEADER *pbmfh = (BITMAPFILEHEADER *)pMemory;
	//���豸�޹ص�λͼ��DIB��
	m_hGdiObj = (HBITMAP) ::CreateDIBitmap(
		::GetDC(NULL),					//TODO : �������岻��,���ڴ��м���Ϊ����Ҫ DC ?
		(BITMAPINFOHEADER *)(pbmfh + 1),
		CBM_INIT,
		(BYTE *)pbmfh + pbmfh->bfOffBits,
		(BITMAPINFO *)(pbmfh + 1),
		DIB_RGB_COLORS);
	//BITMAPINFOHEADER *pbminfohead = (BITMAPINFOHEADER *)(pbmfh + 1);

	return m_hGdiObj ? TRUE : FALSE;
}


//��λͼ�б����ļ�
BOOL SBitmap::Save(LPTSTR lpFileName)
{
	//ժ��http://blog.csdn.net/kaixiang54/article/details/7606598

	HBITMAP hBm = (HBITMAP)m_hGdiObj;
	//  ����λͼ�ļ���ͷ  
	BITMAPFILEHEADER bmfh;
	//  ����λͼ��Ϣ��ͷ  
	BITMAPINFOHEADER bmih;

	//  ��ɫ�峤��  
	int nColorLen = 0;
	//  ��ɫ���С  
	DWORD dwRgbQuadSize = 0;
	//  λͼ��С  
	DWORD dwBmSize = 0;
	//  �����ڴ��ָ��  
	HGLOBAL hMem = NULL;
	LPBITMAPINFOHEADER  lpbi;
	BITMAP bm;
	HDC hDC;
	HANDLE hFile = NULL;
	DWORD dwWritten;

	::GetObject(hBm, sizeof(BITMAP), &bm);

	bmih.biSize = sizeof(BITMAPINFOHEADER); // ���ṹ��ռ���ֽ�  
	bmih.biWidth = bm.bmWidth;           // λͼ��  
	bmih.biHeight = bm.bmHeight;          // λͼ��  
	bmih.biPlanes = 1;
	bmih.biBitCount = bm.bmBitsPixel;   // ÿһͼ�ص�λ��  
	bmih.biCompression = BI_RGB;           // ��ѹ��  
	bmih.biSizeImage = 0;  //  λͼ��С  
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;

	//  ����λͼͼ����������С   
	dwBmSize = 4 * ((bm.bmWidth * bmih.biBitCount + 31) / 32) * bm.bmHeight;

	//  ���ͼ��λ <= 8bit�����е�ɫ��  
	if (bmih.biBitCount <= 8)
	{
		nColorLen = (1 << bm.bmBitsPixel);
	}

	//  �����ɫ���С  
	dwRgbQuadSize = nColorLen * sizeof(RGBQUAD);

	//  �����ڴ�  
	hMem = GlobalAlloc(GHND, dwBmSize + dwRgbQuadSize + sizeof(BITMAPINFOHEADER));

	if (NULL == hMem)
	{
		return FALSE;
	}

	//  �����ڴ�  
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hMem);

	//  ��bmih�е�����д�������ڴ���  
	*lpbi = bmih;

	hDC = GetDC(NULL);

	//  ��λͼ�е�������bits����ʽ����lpData�С�  
	::GetDIBits(hDC, hBm, 0, (DWORD)bmih.biHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwRgbQuadSize, (BITMAPINFO *)lpbi, (DWORD)DIB_RGB_COLORS);

	bmfh.bfType = 0x4D42;  // λͼ�ļ����ͣ�BM  
	bmfh.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwRgbQuadSize + dwBmSize;  // λͼ��С  
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwRgbQuadSize;  // λͼ�������ļ�ͷ����ƫ����  

	//  �����������д���ļ���  

	hFile = ::CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	//  д��λͼ�ļ�ͷ  
	::WriteFile(hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER), (DWORD *)&dwWritten, NULL);
	//  д��λͼ����  
	::WriteFile(hFile, (LPBITMAPINFOHEADER)lpbi, bmfh.bfSize - sizeof(BITMAPFILEHEADER), (DWORD *)&dwWritten, NULL);

	::GlobalFree(hMem);
	::CloseHandle(hFile);

	return TRUE;
}

//////////
BOOL SBitmap::BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop)
{
	return ::BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
}

BOOL SBitmap::BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc , DWORD dwRop )
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = BitBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcMem, nXSrc, nYSrc, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;

}

BOOL SBitmap::BitBlt(HDC hdcDest, int nXDest, int nYDest, DWORD dwRop)
{
	SIZE size = GetSize();
	return BitBlt(hdcDest, nXDest, nYDest, size.cx, size.cy, 0, 0, dwRop);
}

BOOL SBitmap::PatBlt(HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop)
{
	return ::PatBlt(hdc, nXLeft, nYLeft, nWidth, nHeight, dwRop);
}

BOOL SBitmap::PlgBlt(HDC hdcDest, CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask)
{
	return ::PlgBlt(hdcDest, lpPoint, hdcSrc, nXSrc, nYSrc, nWidth,  nHeight, hbmMask, xMask, yMask);
}

BOOL SBitmap::StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	return ::StretchBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);
}

BOOL SBitmap::StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = StretchBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcMem, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	return ::MaskBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, hbmMask, xMask, yMask, dwRop);
}

BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = MaskBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcMem, nXSrc, nYSrc, hbmMask, xMask, yMask, dwRop);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}
BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, DWORD dwRop)
{
	return MaskBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, nXSrc, nYSrc, hbmMask, nXSrc, nYSrc, dwRop);
}

BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	return MaskBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, 0, 0, hbmMask, xMask, yMask, dwRop);
}

BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, DWORD dwRop)
{
	return MaskBlt(hdcDest, nXDest, nYDest, nWidth, nHeight, 0, 0, hbmMask, 0, 0, dwRop);

}
BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop)
{
	SIZE size = GetSize();
	return MaskBlt(hdcDest, nXDest, nYDest, size.cx, size.cy, xMask, yMask, hbmMask, xMask, yMask, dwRop);
}
BOOL SBitmap::MaskBlt(HDC hdcDest, int nXDest, int nYDest, HBITMAP hbmMask, DWORD dwRop)
{
	SIZE size = GetSize();
	return MaskBlt(hdcDest, nXDest, nYDest, size.cx, size.cy, 0, 0, hbmMask, 0, 0, dwRop);

}


BOOL SBitmap::TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	return ::TransparentBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent);
}
BOOL SBitmap::TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = TransparentBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcMem, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}

BOOL SBitmap::TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, UINT crTransparent)
{
	SIZE size = GetSize();
	return TransparentBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, 0, 0, size.cx, size.cy, crTransparent);
}
BOOL SBitmap::TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, UINT crTransparent )
{
	SIZE size = GetSize();
	return TransparentBlt(hdcDest, nXOriginDest, nYOriginDest, size.cx, size.cy, 0, 0, size.cx, size.cy, crTransparent);
}

BOOL SBitmap::AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction)
{
	return ::AlphaBlend(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, blendFunction);
}
BOOL SBitmap::AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	BOOL result = AlphaBlend(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcMem, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, blendFunction);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);

	return result;
}
BOOL SBitmap::AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, BLENDFUNCTION blendFunction)
{
	SIZE size = GetSize();
	return AlphaBlend(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, 0, 0, size.cx, size.cy, blendFunction);
}
BOOL SBitmap::AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, BLENDFUNCTION blendFunction)
{
	SIZE size = GetSize();
	return AlphaBlend(hdcDest, nXOriginDest, nYOriginDest, size.cx, size.cy, 0, 0, size.cx, size.cy, blendFunction);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* ��hDC��ָ��λ��(x,y)���͸����ΪnAlpha(0~255)�İ�͸��ͼ�� */
void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{

		//����bf�ṹ
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = nAlpha;
		bf.AlphaFormat = 0x00;

		//�����͸��ͼ��
		AlphaBlend(hdcDest, nXOriginDest, nYOriginDest ,nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, bf);

}

void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{
	//����bf�ṹ
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = nAlpha;
	bf.AlphaFormat = 0x00;

	//�����͸��ͼ��
	AlphaBlend(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, bf);

}
void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nAlpha)
{
	SIZE size = GetSize();
	return DrawAlpha(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, 0, 0, size.cx, size.cy, nAlpha);
}
void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nAlpha)
{
	SIZE size = GetSize();
	return DrawAlpha(hdcDest, nXOriginDest, nYOriginDest, size.cx, size.cy, 0, 0, size.cx, size.cy, nAlpha);
}


/*���ƻҶ��ο�ͼ*/
void SBitmap::DrawGray(HDC hDC, int x, int y, BOOL bTrans, COLORREF crTrans)
{

	HDC hdcMem = ::CreateCompatibleDC(hDC);		//���������豸

	BITMAP  bm;
	::GetObject((HBITMAP)m_hGdiObj, sizeof(BITMAP), &bm);
	BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //�����ݴ�����
	::GetBitmapBits((HBITMAP)m_hGdiObj, bm.bmHeight*bm.bmWidthBytes, px); //ȡ��Դλͼ�����ص�� RGB ֵ���� px ������


	int pb = bm.bmBitsPixel / 8;
	//ѭ������Ҷ�ֵ
	for (int dy = 0; dy<bm.bmHeight; dy++)
	{
		for (int dx = 0; dx<bm.bmWidth; dx++)
		{
			int rgb_b = dy*bm.bmWidthBytes + dx*pb;
			px[rgb_b] = (px[rgb_b] * 299 + px[rgb_b + 1] * 587 + px[rgb_b + 2] * 114) / 1000;
			px[rgb_b + 1] = px[rgb_b];
			px[rgb_b + 2] = px[rgb_b];
		};
	}
	//������ʱλͼ���Դ洢�Ҷ�ͼ��
	HBITMAP	hbmTmp = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);
	::SetBitmapBits(hbmTmp, bm.bmHeight*bm.bmWidthBytes, px);

	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbmTmp);

	if (bTrans)
		//���͸��λͼ
		::TransparentBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, crTrans);
	else
		//�����͸��λͼ
		::BitBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);



	delete[] px;		//ɾ������

	SelectObject(hdcMem, hOldBmp);
	DeleteObject(hbmTmp);
	DeleteDC(hdcMem);				//ɾ�������豸
	
}

/*���ư�͸���ο�ͼ*/
void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, HDC hdcSrc, int nXFore, int nYFore, int nWidthFore, int nHeightFore, int nAlpha, COLORREF crTrans)
{
	if (nAlpha >0)
	{
		//����һ���뱳��ͬ����С����ʱͼ��	
		RECT rBackRect = { nXBack, nYBack, nWidthBack, nHeightBack };
		HBITMAP	hbmTmp = ::CreateCompatibleBitmap(hdcBack, nWidthBack, nHeightBack);

		HBITMAP hbmBk = (HBITMAP)::SelectObject(hdcBack, hbmTmp);	//�������ͼ��

		RECT rForeRect = { nXFore, nYFore, nXFore + nWidthFore, nYFore + nHeightFore };
		RECT rTransRect, rTransRect2;

		//��ȡǰ�������뱳�����εĽ���,�粻�ཻ������Ҫ������ɫ���� 
		if (::IntersectRect(&rTransRect, &rBackRect, &rForeRect))
		{
			BITMAP  bm, bmBk;
			::GetObject((HBITMAP)m_hGdiObj, sizeof(BITMAP), &bm);
			BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //�����ݴ�����
			::GetBitmapBits((HBITMAP)m_hGdiObj, bm.bmHeight*bm.bmWidthBytes, px); //ȡ��Դλͼ�����ص�� RGB ֵ���� px ������

			::GetObject(hbmBk, sizeof(BITMAP), &bmBk);
			BYTE * pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];  //�����ݴ�����

			::GetBitmapBits(hbmBk, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk); //ȡ��Դλͼ�����ص�� RGB ֵ���� pxBk������

			rTransRect2 = rTransRect;
			::OffsetRect(&rTransRect2, -rForeRect.left, -rForeRect.top);	//ƫ�ƾ�������

			int pb = bm.bmBitsPixel / 8;		//��ȡÿ������ռ�ֽ���
			int pbBk = bmBk.bmBitsPixel / 8;

			//dy1Ϊ����ͼ��������,dy2Ϊǰ��ͼ��������
			//dx1Ϊ����ͼ��������,dx2Ϊǰ��ͼ��������
			int dx1, dx2, dy1, dy2;
			//ѭ�������ؽ��м��㣬������ǰ������Ҫ���м�������طֱ��ڸ��Զ�Ӧ�ľ���rTransRect��rTransRect2�ķ�Χ��ѭ�� 
			for (dy1 = rTransRect.top, dy2 = rTransRect2.top; dy1<rTransRect.bottom; dy1++, dy2++)
			for (dx1 = rTransRect.left, dx2 = rTransRect2.left; dx1<rTransRect.right; dx1++, dx2++)
			{
				int nBackRGB_B = dy1*bmBk.bmWidthBytes + dx1*pbBk;		//���㱳��ͼ������ʼλ��
				int nForeRGB_B = dy2*bm.bmWidthBytes + dx2*pb;			//����ǰ��ͼ������ʼλ��

				if (RGB(px[nForeRGB_B + 2], px[nForeRGB_B + 1], px[nForeRGB_B]) != crTrans)
				{
					pxBk[nBackRGB_B] = (px[nForeRGB_B] * nAlpha + pxBk[nBackRGB_B] * (255 - nAlpha)) / 255;	//��Bɫ��ֵ����nAlpha���� px ���
					pxBk[nBackRGB_B + 1] = (px[nForeRGB_B + 1] * nAlpha + pxBk[nBackRGB_B + 1] * (255 - nAlpha)) / 255;//�� G ɫ��ֵ����nAlpha���� px ���
					pxBk[nBackRGB_B + 2] = (px[nForeRGB_B + 2] * nAlpha + pxBk[nBackRGB_B + 2] * (255 - nAlpha)) / 255;//�� R ɫ��ֵ���� nAlpha���� px ���
				}
			}

			::SetBitmapBits(hbmTmp, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk); //���ñ���ͼ����
			HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcSrc, hbmTmp);
			::BitBlt(hdcBack, 0, 0, rBackRect.right, rBackRect.bottom, hdcSrc, 0, 0, SRCCOPY);

			delete[] px;		//ɾ������
			delete[] pxBk;
			::SelectObject(hdcSrc, hbmOld);
		}

		::DeleteObject(hbmTmp);

	}
}

void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nWidthFore, int nHeightFore, int nAlpha, COLORREF crTrans)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcBack);		//���������豸
	DrawTransAlpha(hdcBack, nXBack, nYBack, nWidthBack, nHeightBack, hdcMem, nXFore, nYFore, nWidthFore, nHeightFore, crTrans);
	::DeleteDC(hdcMem);

}
void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nAlpha , COLORREF crTrans )
{
	SIZE size = GetSize();
	DrawTransAlpha(hdcBack, nXBack, nYBack, nWidthBack, nHeightBack, 0, 0, size.cx, size.cy, crTrans);
}
void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nAlpha, COLORREF crTrans)
{
	SIZE size = GetSize();
	DrawTransAlpha(hdcBack, nXBack, nYBack, size.cx, size.cy, 0, 0, size.cx, size.cy, crTrans);
}


/* ����͸���ο�λͼ */
void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest,
	HDC hdcSrc, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans)
{
	// ��������λͼ
	HBITMAP hbmTmp = ::CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);
	// ������ɫλͼ
	HBITMAP hbmMask = ::CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
	//���������豸����
	HDC		hdcMem = ::CreateCompatibleDC(hdcDest);
	HDC		hdcMask = ::CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)::SelectObject(hdcMask, hbmMask);

	// ��ԴDC�е�λͼ��������ʱ�豸������
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		::BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	else
		::StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest,
		hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// ����͸��ɫ
	::SetBkColor(hdcMem, crTrans);

	// ����͸������Ϊ��ɫ����������Ϊ��ɫ���ɰ�λͼ
	::BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);

	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	::SetBkColor(hdcMem, RGB(0, 0, 0));
	::SetTextColor(hdcMem, RGB(255, 255, 255));
	::BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// ͸�����ֶ�Ӧ�ı������ֲ��䣬�������ֱ�ɺ�ɫ
	::SetBkColor(hdcDest, RGB(255, 255, 255));
	::SetTextColor(hdcDest, RGB(0, 0, 0));
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// "��"����,��������Ч��
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	// ������ʱ���ݣ��ͷ���Դ
	::SelectObject(hdcMem, hbmOld);
	::DeleteDC(hdcMem);
	::SelectObject(hdcMask, hbmMaskOld);
	::DeleteDC(hdcMask);
	::DeleteObject(hbmTmp);
	::DeleteObject(hbmMask);
}

void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//���������豸
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//��λͼѡ������豸������¼�¾ɵľ��

	DrawTransBitmap(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, nXSrc, nYSrc, nWidthSrc, nHeightSrc, crTrans);

	::SelectObject(hdcMem, hOldBmp);
	::DeleteObject(hOldBmp);
	::DeleteDC(hdcMem);
}
void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, COLORREF crTrans)
{
	SIZE size = GetSize();
	DrawTransBitmap(hdcDest, nXDest, nYDest, nWidthDest, nWidthDest, 0, 0, size.cx, size.cy, crTrans);
}
void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, COLORREF crTrans )
{
	SIZE size = GetSize();
	DrawTransBitmap(hdcDest, nXDest, nYDest, size.cx, size.cy, 0, 0, size.cx, size.cy, crTrans);
}

void SBitmap::DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, HBITMAP hMark, int nMarkX, int nMarkY)
{
	/*TODO:���´�����ܲ���ȷ */

	HDC dcMask = ::CreateCompatibleDC(hdcDest);			//���������豸
	HDC dcImage = ::CreateCompatibleDC(hdcDest);		//���������豸

	::SelectObject(dcMask, hMark);
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, dcMask, nMarkX, nMarkY, SRCAND);
	::DeleteDC(dcMask);

	::SelectObject(dcImage, GetHandle());
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, dcImage, nXSrc, nYSrc, SRCPAINT);
	::DeleteDC(dcImage);

}


void SBitmap::DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, HBITMAP hMark)
{
	DrawMaskBitmap(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, nXSrc, nYSrc, hMark, 0, 0);
}
void SBitmap::DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, HBITMAP hMark)
{
	DrawMaskBitmap(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, 0, 0, hMark, 0, 0);
}
void SBitmap::DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, HBITMAP hMark)
{
	SIZE size = GetSize();
	DrawMaskBitmap(hdcDest, nXDest, nYDest, size.cx, size.cy, 0, 0, hMark, 0, 0);
}