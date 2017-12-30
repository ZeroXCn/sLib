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
//取得,设置位图宽
int SBitmap::GetWidth()
{
	return GetSize().cx;
}


//取得,设置位图高
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

//从资源中加载位图
BOOL SBitmap::Load(UINT uRcid, HINSTANCE hInstance)
{
	
	m_hGdiObj = (HBITMAP)::LoadImage(hInstance, MAKEINTRESOURCE(uRcid), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	 return m_hGdiObj ? TRUE : FALSE;
}

//从文件中加载位图
BOOL SBitmap::Load(LPTSTR lpFileName, HINSTANCE hInstance)
{
	m_hGdiObj = (HBITMAP)::LoadImage(hInstance, lpFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	return m_hGdiObj ? TRUE : FALSE;
}

//从内存中加载
BOOL SBitmap::Load(void *pMemory, int nLength)
{
	//摘自http://blog.csdn.net/ccd1230102/article/details/2845646
	BITMAPFILEHEADER *pbmfh = (BITMAPFILEHEADER *)pMemory;
	//与设备无关的位图（DIB）
	m_hGdiObj = (HBITMAP) ::CreateDIBitmap(
		::GetDC(NULL),					//TODO : 这里意义不明,从内存中加载为何需要 DC ?
		(BITMAPINFOHEADER *)(pbmfh + 1),
		CBM_INIT,
		(BYTE *)pbmfh + pbmfh->bfOffBits,
		(BITMAPINFO *)(pbmfh + 1),
		DIB_RGB_COLORS);
	//BITMAPINFOHEADER *pbminfohead = (BITMAPINFOHEADER *)(pbmfh + 1);

	return m_hGdiObj ? TRUE : FALSE;
}


//从位图中保存文件
BOOL SBitmap::Save(LPTSTR lpFileName)
{
	//摘自http://blog.csdn.net/kaixiang54/article/details/7606598

	HBITMAP hBm = (HBITMAP)m_hGdiObj;
	//  定义位图文件表头  
	BITMAPFILEHEADER bmfh;
	//  定义位图信息表头  
	BITMAPINFOHEADER bmih;

	//  调色板长度  
	int nColorLen = 0;
	//  调色表大小  
	DWORD dwRgbQuadSize = 0;
	//  位图大小  
	DWORD dwBmSize = 0;
	//  分配内存的指针  
	HGLOBAL hMem = NULL;
	LPBITMAPINFOHEADER  lpbi;
	BITMAP bm;
	HDC hDC;
	HANDLE hFile = NULL;
	DWORD dwWritten;

	::GetObject(hBm, sizeof(BITMAP), &bm);

	bmih.biSize = sizeof(BITMAPINFOHEADER); // 本结构所占的字节  
	bmih.biWidth = bm.bmWidth;           // 位图宽  
	bmih.biHeight = bm.bmHeight;          // 位图高  
	bmih.biPlanes = 1;
	bmih.biBitCount = bm.bmBitsPixel;   // 每一图素的位数  
	bmih.biCompression = BI_RGB;           // 不压缩  
	bmih.biSizeImage = 0;  //  位图大小  
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;

	//  计算位图图素数据区大小   
	dwBmSize = 4 * ((bm.bmWidth * bmih.biBitCount + 31) / 32) * bm.bmHeight;

	//  如果图素位 <= 8bit，则有调色板  
	if (bmih.biBitCount <= 8)
	{
		nColorLen = (1 << bm.bmBitsPixel);
	}

	//  计算调色板大小  
	dwRgbQuadSize = nColorLen * sizeof(RGBQUAD);

	//  分配内存  
	hMem = GlobalAlloc(GHND, dwBmSize + dwRgbQuadSize + sizeof(BITMAPINFOHEADER));

	if (NULL == hMem)
	{
		return FALSE;
	}

	//  锁定内存  
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(hMem);

	//  将bmih中的内容写入分配的内存中  
	*lpbi = bmih;

	hDC = GetDC(NULL);

	//  将位图中的数据以bits的形式放入lpData中。  
	::GetDIBits(hDC, hBm, 0, (DWORD)bmih.biHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwRgbQuadSize, (BITMAPINFO *)lpbi, (DWORD)DIB_RGB_COLORS);

	bmfh.bfType = 0x4D42;  // 位图文件类型：BM  
	bmfh.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwRgbQuadSize + dwBmSize;  // 位图大小  
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwRgbQuadSize;  // 位图数据与文件头部的偏移量  

	//  把上面的数据写入文件中  

	hFile = ::CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return FALSE;
	}

	//  写入位图文件头  
	::WriteFile(hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER), (DWORD *)&dwWritten, NULL);
	//  写入位图数据  
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
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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

/* 在hDC的指定位置(x,y)输出透明度为nAlpha(0~255)的半透明图像 */
void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{

		//设置bf结构
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = nAlpha;
		bf.AlphaFormat = 0x00;

		//输出半透明图像
		AlphaBlend(hdcDest, nXOriginDest, nYOriginDest ,nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, bf);

}

void SBitmap::DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{
	//设置bf结构
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = nAlpha;
	bf.AlphaFormat = 0x00;

	//输出半透明图像
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


/*绘制灰度镂空图*/
void SBitmap::DrawGray(HDC hDC, int x, int y, BOOL bTrans, COLORREF crTrans)
{

	HDC hdcMem = ::CreateCompatibleDC(hDC);		//创建兼容设备

	BITMAP  bm;
	::GetObject((HBITMAP)m_hGdiObj, sizeof(BITMAP), &bm);
	BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //声明暂存数组
	::GetBitmapBits((HBITMAP)m_hGdiObj, bm.bmHeight*bm.bmWidthBytes, px); //取得源位图各像素点的 RGB 值存入 px 数组中


	int pb = bm.bmBitsPixel / 8;
	//循环计算灰度值
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
	//创建临时位图，以存储灰度图像
	HBITMAP	hbmTmp = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);
	::SetBitmapBits(hbmTmp, bm.bmHeight*bm.bmWidthBytes, px);

	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, hbmTmp);

	if (bTrans)
		//输出透明位图
		::TransparentBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, crTrans);
	else
		//输出不透明位图
		::BitBlt(hDC, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);



	delete[] px;		//删除数组

	SelectObject(hdcMem, hOldBmp);
	DeleteObject(hbmTmp);
	DeleteDC(hdcMem);				//删除兼容设备
	
}

/*绘制半透明镂空图*/
void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, HDC hdcSrc, int nXFore, int nYFore, int nWidthFore, int nHeightFore, int nAlpha, COLORREF crTrans)
{
	if (nAlpha >0)
	{
		//创建一个与背景同样大小的临时图像	
		RECT rBackRect = { nXBack, nYBack, nWidthBack, nHeightBack };
		HBITMAP	hbmTmp = ::CreateCompatibleBitmap(hdcBack, nWidthBack, nHeightBack);

		HBITMAP hbmBk = (HBITMAP)::SelectObject(hdcBack, hbmTmp);	//替出背景图像

		RECT rForeRect = { nXFore, nYFore, nXFore + nWidthFore, nYFore + nHeightFore };
		RECT rTransRect, rTransRect2;

		//获取前景矩形与背景矩形的交集,如不相交，则不需要进行颜色计算 
		if (::IntersectRect(&rTransRect, &rBackRect, &rForeRect))
		{
			BITMAP  bm, bmBk;
			::GetObject((HBITMAP)m_hGdiObj, sizeof(BITMAP), &bm);
			BYTE * px = new unsigned char[bm.bmHeight*bm.bmWidthBytes]; //声明暂存数组
			::GetBitmapBits((HBITMAP)m_hGdiObj, bm.bmHeight*bm.bmWidthBytes, px); //取得源位图各像素点的 RGB 值存入 px 数组中

			::GetObject(hbmBk, sizeof(BITMAP), &bmBk);
			BYTE * pxBk = new unsigned char[bmBk.bmHeight*bmBk.bmWidthBytes];  //声明暂存数组

			::GetBitmapBits(hbmBk, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk); //取得源位图各像素点的 RGB 值存入 pxBk数组中

			rTransRect2 = rTransRect;
			::OffsetRect(&rTransRect2, -rForeRect.left, -rForeRect.top);	//偏移矩形坐标

			int pb = bm.bmBitsPixel / 8;		//获取每像素所占字节数
			int pbBk = bmBk.bmBitsPixel / 8;

			//dy1为背景图像素行数,dy2为前景图像素行数
			//dx1为背景图像素列数,dx2为前景图像素列数
			int dx1, dx2, dy1, dy2;
			//循环对像素进行计算，背景和前景中需要进行计算的像素分别在各自对应的矩形rTransRect和rTransRect2的范围内循环 
			for (dy1 = rTransRect.top, dy2 = rTransRect2.top; dy1<rTransRect.bottom; dy1++, dy2++)
			for (dx1 = rTransRect.left, dx2 = rTransRect2.left; dx1<rTransRect.right; dx1++, dx2++)
			{
				int nBackRGB_B = dy1*bmBk.bmWidthBytes + dx1*pbBk;		//计算背景图像素起始位置
				int nForeRGB_B = dy2*bm.bmWidthBytes + dx2*pb;			//计算前景图像素起始位置

				if (RGB(px[nForeRGB_B + 2], px[nForeRGB_B + 1], px[nForeRGB_B]) != crTrans)
				{
					pxBk[nBackRGB_B] = (px[nForeRGB_B] * nAlpha + pxBk[nBackRGB_B] * (255 - nAlpha)) / 255;	//将B色彩值乘以nAlpha并与 px 相加
					pxBk[nBackRGB_B + 1] = (px[nForeRGB_B + 1] * nAlpha + pxBk[nBackRGB_B + 1] * (255 - nAlpha)) / 255;//将 G 色彩值乘以nAlpha并与 px 相加
					pxBk[nBackRGB_B + 2] = (px[nForeRGB_B + 2] * nAlpha + pxBk[nBackRGB_B + 2] * (255 - nAlpha)) / 255;//将 R 色彩值乘以 nAlpha并与 px 相加
				}
			}

			::SetBitmapBits(hbmTmp, bmBk.bmHeight*bmBk.bmWidthBytes, pxBk); //设置背景图数据
			HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcSrc, hbmTmp);
			::BitBlt(hdcBack, 0, 0, rBackRect.right, rBackRect.bottom, hdcSrc, 0, 0, SRCCOPY);

			delete[] px;		//删除数组
			delete[] pxBk;
			::SelectObject(hdcSrc, hbmOld);
		}

		::DeleteObject(hbmTmp);

	}
}

void SBitmap::DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack, int nXFore, int nYFore, int nWidthFore, int nHeightFore, int nAlpha, COLORREF crTrans)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcBack);		//创建兼容设备
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


/* 绘制透明镂空位图 */
void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest,
	HDC hdcSrc, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans)
{
	// 创建兼容位图
	HBITMAP hbmTmp = ::CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);
	// 创建单色位图
	HBITMAP hbmMask = ::CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);
	//创建兼容设备环境
	HDC		hdcMem = ::CreateCompatibleDC(hdcDest);
	HDC		hdcMask = ::CreateCompatibleDC(hdcDest);

	HBITMAP hbmOld = (HBITMAP)::SelectObject(hdcMem, hbmTmp);
	HBITMAP hbmMaskOld = (HBITMAP)::SelectObject(hdcMask, hbmMask);

	// 将源DC中的位图拷贝到临时设备环境中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		::BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXSrc, nYSrc, SRCCOPY);
	else
		::StretchBlt(hdcMem, 0, 0, nWidthDest, nHeightDest,
		hdcSrc, nXSrc, nYSrc, nWidthSrc, nHeightSrc, SRCCOPY);

	// 设置透明色
	::SetBkColor(hdcMem, crTrans);

	// 生成透明区域为白色，其它区域为黑色的蒙版位图
	::BitBlt(hdcMask, 0, 0, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCCOPY);

	// 生成透明区域为黑色，其它区域保持不变的位图
	::SetBkColor(hdcMem, RGB(0, 0, 0));
	::SetTextColor(hdcMem, RGB(255, 255, 255));
	::BitBlt(hdcMem, 0, 0, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// 透明部分对应的背景保持不变，其它部分变成黑色
	::SetBkColor(hdcDest, RGB(255, 255, 255));
	::SetTextColor(hdcDest, RGB(0, 0, 0));
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMask, 0, 0, SRCAND);

	// "或"运算,生成最终效果
	::BitBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest, hdcMem, 0, 0, SRCPAINT);

	// 清理临时内容，释放资源
	::SelectObject(hdcMem, hbmOld);
	::DeleteDC(hdcMem);
	::SelectObject(hdcMask, hbmMaskOld);
	::DeleteDC(hdcMask);
	::DeleteObject(hbmTmp);
	::DeleteObject(hbmMask);
}

void SBitmap::DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans)
{
	HDC hdcMem = ::CreateCompatibleDC(hdcDest);		//创建兼容设备
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)m_hGdiObj);	//将位图选入兼容设备，并记录下旧的句柄

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
	/*TODO:以下代码可能不正确 */

	HDC dcMask = ::CreateCompatibleDC(hdcDest);			//创建兼容设备
	HDC dcImage = ::CreateCompatibleDC(hdcDest);		//创建兼容设备

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