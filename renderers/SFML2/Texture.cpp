#include "Main.h"

Texture::Texture() { _texture = new sf::Texture(); }

Texture::~Texture() { Release(); }

bool Texture::Load(cchar* name)
{
	if (!Get()->loadFromFile(name)) return false;
	return XAGUI::Texture::Load(name);
}

void Texture::Release() 
{ 
	SAFE_DELETE(_texture);
}