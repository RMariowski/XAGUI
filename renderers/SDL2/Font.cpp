#include "Main.h"

Font::Font()
	: _font(0)
{}

Font::~Font() { Release(); }

bool Font::Load(cchar* name, uint8_t size)
{
	_font = TTF_OpenFont(name, size);
	if (Get() == 0) return false;
	return XAGUI::Font::Load(name, size);
}

void Font::Release() { TTF_CloseFont(_font); }

XAGUI::SizeType Font::GetTextWidth(cchar* text) const
{
	int32_t width;
	TTF_SizeUTF8(Get(), text, &width, 0);
	return width;
}

XAGUI::SizeType Font::GetTextHeight(cchar* text) const
{
	int32_t height;
	TTF_SizeUTF8(Get(), text, 0, &height);
	return height;
}