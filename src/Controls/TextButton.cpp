#include <XAGUI.h>

namespace XAGUI
{

TextButton::TextButton()
{
	_label = new Label();
	GetLabel()->SetAlignment(ALIGNMENT_VCENTER_HCENTER);
	GetLabel()->SetConsumeMouseEvents(false);
	AddChild(GetLabel());
}

void TextButton::SetText(cchar* fontName, uint8_t fontSize, cchar* text)
{ GetLabel()->SetText(fontName, fontSize, text); }

};