#pragma once
#include <Windows.h>
#include "SWidget.h"
class SLabel :public SWidget
{
protected:
	TCHAR m_text[256];				//��������
	LOGFONT m_lFont;				//����
	COLORREF m_crTextColor;			//ǰ��ɫ
	BOOL m_bTrans;					//�Ƿ�͸��
	COLORREF m_crBackColor;			//����ɫ
	int m_nMode;					//ģʽ

public:
	/* ��ȡ���ÿؼ����� */
	void SetText(LPTSTR szText);
	LPTSTR GetText();

	/* ��ȡ�������� */
	void SetFont(LOGFONT lFont);
	LOGFONT GetFont();

	/* ��ȡ����������ɫ */
	void SetTextColor(COLORREF crTextColor);
	COLORREF GetTextColor();

	/* ��ȡ�����Ƿ�͸�� */
	BOOL IsTrans();
	void SetTrans(BOOL bTrans);

	/* ��ȡ���ñ���ɫ */
	void SetBkColor(COLORREF crBackColor);
	COLORREF GetBkColor();

	/* ��ȡ����ģʽ */
	void SetMode(int nMode);
	int GetMode();

protected:
	//�����ؼ�
	virtual BOOL OnCreate();

	//��дPaint�¼�,���Ƹÿؼ�
	virtual void OnPaint();
};