#include "SLabel.h"



BOOL SLabel::Create()
{
	SetClassName(TEXT("Label"));
	SetTitle(TEXT("Label"));
	SetStyle(WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER);
	SetPos(0, 0);
	SetWidth(0);
	SetHeight(0);

	return SWidget::Create();

}