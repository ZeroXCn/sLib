#include "sUi/SWindow.h"
#include "sCore/SDebug.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SApplication a(hInstance, hPrevInstance, pScmdline, iCmdshow);
	SWindow w; 
	w.Show();

	SWindow v;
	v.SetWindowAttribute(TEXT("wijj"));
	v.Show();


	return a.Exec();


}