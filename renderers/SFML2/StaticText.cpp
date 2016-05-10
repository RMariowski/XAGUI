#include "Main.h"

StaticText::StaticText() { _text = new sf::Text(); }

StaticText::~StaticText() { Release(); }

void StaticText::Release() 
{
	SAFE_DELETE(_text);
}

void StaticText::SetFont(cchar* name, uint8_t size)
{
	_font = XAGUI::XAGUI::GetRenderer()->GetFont(name, size);
	if (_font == 0) return;
	Get()->setFont(*static_cast<Font*>(GetFont())->Get());
	SetText(GetText());
}

void StaticText::SetText(cchar* text)
{
	XAGUI::StaticText::SetText(text);
	Get()->setString(text);
}

void StaticText::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	XAGUI::StaticText::SetColor(red, green, blue, alpha);
	Get()->setColor(sf::Color(red, green, blue, alpha));
}
