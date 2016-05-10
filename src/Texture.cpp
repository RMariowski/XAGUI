#include <XAGUI.h>

namespace XAGUI
{

Texture::Texture() { }

bool Texture::Load(cchar* name)
{
	_name = name;
	return true;
}

};