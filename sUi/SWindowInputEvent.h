/**
* SWindowInputEvent��
* ���������¼�
* @author ZeroX
* @version v1.0 24/07/2017
*/
/*************************************
���������������
��Ҫ�������������
*************************************/
#include "../sCore/SObject.h"

#ifndef _SWINDOWINPUTEVENT_H_
#define _SWINDOWINPUTEVENT_H_

#include <Windows.h>

class SWindowInputEvent:public SObject
{
public:
	//�����
	virtual void OnKeyEvent();
	//���̰���
	virtual void OnKeyDown(HWND hWnd, WPARAM wParam);
	//���̵���
	virtual void OnKeyUp(HWND hWnd, WPARAM wParam);
	//����������
	virtual void OnMouseLButtonDown(HWND hWnd, int x, int y, WPARAM wParam);
	//����������
	virtual void OnMouseLButtonUp(HWND hWnd, int x, int y, WPARAM wParam);
	//������
	virtual void OnMouseWheel(HWND hWnd, WPARAM wParam);
	//������˫��
	virtual void OnMouseDoubleClick(HWND hWnd, int x, int y, WPARAM wParam);
	//����Ҽ�����
	virtual void OnMouseRButtonDown(HWND hWnd, int x, int y, WPARAM wParam);
	//����Ҽ�����
	virtual void OnMouseRButtonUp(HWND hWnd, int x, int y, WPARAM wParam);
	//����ƶ�
	virtual void OnMouseMove(HWND hWnd, int x, int y, WPARAM wParam);

};

#endif