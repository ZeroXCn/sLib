#include "../../sUi/SApplication.h"
#include "../../sUi/SWindow.h"
#include "../../sUi/SButton.h"
#include "../../sUI/SMessageBox.h"
class MyWindow :public SWindow
{
private:
	SButton *mybuttom;
public:
	BOOL MyWindow::OnCreate(ActivityParam &param)
	{
		mybuttom = new SButton(this, TEXT("别点我"));
		mybuttom->Create();
		mybuttom->SubChildClass(mybuttom->GetWnd().GetWnd(), this);
		mybuttom->OnClicked([=](){
			this->func();
		});
	}

	void func()
	{
		SMessageBox::Information(this->GetWnd(), TEXT("信息"), TEXT("Don't touch me,fuck off!!"));
	}

	void OnPaint(SDc dc)
	{
		//双缓冲
		SBufferDc bdc(dc.GetDC(), SWindow::GetWidth(), SWindow::GetHeight());
		
		SFont font;
		font.Create(44, TEXT("微软雅黑"));
		bdc.SetFont(font.GetFont());
		bdc.DrawString(TEXT("夕阳无限好,只是近黄昏"), 100, 100, WHITE_COLOR);

		font.Delete();



	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SApplication a(hInstance, hPrevInstance, pScmdline, iCmdshow);
	MyWindow w;
	w.SetAttribute(TEXT("win32"));

	w.DoModal();


	return a.Exec();
}

