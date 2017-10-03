#include <sUi/SWindow.h>

class MyWindow :public SWindow
{
public:
	MyWindow()
	{
		SetTitle(TEXT("Window"));
		SetSize(800, 600);
	}
	BOOL OnInit(SWnd sWnd, SInstance sInstance){ ; }
	void OnPaint(SDc sdc){ ; }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SApplication a(hInstance, hPrevInstance, pScmdline, iCmdshow);
	MyWindow w;
	
	w.DoModal();

	return a.Exec();
}