#include "../../sUi/SApplication.h"
#include "../../sUi/SWindow.h"
#include "../../sUi/SButton.h"
#include "../../sUi/SMenuBar.h"
#include "../../sUI/SMessageBox.h"
class MyWindow :public SWindow
{
private:
	SButton *mybuttom;
	SMenuBar *mymenu;
public:
	BOOL MyWindow::OnCreate(ActivityParam &param)
	{
		mybuttom = new SButton(this, TEXT("�����"));
		mybuttom->Create();
		mybuttom->SubChildClass(mybuttom->GetWnd().GetHandle(), this);
		mybuttom->OnClicked([=](){
			this->func();
		});

		mymenu = new SMenuBar(this);
		mymenu->NewMenu(TEXT("File"))
			.AddItem(TEXT("New"), 40001)
			.AddItem(TEXT("Open"), 40002)
			.AddSeparator()
			.AddItem(TEXT("Quit"), 40003);
		mymenu->NewMenu(TEXT("Edit"))
			.AddItem(TEXT("Copy"), 40004)
			.AddItem(TEXT("Paste"), 40005);

		mymenu->OnProc([=](int id){
			switch (id)
			{
			case 40001:
				this->func();
				break;
			default:
				break;
			}
		});
		mymenu->Create();
	}

	void func()
	{
		SMessageBox::Information(this->GetWnd(), TEXT("��Ϣ"), TEXT("Don't touch me,fuck off!!"));
	}

	void OnPaint(SDc dc)
	{
		//˫����
		SBufferDc bdc(dc.GetHandle(), SWindow::GetWidth(), SWindow::GetHeight());
		
		SFont font;
		font.Create(44, TEXT("΢���ź�"));
		bdc.SetFont(font.GetHandle());
		bdc.DrawString(TEXT("Ϧ�����޺�,ֻ�ǽ��ƻ�"), 100, 100, WHITE_COLOR);

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

