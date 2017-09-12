/**
*	SLayered
*	@brief ϵͳ�ֲ���
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 08/09/2017
*	@update  08/09/2017
*/
#include "../sCore/SObject.h"
#ifndef _SLAYERED_H_
#define _SLAYERED_H_
#include <Windows.h>
class SLayered:public SObject
{
public:
	//���ô�����չ��ʽ����
	static BOOL SetWindowExStyle(HWND hWnd);
	//���ò�����(���ھ��,͸��ɫ,͸����,͸������)
	static BOOL SetLayeredArrtibutes(HWND hWnd, COLORREF crKey, UINT cAlpha, BOOL dwFlags);
	//���·ֲ�
	static BOOL UpdateLayeredWindow(HWND hWnd, HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	/*
	LWA_ALPHAʱ��crKey������Ч��bAlpha������Ч��
	LWA_COLORKEY�������е�������ɫΪcrKey�ĵط�����Ϊ͸����bAlpha������Ч���䳣��ֵΪ1��
	LWA_ALPHA | LWA_COLORKEY��crKey�ĵط�����Ϊȫ͸�����������ط�����bAlpha����ȷ��͸���ȡ�
	*/
	static BOOL TransWindow(HWND hWnd, COLORREF crKey = RGB(0, 0, 0), UINT cAlpha = 255, BOOL dwFlags = LWA_ALPHA | LWA_COLORKEY);
private:
	UINT m_nAlpha;			//͸����
	DWORD m_dwColor;		//͸��ɫ
	HWND m_hWnd;			//��¼���ھ��

public:
	SLayered(HWND hWnd=NULL);
	~SLayered();
public:
	void SetAlpha(UINT nAlpha);
	UINT GetAlpha();

	void SetColor(DWORD dwColor);
	DWORD GetAColor();

public:
	//��ʼ��
	BOOL Init(HWND hWnd);

	//���ö���
	BOOL SetLayered(BOOL dwFlags,COLORREF crKey, UINT cAlpha);
	BOOL SetLayered(BOOL dwFlags , COLORREF crKey );
	BOOL SetLayered(BOOL dwFlags , UINT cAlpha );
	BOOL SetLayered(BOOL dwFlags = LWA_ALPHA | LWA_COLORKEY);
	//���²�
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, HDC hSrc, POINT *pptSrc, DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hDst,HDC hSrc,  DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hSrc,DWORD dwFlags = ULW_ALPHA);

};
#endif