#include "Main.h"

XAGUI::MouseButton MouseButtonToXAGUI(sf::Mouse::Button mouseButton)
{
	switch (mouseButton)
	{
		case sf::Mouse::Left:	return MOUSE_BUTTON_LEFT;
		case sf::Mouse::Middle: return MOUSE_BUTTON_MIDDLE;
		case sf::Mouse::Right:	return MOUSE_BUTTON_RIGHT;
	}
	return MOUSE_BUTTON_COUNT;
}

XAGUI::Key KeyToXAGUI(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Return:		return XAGUI::KEY_RETURN;
		case sf::Keyboard::Left:		return XAGUI::KEY_LEFT;
		case sf::Keyboard::Right:		return XAGUI::KEY_RIGHT;
		case sf::Keyboard::BackSpace:	return XAGUI::KEY_BACKSPACE;
		default: break;
	}
	return XAGUI::KEY_COUNT;
}