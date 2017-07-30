/**
* SMessageHandler������
* ��Ϣ�������,ʵ�ִ���ͨ���������󷽷�ת��
*
* @author ZeroX �ο���colin<linzhenqun@gmail.com>
* @address http://blog.csdn.net/linzhengqun/article/details/6540366
* @version v1.0 21/07/2017
*/

#ifndef _SMESSAGEHANDLER_H_
#define _SMESSAGEHANDLER_H_

#include <Windows.h>
#include <hash_map>
using namespace std;

//typedef LRESULT(CALLBACK *WNDPROC)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
class SMessageHandler
{
protected:
	class wnd_hash
	{
	public:
		enum
		{
			bucket_size = 4,
			min_buckets = 8
		};
		wnd_hash()
		{
		}
		size_t operator()(const HWND& hwnd) const
		{
			return size_t(hwnd);
		}
		bool operator()(const HWND& hwnd1, const HWND& hwnd2) const
		{
			return   hwnd1 != hwnd2;
		}
	};
	typedef hash_map<HWND, SMessageHandler *, wnd_hash> WndHandlerMap;
	
public:
	//��ͨ����
	static LRESULT CALLBACK MessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static WNDPROC GetMessageHandlerProc();
protected:
	static WndHandlerMap s_WndHandlerMap;
protected:
	WNDPROC m_pWndProc;

protected:
	//���󷽷�
	virtual LRESULT CALLBACK OnProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	SMessageHandler();
	virtual ~SMessageHandler();
public:
	//ȡ�ü�¼��
	WndHandlerMap *GetWndHandlerMap();

	//ȡ����Ϣ������
	WNDPROC GetMessageProc();

	//������Ϣ������
	void SetMessageProc(WNDPROC pWndProc);
protected:
	//�������໯
	bool Subclass(HWND hwnd);

	//���ڷ����໯
	void Unsubclass(HWND hwnd);
};

#endif