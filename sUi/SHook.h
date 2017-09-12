/**
* SHook类
* HHOOK封装类
* @author ZeroX
* @version v1.0 05/09/2017
*/

#include "../sCore/SObject.h"
#ifndef _SHOOK_H_
#define _SHOOK_H_
#include <Windows.h>
#include <functional>
#include <map>
#include <vector>
class SHook
{
public:
	//卸载钩子
	static bool UninstallKbHook(HHOOK &hHook);
	//安装钩子
	static bool InstallKbHook(HHOOK &hHook, int idHook, DWORD dwThreadId, HINSTANCE hInstance, HOOKPROC lpfn);

	static DWORD GetCurrentThreadId();
private:
	static std::map<int, std::vector<SHook *> *> g_hooklist;
	/* 各种钩子的回调函数 */

	static LRESULT CALLBACK CallWndProcProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_CALLWNDPROC
	static LRESULT CALLBACK CallWndProcRetProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_CALLWNDPROCRET
	static LRESULT CALLBACK GetMessageProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_GETMESSAGE
	static LRESULT CALLBACK KeyBoardProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_KEYBOARD
	static LRESULT CALLBACK KeyBoardLLProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_KEYBOARD_LL
	static LRESULT CALLBACK MouseProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_MOUSE
	static LRESULT CALLBACK MouseLLProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_MOUSE_LL
	static LRESULT CALLBACK MsgFilterProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_MSGFILTER
	static LRESULT CALLBACK SysMsgFilterProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_SYSMSGFILTER
	static LRESULT CALLBACK DebugProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_DEBUG 
	static LRESULT CALLBACK JournalRecordProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_JOURNALRECORD
	static LRESULT CALLBACK JournalPlaybackProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_JOURNALPLAYBACK 
	static LRESULT CALLBACK ShellProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_SHELL
	static LRESULT CALLBACK ForegroundIdleProc(INT nCode, WPARAM wParam, LPARAM lParam);	//WH_FOREGROUNDIDLE


	//消息分拣
	static void SortProc(int idHook, HOOKPROC *lpfn);
	static LRESULT ShellChildProc(int idHook, INT &nCode, WPARAM &wParam, LPARAM &lParam);
private:
	std::function<void(INT, WPARAM, LPARAM)> m_fProc;
	HHOOK	m_hHook;	//记录 HOOK 
	int m_nIdHook;		//HOOK类型
protected:
	void OnProc(INT nCode, WPARAM wParam, LPARAM lParam);

public:
	SHook();
	~SHook();

	bool Install(int idHook, DWORD dwThreadId, HINSTANCE hInstance = NULL, HOOKPROC lpfn = NULL);
	bool Install(int idHook, BOOL bGlobal=FALSE, HINSTANCE hInstance = NULL, HOOKPROC lpfn = NULL);
	bool Uninstall();

	void Proc(std::function<void(INT nCode, WPARAM wParam, LPARAM lParam)> fProc);
};

#endif