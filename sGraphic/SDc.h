/**
* SDc��
* HDC��װ��
* @author ZeroX
* @version v1.0 25/07/2017
*/

#include "../sCore/SObject.h"
#include "../sCore/SString.h"

#include "SGdiObject.h"
#include "SBitmap.h"
#include "SFont.h"
#include "SBrush.h"
#include "SPen.h"
#include "SRgn.h"
#include "SPalette.h"

#include "SBufferDC.h"

#ifndef _SDC_H_
#define _SDC_H_
#include <Windows.h>
#include <Mmsystem.h>
#include <wingdi.h>

#pragma	comment(lib,"winmm.lib" )
#pragma comment(lib,"gdi32.lib")

#define RED_COLOR RGB(255,0,0)
#define GREEN_COLOR RGB(255,0,0)
#define BLUE_COLOR RGB(255,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BLACK_COLOR RGB(0,0,0)


class SDc:public SObject
{
protected:
	HDC m_hDC;			//�豸������
public:
	SDc();
	SDc(HDC hDC);

	virtual ~SDc();


public:
	//���û�ͼ������
	void SetDC(HDC hDC);

	//ȡ�õ�ǰ��ͼ������
	HDC GetDC();

public:
	//�����豸�����Ļ���
	SDc &CreateDC(LPTSTR lpszDriver, LPTSTR lpszDevice = NULL, LPTSTR lpszPort = NULL, const DEVMODE *pdm = NULL);

	// ����һ����ָ���豸���ݵ��ڴ��豸�����Ļ���
	SDc &CreateCompatibleDC(SDc dc);

	// ɾ��ָ�����豸�����Ļ�����Dc����
	BOOL DeleteDC();

	//���豸�����Ļ���������δ���Ĳ���ȡ����
	BOOL CancelDC();

	//����DC��ǰ״̬
	int SavaDC();

	//�ָ���SavaDC()�����DC
	BOOL RestoreDC(int nSavedDc);


public:
	//ѡ��һ����ָ�����豸�����Ļ�����
	HGDIOBJ SelectObject(HGDIOBJ hgdiobj);
	SGdiObject SelectObject(SGdiObject pObj);

	//��ȡ��ǰDC����
	HGDIOBJ GetCurrentObject(UINT uObjectType);
	//��ȡ��������
	UINT GetObjectType(HGDIOBJ hObject);

	//ɾ�����ͷ�ϵͳ��Դ
	BOOL DeleteObject(HGDIOBJ hObject);
	BOOL DeleteObject(SGdiObject pObj);
	
	//ѡ������
	SFont SetFont(SFont ofont);
	SFont GetFont();
	//ѡ��λͼ
	SBitmap SetBitmap(SBitmap bitmap);
	SBitmap GetBitmap();
	//ѡ��ˢ
	SBrush SetBrush(SBrush brush);
	SBrush GetBrush();
	//ѡ�񻭱�
	SPen SetPen(SPen pen);
	SPen GetPen();
	//ѡ������
	SRgn SetRgn(SRgn rgn);
	//��ɫ��
	SPalette GetPalette();
public:
	/* DC���Բ��� */
	//ȡ��DC��ʼ������
	POINT GetDCOrgEx();

public:
	//ָ���豸�����������ֶ����־
	UINT SetTextAlign(UINT fMode); // �ı�����ѡ��
	UINT GetTextAlign(); // �ı�����ѡ��

	//�����ı���ɫ
	COLORREF SetTextColor(COLORREF crColor);
	COLORREF GetTextColor();

	//���ñ���ɫ
	COLORREF SetBkColor(COLORREF color);
	COLORREF SetBkColor(BOOL bTrans);
	COLORREF GetBkColor();

	//���ñ���ģʽ-OPAQUE��͸����TRANSPARENT͸��
	int SetBkMode(int iBkMode);
	int GetBkMode();

public:
	//����
	BOOL DrawPoint(int x, int y, COLORREF color = RGB(0, 0, 0));

	//����
	void DrawLine(int x1, int y1, int x2, int y2);

	//��������
	void DrawTringle(POINT a, POINT b, POINT c);

	//������-�������ͻ��߿�
	BOOL DrawRect(int left, int top, int right, int bottom);

	//�����α߿�
	BOOL FrameRect(int left, int top, int right, int bottom, HBRUSH hbr = NULL);

	//������
	BOOL FillRect(int left, int top, int right, int bottom, HBRUSH hbr);
	BOOL FillRect(int left, int top, int right, int bottom, COLORREF crColor=BLACK_COLOR);

	//����Բ�Ǿ���
	BOOL RoundRect(int left, int top, int right, int bottom, int width, int height);

	//���������ݷ�ɫ
	BOOL InvertRect(int left, int top, int right, int bottom);

	//��Բ
	BOOL DrawRadius(int x, int y, int radius);

	//����Բ
	BOOL DrawEllipse(int left, int top, int right, int bottom);

	//��Բ������
	BOOL DrawPie(int left, int top, int right, int bottom, int xr1, int yr1, int xr2, int yr2);

	//�����и���Բ
	BOOL DrawChord(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

	//�����Բ
	//void FillEllipse(int left, int top, int right, int bottom);

	//���ƶ����
	BOOL DrawPolygon(POINT *apt, int cpt);

	//����ͬʱ���ƶ����յĶ���Ρ�
	BOOL DrawPolyPolygon(POINT *apt, int *asz, int csz);

	//�������
	BOOL GradientFill(CONST PTRIVERTEX pVertex, DWORD dwNumVertex, CONST PVOID pMesh, DWORD dwNumMesh, DWORD dwMode);

	//�������
	BOOL DrawString(SString str, int x, int y, COLORREF crColor = BLACK_COLOR, BOOL bTrans = TRUE, UINT format = DT_LEFT);
	int DrawString(SString str, RECT rt, UINT format = DT_CALCRECT);
	//������߿�����
	int DrawStringEx(SString str, LPRECT lprc, UINT dwDTFormat = DT_LEFT, LPDRAWTEXTPARAMS lpDTParams = NULL);

	//���λͼ
	BOOL DrawImage(HBITMAP hbm, int x, int y, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, UINT crTransparent);	//���߲�������,������Ҫǿ��ת��
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc = 0, int ySrc = 0, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, DWORD dwRop = SRCCOPY);
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, UINT crTransparent = RGB(255, 255, 255));
	BOOL DrawImage(HBITMAP hbm, int x, int y, int nWidth, int nHeight, int xSrc, int ySrc, int xSrcWidth, int ySrcHeight, UINT crTransparent );

	//�������
	BOOL DrawDC(HDC hdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop = SRCCOPY);
	BOOL DrawDC(HDC hdcSrc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, int nXOriginSrc = 0, int nYOriginSrc = 0, DWORD dwRop = SRCCOPY);
public:
	/* DC���� */
	//��ά������ת�䣬��ת��������������š���ת����б�任��ƽ�Ʊ任��ͼ�Ρ�
	int SetTransform(CONST XFORM *lpXform);
	XFORM GetTransform();
	int RestoreTransform(int nGraphicsMode = GM_COMPATIBLE);	//�ָ�����DC

	//��ת�ͻָ���ת
	int Rotate(int iAngle, int cx = 0, int cy = 0);
	int Rotate(double dTheta, int cx = 0, int cy = 0);
	int RotateFrom(int iAngle, int cx = 0, int cy = 0);
	int RotateFrom(double dTheta, int cx = 0, int cy = 0);
	
	//����
	int Scale(float sx, float sy);
	int ScaleFrom(float sx, float sy);

	//ƽ��
	int Offset(int cx, int cy);
	int OffsetFrom(int cx, int cy);

	//����
	int Shear(int sx, int sy);

	//����
	int Reflect(int cx, int cy );

	//����-����ĳ������
	int Mirror(int dX);

	//����ĳ��Գ�
	int Symmetry(int cx, int cy);

public:
	/* ������λͼ���� */
	//��ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������
	BOOL BitBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop = SRCCOPY);

	//ѡ��ָ���豸�����е�ˢ�ӻ��Ƹ����ľ�������
	BOOL PatBlt(int nXLeft, int nYLeft, int nWidth, int nHeight, DWORD dwRop = PATCOPY);

	//��Դ�豸������ָ���ľ��������е���ɫ����λ����λ��ת������ת����Ŀ���豸������ָ����ƽ���ı����
	BOOL PlgBlt(CONST POINT *lpPoint, HDC hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, HBITMAP hbmMask, int xMask, int yMask);

	//��Դ�����и���һ��λͼ��Ŀ����Σ���Ҫʱ��Ŀ���豸���õ�ģʽ����ͼ��������ѹ��
	BOOL StretchBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);

	//ʹ���ض�������͹�դ��������Դ��Ŀ��λͼ����ɫ���ݽ������
	BOOL MaskBlt(int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, HBITMAP hbmMask, int xMask, int yMask, DWORD dwRop);

	//��ָ����Դ�豸�����еľ����������ص���ɫ���ݽ���λ�飨bit_block��ת���������������Ŀ���豸����
	BOOL TransparentBlt(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent);

	//������ʾ����ָ��͸���ȵ�ͼ��
	BOOL AlphaBlend(int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);

};

#endif