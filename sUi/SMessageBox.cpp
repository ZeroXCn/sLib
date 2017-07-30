#include "SMessageBox.h"
int SMessageBox::Dialog(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText,  uButtons);
}

int SMessageBox::Information(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText, MB_ICONINFORMATION | uButtons);
}
int SMessageBox::Warning(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText, MB_ICONWARNING | uButtons);
}
int SMessageBox::Critical(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText, MB_ICONSTOP | uButtons);
}

int SMessageBox::Question(SWnd sWnd, LPTSTR lpTitle, LPTSTR lpText, UINT uButtons)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText, MB_ICONQUESTION | uButtons);
}
int SMessageBox::About(SWnd sWnd, LPTSTR lpText, LPTSTR lpTitle)
{
	return ::MessageBox(sWnd.GetWnd(), lpTitle, lpText, MB_OK);
}