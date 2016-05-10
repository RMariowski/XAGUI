#include "Main.h"

Texture::Texture()
	: _texture(0)
{ }

Texture::~Texture() { Release(); }

bool Texture::Load(cchar* name)
{
	SDL_Surface* surface = IMG_Load(name);
	if (surface == 0) return false;
	_texture = SDL_CreateTextureFromSurface(static_cast<Renderer*>(XAGUI::XAGUI::GetRenderer())->Get(), 
		surface);
    if (Get() == 0) return false;
	return XAGUI::Texture::Load(name);
}

bool Texture::CreateTarget(XAGUI::SizeType width, XAGUI::SizeType height)
{
	_texture = SDL_CreateTexture(static_cast<Renderer*>(XAGUI::XAGUI::GetRenderer())->Get(), 
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (Get() == 0) return false;
	SDL_SetTextureBlendMode(Get(), SDL_BLENDMODE_BLEND); 
	return true;
}

void Texture::Release() { SDL_DestroyTexture(_texture); }