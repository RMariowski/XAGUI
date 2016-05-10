#include "Main.h"

XAGUI::MouseButton MouseButtonToXAGUI(uint8_t mouseButton)
{
	switch (mouseButton)
	{
		case SDL_BUTTON_LEFT:	return MOUSE_BUTTON_LEFT;
		case SDL_BUTTON_MIDDLE:	return MOUSE_BUTTON_MIDDLE;
		case SDL_BUTTON_RIGHT:	return MOUSE_BUTTON_RIGHT;
		default: break;
	}
	return MOUSE_BUTTON_COUNT;
}

XAGUI::Key KeyToXAGUI(SDL_Scancode key)
{
	switch (key)
	{
		case SDL_SCANCODE_RETURN:		return XAGUI::KEY_RETURN;
		case SDL_SCANCODE_LEFT:			return XAGUI::KEY_LEFT;
		case SDL_SCANCODE_RIGHT:		return XAGUI::KEY_RIGHT;
		case SDL_SCANCODE_BACKSPACE:	return XAGUI::KEY_BACKSPACE;
		default: break;
	}
	return XAGUI::KEY_COUNT;
}