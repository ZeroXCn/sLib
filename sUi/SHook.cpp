#include "SHook.h"
std::map<int, std::vector<SHook *> *> SHook::g_hooklist;

LRESULT CALLBACK SHook::CallWndProcProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_CALLWNDPROC
	return SHook::ShellChildProc(WH_CALLWNDPROC, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::CallWndProcRetProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_CALLWNDPROCRET
	return SHook::ShellChildProc(WH_CALLWNDPROCRET, nCode, wParam, lParam);
}

LRESULT CALLBACK SHook::GetMessageProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_GETMESSAGE
	return SHook::ShellChildProc(WH_GETMESSAGE, nCode, wParam, lParam);
}

LRESULT CALLBACK SHook::KeyBoardProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_KEYBOARD
	return SHook::ShellChildProc(WH_KEYBOARD, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::KeyBoardLLProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_KEYBOARD_LL
	return SHook::ShellChildProc(WH_KEYBOARD_LL, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::MouseProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_MOUSE
	return SHook::ShellChildProc(WH_MOUSE, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::MouseLLProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_MOUSE_LL
	return SHook::ShellChildProc(WH_MOUSE_LL, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::MsgFilterProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_MSGFILTER
	return SHook::ShellChildProc(WH_MSGFILTER, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::SysMsgFilterProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_SYSMSGFILTER
	return SHook::ShellChildProc(WH_SYSMSGFILTER, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::DebugProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_DEBUG 
	return SHook::ShellChildProc(WH_DEBUG, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::JournalRecordProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_JOURNALRECORD
	return SHook::ShellChildProc(WH_JOURNALRECORD, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::JournalPlaybackProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_JOURNALPLAYBACK 
	return SHook::ShellChildProc(WH_JOURNALPLAYBACK, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::ShellProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_SHELL
	return SHook::ShellChildProc(WH_SHELL, nCode, wParam, lParam);
}
LRESULT CALLBACK SHook::ForegroundIdleProc(INT nCode, WPARAM wParam, LPARAM lParam){	//WH_FOREGROUNDIDLE
	return SHook::ShellChildProc(WH_FOREGROUNDIDLE, nCode, wParam, lParam);
}

LRESULT SHook::ShellChildProc(int idHook, INT &nCode, WPARAM &wParam, LPARAM &lParam)
{
	auto ita = g_hooklist.find(idHook);
	if (ita != g_hooklist.end()){
		for (auto itb : *ita->second)
			itb->OnProc(nCode, wParam, lParam);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void SHook::SortProc(int idHook, HOOKPROC *lpfn)
{
	if (*lpfn != NULL)return;
	switch (idHook)
	{
	case WH_CALLWNDPROC:
		*lpfn = SHook::CallWndProcProc;
		break;
	case WH_CALLWNDPROCRET:
		*lpfn = SHook::CallWndProcRetProc;
		break;
	case WH_GETMESSAGE:
		*lpfn = SHook::GetMessageProc;
		break;
	case WH_KEYBOARD:
		*lpfn = SHook::KeyBoardProc;
		break;
	case WH_KEYBOARD_LL:
		*lpfn = SHook::KeyBoardLLProc;
		break;
	case WH_MOUSE:
		*lpfn = SHook::MouseProc;
		break;
	case WH_MOUSE_LL:
		*lpfn = SHook::MouseLLProc;
	case WH_MSGFILTER:
		*lpfn = SHook::MsgFilterProc;
		break;
	case WH_SYSMSGFILTER:
		*lpfn = SHook::SysMsgFilterProc;
		break;
	case WH_DEBUG:
		*lpfn = SHook::DebugProc;
		break;
	case WH_JOURNALRECORD:
		*lpfn = SHook::JournalRecordProc;
		break;
	case WH_JOURNALPLAYBACK:
		*lpfn = SHook::JournalPlaybackProc;
		break;
	case WH_SHELL:
		*lpfn = SHook::ShellProc;
		break;
	case WH_FOREGROUNDIDLE:
		*lpfn = SHook::ForegroundIdleProc;
		break;

	}
}

/////////////////////////////////////
//卸载钩子
bool SHook::UninstallKbHook(HHOOK &hHook)
{
	bool fOk = true;
	if (hHook) {
		fOk = UnhookWindowsHookEx(hHook) ? true : false;
		hHook = nullptr;
	}

	return(fOk);
}
//安装钩子
bool SHook::InstallKbHook(HHOOK &hHook, int idHook, DWORD dwThreadId, HINSTANCE hInstance, HOOKPROC lpfn)
{
	if (hHook)
		UninstallKbHook(hHook);//LowLevelMouseProc

	hHook = ::SetWindowsHookEx(idHook,	//值监控本模块 1294
		lpfn, hInstance, dwThreadId);	//最后一个参数为0,则为全局钩子

	return(hHook != NULL);
}


DWORD SHook::GetCurrentThreadId()
{
	return ::GetCurrentThreadId();
}
//////////////////////////////////////
void SHook::OnProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	m_fProc(nCode, wParam, lParam);
}


SHook::SHook() : m_hHook(nullptr)
{
	m_fProc = [=](INT nCode, WPARAM wParam, LPARAM lParam)
	{
		
	};
}

SHook::~SHook()
{
	UninstallKbHook(m_hHook);
}

bool SHook::Install(int idHook, DWORD dwThreadId , HINSTANCE hInstance, HOOKPROC lpfn)
{
	SortProc(idHook, &lpfn);
	bool ret = InstallKbHook(m_hHook, idHook, dwThreadId, hInstance, lpfn);
	m_nIdHook = idHook;

	//if (lpfn == NULL){
		if (m_hHook){
			auto ita = g_hooklist.find(idHook);
			std::vector<SHook *> *idlist = nullptr;
			if (ita == g_hooklist.end()){
				idlist = new std::vector<SHook *>();
				g_hooklist.insert(std::pair<int, std::vector<SHook *> *>(m_nIdHook, idlist));
			}else{
				idlist = ita->second;
			}
			idlist->push_back(this);
			
		}
	//}
	return ret;
}

bool SHook::Install(int idHook, BOOL bGlobal, HINSTANCE hInstance, HOOKPROC lpfn )
{
	if (hInstance)
		return Install(idHook, 0, hInstance, lpfn);
	else
		return Install(idHook, ::GetCurrentThreadId(), hInstance, lpfn);
}
bool SHook::Uninstall()
{
	if (m_hHook == nullptr) return true;
	auto ita = g_hooklist.find(m_nIdHook);
	std::vector<SHook *> *idlist = nullptr;
	if (ita != g_hooklist.end()){
		idlist = ita->second;
		for (auto itb = idlist->begin(); itb != idlist->end();itb++){
			if (*itb == this){
				idlist->erase(itb);
				break;
			}
		}
	}
	return UninstallKbHook(m_hHook);
}
/////////////////////////////////////
void SHook::Proc(std::function<void(INT nCode, WPARAM wParam, LPARAM lParam)> fProc)
{
	m_fProc = fProc;
}
