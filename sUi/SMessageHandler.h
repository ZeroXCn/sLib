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


//typedef LRESULT(CALLBACK *WNDPROC)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class SMessageHandler
{

protected:
	class MessageParam
	{
		public:
			HWND hWnd;
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;
	public:
		MessageParam(HWND &hWnd, UINT &message, WPARAM &wParam, LPARAM &lParam);
	public:

		WORD GetItemId();//ȡ�ÿؼ�ID
		WORD GetCode();	//ȡ��֪ͨ��
		HWND GetChildHandle();	//�Ӵ��ھ��
	};
private:
	class handle_hash
	{
	public:
		enum
		{
			bucket_size = 4,
			min_buckets = 8
		};
		handle_hash();
		size_t operator()(const HANDLE& handle) const;
		bool operator()(const HANDLE& handle1, const HANDLE& handle2) const;
	};
	typedef std::hash_map<HANDLE, SMessageHandler *, handle_hash> HandleHandlerMap;
	typedef MessageParam handle_msg;
public:
	//��ͨ����
	static LRESULT CALLBACK MessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static WNDPROC GetMessageHandlerProc();

	static LRESULT CALLBACK ParentMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ChildMessageHandlerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
protected:
	static HandleHandlerMap s_WndHandlerMap;		//��¼ȫ�ָ�������Ϣ��map
	HandleHandlerMap m_ChildWndMap;				//��¼ĳ���������µ�����Ϣmap
protected:
	WNDPROC m_pWndProc;

protected:
	//���󷽷�
	virtual LRESULT CALLBACK OnProc(MessageParam param);

public:
	SMessageHandler();
	virtual ~SMessageHandler();
public:
	//ȡ�ü�¼��
	HandleHandlerMap *GetWndHandlerMap();

	//ȡ����Ϣ������
	WNDPROC GetMessageProc();

	//������Ϣ������
	void SetMessageProc(WNDPROC pWndProc);

	//�ı���Ϣ������
	WNDPROC ChangeMessageProc(HWND hWnd, WNDPROC pWndProc);

	//��������Ϣ����ص�����
	LRESULT CALLBACK Proc(MessageParam param);
	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	/*���²����ʺϸ�����*/
	//�������໯
	bool SubClass(HWND hwnd);

	//���ڷ����໯
	void UnSubClass(HWND hwnd);
	void UnSubClass(SMessageHandler *handler);

	//����Ӵ���
	bool SubChildClass(HANDLE handle, SMessageHandler *parent);

	//�Ƴ��Ӵ���
	void UnSubChildClass(HANDLE handle, SMessageHandler *parent);

};

#endif