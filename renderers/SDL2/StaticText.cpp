#include "Main.h"

StaticText::StaticText() 
	: _texture(0)
{ }

StaticText::~StaticText() { Release(); }

void StaticText::Release() { SDL_DestroyTexture(_texture); }

void StaticText::SetFont(cchar* name, uint8_t size)
{
	_font = XAGUI::XAGUI::GetRenderer()->GetFont(name, size);
	SetText(GetText());
}

void StaticText::SetText(cchar* text)
{
	XAGUI::StaticText::SetText(text);

	Release();

	SDL_Color color = { GetRed(), GetGreen(), GetBlue(), GetAlpha() };
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(static_cast<Font*>(GetFont())->Get(), GetText(),
		color, GetFont()->GetTextWidth(text));
	_texture = SDL_CreateTextureFromSurface(static_cast<Renderer*>(XAGUI::XAGUI::GetRenderer())->Get(), 
		surface);
	SDL_SetTextureAlphaMod(_texture, color.a);
	SDL_FreeSurface(surface);
}

void StaticText::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	XAGUI::StaticText::SetColor(red, green, blue, alpha);
	SetText(GetText());
}
