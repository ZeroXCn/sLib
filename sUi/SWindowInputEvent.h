/**
* SWindowInputEvent�ӿ���
* ���������¼�
* @author ZeroX
* @version v1.0 24/07/2017
*/
/*************************************
���������������
��Ҫ�������������
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
		HWND &hWnd;			//���
		UINT &message;		//��Ϣ
		WPARAM &wParam;		//����1
		LPARAM &lParam;		//����2
	public:
		InputParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);
	public:
		HWND &GetWnd();
		UINT &GetMessage();
		WPARAM &GetWParam();
		LPARAM &GetLParam();

		void SetWnd(HWND &hWnd);
		void SetMessage(UINT &message);
		void SetWParam(WPARAM &wParam);
		void SetLParam(LPARAM &lParam);
	public:

	};
public:
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