#include <XAGUI.h>

namespace XAGUI
{

Container::Container() { }

void Container::Render()
{
	if (IsVisible())
		Control::Render();
}

};