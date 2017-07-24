/**
* SLabel��
* ��ǩ����
* @author ZeroX
* @version v1.0 21/07/2017
*/

#include "SWidget.h"
#ifndef _SLABEL_H_
#define _SLABEL_H_

#include <Windows.h>
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

public:
	//�����ؼ�
	virtual BOOL Create();

};
#endif