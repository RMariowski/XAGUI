#include <XAGUI.h>

namespace XAGUI
{

Layout::Layout() { }

void Layout::AddControl(Control* control)
{ 
	_controls.push_back(control);
	Update();
}

void Layout::RemoveControl(size_t i)
{
	_controls.erase(_controls.begin() + i); 
	Update();
}

void Layout::RemoveControl(Control* control)
{
	for (size_t i = 0; i < GetControlsCount(); i++)
	{
		if (control == _controls[i])
		{
			_controls.erase(_controls.begin() + i); 
			break;
		}
	}
	Update();
}


}