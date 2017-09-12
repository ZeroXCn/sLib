#include <sUi\SWindow.h>
#include <sUi\SButton.h>
#include <sUi\SLabel.h>
#include <sUi\SEditText.h>
#include <sUi\SMessageBox.h>
#include <sUi\SDialog.h>
#include <sCore\SDebug.h>
#include <sHelper\SMathHelper.hpp>
#include <sUi\SMenuBar.h>
#include <sParser\SJson.h>
#include <sParser\SXml.h>
#include <sParser\SIni.h>
#include <sParser\SInf.h>
#include <ximage.h>

class MyWindow :public SWindow
{
public:
	CxImage aaa;
	SBitmap bit;
	SBitmap dra;

	SButton *m_buttom=NULL;
	SEditText *m_text = NULL;
	SLabel *m_label = NULL;
	SMenuBar *m_menubar = NULL;

	int m_nMouseX = 0, m_nMouseY = 0;
public:
	MyWindow()
	{
		aaa.Load(TEXT("D:/startscreen.jpg"));
		bit.Load(TEXT("D:/4.bmp"));

		dra.Load(TEXT("D:/dra.bmp"));
		m_buttom = new SButton(this, TEXT("别点我"));
		m_buttom->OnClicked([=](){
			//m_buttom->SetText(TEXT("你好"));
			this->func();
		});

		m_text = new SEditText(this);
		m_text->SetPos(20, 100);


		m_menubar = new SMenuBar(this);

		m_menubar->NewMenu(TEXT("File"))
			.AddItem(TEXT("New"), 40001)
			.AddItem(TEXT("Open"), 40002)
			.AddSeparator()
			.AddItem(TEXT("Quit"), 40003);
		m_menubar->NewMenu(TEXT("Edit"))
			.AddItem(TEXT("Copy"), 40004)
			.AddItem(TEXT("Paste"), 40005);

		m_menubar->OnProc([=](int id){
			switch (id)
			{
			case 40001:
				this->func();
				break;
			case 40003:
				this->Destroy();
			}
		});
	}
	~MyWindow()
	{
		delete m_buttom;
		delete m_text;
		delete m_label;
		delete m_menubar;

	}
public:

	void OnRunning()
	{
		//RePaint();
		SWindow::OnRunning();

	}
	void OnMouseMove(InputParam param)
	{
		m_nMouseX = param.GetMouseX();
		m_nMouseY = param.GetMouseY();
	}

	void OnPaint(SDc dc)
	{
		SBufferDc bdc(dc, SWindow::GetWidth(), SWindow::GetHeight());
		bdc.Symmetry(128,64);
		bdc.DrawImage(bit, 0, 0);
		bdc.RestoreWorldTransform();
		SFont font;
		SFont oldfront;
		font.Create(44, TEXT("微软雅黑"));
		oldfront=bdc.SetFont(font);
		bdc.DrawString(TEXT("夕阳无限好,只是近黄昏"), 100, 100, WHITE_COLOR);
		bdc.DrawString(SString::Format(TEXT("%d,%d"), GetClientWidth(), GetClientHeight()), 100, 200, WHITE_COLOR);
		font.Delete();
		bdc.SetFont(oldfront);

		bdc.Paint();
	}

	void func()
	{
		SInfDocument rr;
		rr.Load("D:/Configuration.ini");

		SString ret(rr["XSSettings"]["Font"].ToStrString());
		SMessageBox::Information(NULL, TEXT("tret"), ret.str());

	}

};

