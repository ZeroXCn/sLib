/**
*	SLayered
*	@brief 系统分层类
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
	//设置窗口扩展样式属性
	static BOOL SetWindowExStyle(HWND hWnd);
	//设置层属性(窗口句柄,透明色,透明度,透明类型)
	static BOOL SetLayeredArrtibutes(HWND hWnd, COLORREF crKey, UINT cAlpha, BOOL dwFlags);
	//更新分层
	static BOOL UpdateLayeredWindow(HWND hWnd, HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	/*
	LWA_ALPHA时：crKey参数无效，bAlpha参数有效；
	LWA_COLORKEY：窗体中的所有颜色为crKey的地方将变为透明，bAlpha参数无效。其常量值为1。
	LWA_ALPHA | LWA_COLORKEY：crKey的地方将变为全透明，而其它地方根据bAlpha参数确定透明度。
	*/
	static BOOL TransWindow(HWND hWnd, COLORREF crKey = RGB(0, 0, 0), UINT cAlpha = 255, BOOL dwFlags = LWA_ALPHA | LWA_COLORKEY);
private:
	UINT m_nAlpha;			//透明度
	DWORD m_dwColor;		//透明色
	HWND m_hWnd;			//记录窗口句柄

public:
	SLayered(HWND hWnd=NULL);
	~SLayered();
public:
	void SetAlpha(UINT nAlpha);
	UINT GetAlpha();

	void SetColor(DWORD dwColor);
	DWORD GetAColor();

public:
	//初始化
	BOOL Init(HWND hWnd);

	//设置对像
	BOOL SetLayered(BOOL dwFlags,COLORREF crKey, UINT cAlpha);
	BOOL SetLayered(BOOL dwFlags , COLORREF crKey );
	BOOL SetLayered(BOOL dwFlags , UINT cAlpha );
	BOOL SetLayered(BOOL dwFlags = LWA_ALPHA | LWA_COLORKEY);
	//更新层
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags);
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, HDC hSrc, POINT *pptSrc, DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hDst, POINT *pptDst, SIZE *psize, HDC hSrc, POINT *pptSrc, DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hDst,HDC hSrc,  DWORD dwFlags = ULW_ALPHA);
	BOOL UpdateLayered(HDC hSrc,DWORD dwFlags = ULW_ALPHA);

};
#endif