#include <XAGUI.h>

namespace XAGUI
{

Label::Label()
	: _staticText(0), _flip(FLIP_NONE)
{ }

Label::~Label()
{ 
	SAFE_DELETE(_staticText);	
}

void Label::Render()
{
	if (!IsVisible()) return;
	
	XAGUI::GetRenderer()->Render(GetStaticText(), GetAbsX(), GetAbsY(), GetFlip());
	Control::Render();
}

void Label::SetFont(cchar* name, uint8_t size)
{
	if (GetStaticText() != 0)
	{
		_staticText = XAGUI::GetRenderer()->GetStaticText(name, size, GetText());
	}
	else _staticText = XAGUI::GetRenderer()->GetStaticText(name, size, "");
	
	SetWidth(0);
	SetHeight(0);
}

void Label::SetText(cchar* text)
{
	if (GetStaticText() == 0) return;
	
	GetStaticText()->SetText(text);
	SetWidth(0);
	SetHeight(0);
	XAGUI::SetRequestRedraw(true);
}

void Label::SetText(cchar* fontName, uint8_t fontSize, cchar* text)
{
	_staticText = XAGUI::GetRenderer()->GetStaticText(fontName, fontSize, text);
	SetWidth(0);
	SetHeight(0);
}

void Label::SetWidth(SizeType width)
{ Control::SetWidth(_staticText->GetFont()->GetTextWidth(GetStaticText()->GetText())); }

void Label::SetHeight(SizeType height)
{ Control::SetHeight(_staticText->GetFont()->GetTextHeight(GetStaticText()->GetText())); }

void Label::SetState(ControlState state)
{
	Control::SetState(state);
	GetStaticText()->SetColor(GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()),
		GetColorAlpha(GetState()));
}

void Label::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	Control::SetColor(red, green, blue, alpha);
	GetStaticText()->SetColor(red, green, blue, alpha);
}

void Label::SetColor(ControlState controlState, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	Control::SetColor(controlState, red, green, blue, alpha);

	// Label shouldn't change color when we set color of other state than label is.
	if (GetState() == controlState)
		GetStaticText()->SetColor(red, green, blue, alpha);
}

void Label::SetFlip(Flip flip)
{
	if (GetFlip() == flip) return;
	
	_flip = flip; 
	XAGUI::SetRequestRedraw(true);
}

};