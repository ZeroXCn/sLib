/*************************************
���������������
��Ҫ�������������
*************************************/
#pragma once
#include <Windows.h>

class SAbstractInput
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