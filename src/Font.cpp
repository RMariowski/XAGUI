#include <XAGUI.h>

namespace XAGUI
{

Font::Font()
	: _size(0)
{ }

bool Font::Load(cchar* name, uint8_t size)
{
	_name = name;
	_size = size;
	return true;
}

};
