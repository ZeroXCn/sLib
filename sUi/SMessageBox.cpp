#include "SMessageBox.h"
int SMessageBox::Dialog(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, uButtons);
}

int SMessageBox::Information(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONINFORMATION | uButtons);
}
int SMessageBox::Warning(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONWARNING | uButtons);
}
int SMessageBox::Critical(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONSTOP | uButtons);
}

int SMessageBox::Question(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_ICONQUESTION | uButtons);
}
int SMessageBox::About(SWnd sWnd, LPTSTR lpText, LPTSTR lpTitle)
{
	return ::MessageBox(sWnd.GetHandle(), lpText, lpTitle, MB_OK);
}