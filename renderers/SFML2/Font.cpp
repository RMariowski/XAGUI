#include "Main.h"

Font::Font() { _font = new sf::Font(); }

Font::~Font() { Release(); }

bool Font::Load(cchar* name, uint8_t size)
{
	if (!_font->loadFromFile(name)) return false;
	return XAGUI::Font::Load(name, size);
}

void Font::Release() 
{ 
	SAFE_DELETE(_font);
}

XAGUI::SizeType Font::GetTextWidth(cchar* text) const
{
	sf::Text staticText(text, *Get(), GetSize()); 
	return static_cast<XAGUI::SizeType>(staticText.getLocalBounds().width);
}

XAGUI::SizeType Font::GetTextHeight(cchar* text) const
{
	sf::Text staticText(text, *Get(), GetSize()); 
	return static_cast<XAGUI::SizeType>(staticText.getLocalBounds().height);
}