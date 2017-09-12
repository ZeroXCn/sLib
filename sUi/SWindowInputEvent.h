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
#include <functional>
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
		int GetMouseZ();
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
private:
	std::function<void(InputParam)> m_fKeyDown;
	std::function<void(InputParam)> m_fKeyUp;
	std::function<void(InputParam)> m_fMouseLButtonDown;
	std::function<void(InputParam)> m_fMouseLButtonUp;
	std::function<void(InputParam)> m_fMouseWheel;
	std::function<void(InputParam)> m_fMouseDoubleClick;
	std::function<void(InputParam)> m_fMouseRButtonDown;
	std::function<void(InputParam)> m_fMouseRButtonUp;
	std::function<void(InputParam)> m_fMouseMove;

public:
	SWindowInputEvent();
	virtual ~SWindowInputEvent();
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
public:
	//���̰���
	void OnKeyDown(std::function<void(InputParam)> fKeyDowm);
	//���̵���
	void OnKeyUp(std::function<void(InputParam)> fKeyUp);
	//����������
	void OnMouseLButtonDown(std::function<void(InputParam)> fMouseLButtonDown);
	//����������
	void OnMouseLButtonUp(std::function<void(InputParam)> fMouseLButtonUp);
	//������
	void OnMouseWheel(std::function<void(InputParam)> fMouseWheel);
	//������˫��
	void OnMouseDoubleClick(std::function<void(InputParam)> fMouseDoubleClick);
	//����Ҽ�����
	void OnMouseRButtonDown(std::function<void(InputParam)> fMouseRButtonDown);
	//����Ҽ�����
	void OnMouseRButtonUp(std::function<void(InputParam)> fMouseRButtonUp);
	//����ƶ�
	void OnMouseMove(std::function<void(InputParam)> fMouseMove);
};

#endif