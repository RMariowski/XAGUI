#include <XAGUI.h>

namespace XAGUI
{

StaticText::StaticText()
	: _font(0), _red(255), _green(255), _blue(255), _alpha(255)
{ }

void StaticText::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha;
}

};