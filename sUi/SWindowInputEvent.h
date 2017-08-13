/**
* SWindowInputEvent接口类
* 窗体输入事件
* @author ZeroX
* @version v1.0 24/07/2017
*/
/*************************************
窗口类输入抽象类
主要负责外设的输入
*************************************/

#ifndef _SWINDOWINPUTEVENT_H_
#define _SWINDOWINPUTEVENT_H_

#include <Windows.h>

class SWindowInputEvent
{
public:
	class InputParam
	{
	public:
		HWND hWnd;			//句柄
		UINT uMsg;		//消息
		WPARAM wParam;		//参数1
		LPARAM lParam;		//参数2
	public:
		InputParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

	public:
		//取得鼠标X,Y坐标
		int GetMouseX();
		int GetMouseY();
	public:
		//指定虚拟键的状态的一个函数 > 0 没按下|< 0被按下
		static SHORT GetKeyState(int nVirtKey);

		//确定用户当前是否按下了键盘上的一个键
		//如键已被按过，则位0设为1；否则设为0
		//如键目前处于按下状态，则位15设为1；如抬起，则为0。
		static SHORT GetAsyncKeyState(int nVirtKey);

		//判断虚拟按键是否被按下
		static BOOL GetKeyboardState(PBYTE lpKeyState);
	};
public:
	//键盘按下
	virtual void OnKeyDown(InputParam param);
	//键盘弹起
	virtual void OnKeyUp(InputParam param);
	//鼠标左键按下
	virtual void OnMouseLButtonDown(InputParam param);
	//鼠标左键弹起
	virtual void OnMouseLButtonUp(InputParam param);
	//鼠标滚轮
	virtual void OnMouseWheel(InputParam param);
	//鼠标左键双击
	virtual void OnMouseDoubleClick(InputParam param);
	//鼠标右键按下
	virtual void OnMouseRButtonDown(InputParam param);
	//鼠标右键按下
	virtual void OnMouseRButtonUp(InputParam param);
	//鼠标移动
	virtual void OnMouseMove(InputParam param);

};

#endif