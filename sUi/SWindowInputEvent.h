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
		HWND hWnd;			//���
		UINT uMsg;		//��Ϣ
		WPARAM wParam;		//����1
		LPARAM lParam;		//����2
	public:
		InputParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);

	public:
		//ȡ�����X,Y����
		int GetMouseX();
		int GetMouseY();
	public:
		//ָ���������״̬��һ������ > 0 û����|< 0������
		static SHORT GetKeyState(int nVirtKey);

		//ȷ���û���ǰ�Ƿ����˼����ϵ�һ����
		//����ѱ���������λ0��Ϊ1��������Ϊ0
		//���Ŀǰ���ڰ���״̬����λ15��Ϊ1����̧����Ϊ0��
		static SHORT GetAsyncKeyState(int nVirtKey);

		//�ж����ⰴ���Ƿ񱻰���
		static BOOL GetKeyboardState(PBYTE lpKeyState);
	};
public:
	//���̰���
	virtual void OnKeyDown(InputParam param);
	//���̵���
	virtual void OnKeyUp(InputParam param);
	//����������
	virtual void OnMouseLButtonDown(InputParam param);
	//����������
	virtual void OnMouseLButtonUp(InputParam param);
	//������
	virtual void OnMouseWheel(InputParam param);
	//������˫��
	virtual void OnMouseDoubleClick(InputParam param);
	//����Ҽ�����
	virtual void OnMouseRButtonDown(InputParam param);
	//����Ҽ�����
	virtual void OnMouseRButtonUp(InputParam param);
	//����ƶ�
	virtual void OnMouseMove(InputParam param);

};

#endif