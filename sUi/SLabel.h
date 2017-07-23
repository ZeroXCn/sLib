#pragma once
#include <Windows.h>
#include "SWidget.h"
class SLabel :public SWidget
{
protected:
	TCHAR m_text[256];				//文字内容
	LOGFONT m_lFont;				//字体
	COLORREF m_crTextColor;			//前景色
	BOOL m_bTrans;					//是否透明
	COLORREF m_crBackColor;			//背景色
	int m_nMode;					//模式

public:
	/* 获取设置控件文字 */
	void SetText(LPTSTR szText);
	LPTSTR GetText();

	/* 获取设置字体 */
	void SetFont(LOGFONT lFont);
	LOGFONT GetFont();

	/* 获取设置文字颜色 */
	void SetTextColor(COLORREF crTextColor);
	COLORREF GetTextColor();

	/* 获取设置是否透明 */
	BOOL IsTrans();
	void SetTrans(BOOL bTrans);

	/* 获取设置背景色 */
	void SetBkColor(COLORREF crBackColor);
	COLORREF GetBkColor();

	/* 获取设置模式 */
	void SetMode(int nMode);
	int GetMode();

protected:
	//创建控件
	virtual BOOL OnCreate();

	//重写Paint事件,绘制该控件
	virtual void OnPaint();
};