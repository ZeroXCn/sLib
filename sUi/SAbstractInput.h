/*************************************
窗口类输入抽象类
主要负责外设的输入
*************************************/
#pragma once
#include <Windows.h>

class SAbstractInput
{
public:
	//活动控制
	virtual void OnKeyEvent();
	//键盘按下
	virtual void OnKeyDown(HWND hWnd, WPARAM wParam);
	//键盘弹起
	virtual void OnKeyUp(HWND hWnd, WPARAM wParam);
	//鼠标左键按下
	virtual void OnMouseLButtonDown(HWND hWnd, int x, int y, WPARAM wParam);
	//鼠标左键弹起
	virtual void OnMouseLButtonUp(HWND hWnd, int x, int y, WPARAM wParam);
	//鼠标滚轮
	virtual void OnMouseWheel(HWND hWnd, WPARAM wParam);
	//鼠标左键双击
	virtual void OnMouseDoubleClick(HWND hWnd, int x, int y, WPARAM wParam);
	//鼠标右键按下
	virtual void OnMouseRButtonDown(HWND hWnd, int x, int y, WPARAM wParam);
	//鼠标右键按下
	virtual void OnMouseRButtonUp(HWND hWnd, int x, int y, WPARAM wParam);
	//鼠标移动
	virtual void OnMouseMove(HWND hWnd, int x, int y, WPARAM wParam);

};