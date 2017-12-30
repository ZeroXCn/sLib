/**
* SBitmap��
* GDI����-λͼ��(ֻ֧��BMP��ʽ)
* @author ZeroX
* @version v1.0 25/07/2017
*/
#include "SGdiHandle.h"
#ifndef _SBITMAP_H_
#define _SBITMAP_H_
#include <Windows.h>
#include <Mmsystem.h>
#include <wingdi.h>

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"gdi32.lib")

class SBitmap :public SGdiHandle<HBITMAP, BITMAP>
{
public:
	SBitmap(SGdiObj Obj);
	SBitmap(HBITMAP hBitmap=NULL);
	virtual ~SBitmap();
public:
	//����һ�������ض���ȡ��߶Ⱥ���ɫ��ʽ��λͼ��
	BOOL Create(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPeral, CONST VOID *lpvBits);

	//������ָ�����豸������ص��豸���ݵ�λͼ
	BOOL CreateCompatible(HDC hdc, int nWidth, int nHeight);

	//����һ�������ض���ȡ��߶Ⱥ���ɫ��ʽ��λͼ
	BOOL CreateIndirect(CONST BITMAP *lpbm);

	//����Ӧ�ó������ֱ��д��ġ����豸�޹ص�λͼ��DIB���ĺ�����
	BOOL CreateDIBSection(HDC hdc, CONST BITMAPINFO *pbmi, UINT iUsage, VOID** ppvBits, HANDLE hSection, DWORD dwOffset);

	//����Դ�м���λͼ
	BOOL Load(UINT uRcid, HINSTANCE hInstance = NULL);

	//���ļ��м���λͼ
	BOOL Load(LPTSTR lpFileName, HINSTANCE hInstance = NULL);

	//���ڴ��м���
	BOOL Load(void *pMemory, int nLength);

	//��λͼ�б����ļ�
	BOOL Save(LPTSTR lpFileName);

public:
	//ȡ��,����λ��
	int GetWidth();

	//ȡ��,����λ��
	int GetHeight();

	//ȡ��,����λͼ���
	SIZE GetSize();
	void SetSize(int nWidth,int nHeight);



public:
	/* λͼ���� */
	//��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������
	BOOL BitBlt(HDC hdcDest,  int nXDest,  int nYDest,  int nWidth,  int nHeight,  HDC hdcSrc,  int nXSrc,  int nYSrc,  DWORD dwRop);
	BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc = 0, int nYSrc = 0, DWORD dwRop = SRCCOPY);
	BOOL BitBlt(HDC hdcDest, int nXDest, int nYDest, DWORD dwRop = SRCCOPY);

	//ѡ��ָ���豸�����е�ˢ�ӻ��Ƹ����ľ�������
	BOOL PatBlt(HDC hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop = PATCOPY);

	//��Դ�豸������ָ���ľ��������е���ɫ����λ����λ��ת������ת����Ŀ���豸������ָ����ƽ���ı����
	BOOL PlgBlt(HDC hdcDest, CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask);

	//��Դ�����и���һ��λͼ��Ŀ����Σ���Ҫʱ��Ŀ���豸���õ�ģʽ����ͼ��������ѹ��
	BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);
	BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);


	//ʹ���ض�������͹�դ��������Դ��Ŀ��λͼ����ɫ���ݽ������
	//���ַ�-Ҫ��Ϊɫ�ڰ�ͼ(��������Ϊ��,����Ϊ��)-���һ������Ϊ���߹�դ������-��λΪǰ��(MARK)�뱳����,��λΪ�����������DC
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, int nXSrc, int nYSrc, HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));
	BOOL MaskBlt(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hbmMask, DWORD dwRop = MAKEROP4(SRCPAINT, SRCCOPY));

	//��ָ����Դ�豸�����еľ����������ص���ɫ���ݽ���λ�飨bit_block��ת���������������Ŀ���豸����
	//͸��ɫ�ʷ�
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,UINT crTransparent = RGB(255, 255, 255));
	BOOL TransparentBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest,UINT crTransparent = RGB(255, 255, 255));

	//������ʾ����ָ��͸���ȵ�ͼ��
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, BLENDFUNCTION blendFunction);
	BOOL AlphaBlend(HDC hdcDest, int nXOriginDest, int nYOriginDest, BLENDFUNCTION blendFunction);
public:
	/* ����Ϊ��չ���� */

	//���ư�͸��λͼ,��͸����nAphaȡֵΪ0~255
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nAlpha);
	void DrawAlpha(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nAlpha);

	//���ƻҶ�λͼ��������Ϊ�ο�
	void DrawGray(HDC hDC, int x, int y, BOOL bTrans = FALSE, COLORREF crTransparent = RGB(0, 0, 0));

	//���ư�͸���ο�λͼ
	void DrawTransAlpha(HDC hdcBack,		// ����DC
		int nXBack,							// ����ͼ���Ͻ�X����
		int nYBack,							// ����ͼ���Ͻ�Y����
		int nWidthBack,						// ����ͼ���
		int nHeightBack,					// ����ͼ�߶�
		HDC hdcSrc,							// ԴDC
		int nXFore,							// ǰ��ͼ���Ͻ�X����
		int nYFore,							// ǰ��ͼ���Ͻ�Y����
		int nWidthFore,						// ǰ��ͼ���
		int nHeightFore,					// ǰ��ͼ�߶�
		int nAlpha = 100,					// ��͸����
		COLORREF crTrans = RGB(0, 0, 0));	//�ο�ɫ
	void DrawTransAlpha(HDC hdcBack,int nXBack,int nYBack,int nWidthBack,int nHeightBack,int nXFore,int nYFore,int nWidthFore,int nHeightFore,int nAlpha = 100,COLORREF crTrans = RGB(0, 0, 0));
	void DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nWidthBack, int nHeightBack,int nAlpha = 100, COLORREF crTrans = RGB(0, 0, 0));
	void DrawTransAlpha(HDC hdcBack, int nXBack, int nYBack, int nAlpha = 100, COLORREF crTrans = RGB(0, 0, 0));

	//�Զ���Ļ����ο�ͼ�ķ���
	void DrawTransBitmap(
		HDC hdcDest,						// Ŀ��DC
		int nXDest,							// Ŀ�����Ͻ�X����
		int nYDest,							// Ŀ�����Ͻ�Y����
		int nWidthDest,						// Ŀ����
		int nHeightDest,					// Ŀ��߶�
		HDC hdcSrc,							// ԴDC
		int nXSrc,							// ԴX���
		int nYSrc,							// ԴY���
		int nWidthSrc,						// Դ���
		int nHeightSrc,						// Դ�߶�
		COLORREF crTrans = RGB(255, 255, 255)  // ͸��ɫ
		);
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, int nWidthSrc, int nHeightSrc, COLORREF crTrans = RGB(255, 255, 255));
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest,COLORREF crTrans = RGB(255, 255, 255));
	void DrawTransBitmap(HDC hdcDest, int nXDest, int nYDest, COLORREF crTrans = RGB(255, 255, 255));

	//�Զ���Ļ���
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc,HBITMAP hMark, int nMarkX, int nMarkY);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, int nXSrc, int nYSrc, HBITMAP hMark);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest, int nWidthDest, int nHeightDest, HBITMAP hMark);
	void DrawMaskBitmap(HDC hdcDest, int nXDest, int nYDest,  HBITMAP hMark);
};

#endif