#include <XAGUI.h>

namespace XAGUI
{

Renderer* XAGUI::_renderer = 0;
Texture* XAGUI::_skin = 0;

bool XAGUI::_redraw = true;
#if defined(__ANDROID__) || defined(__IPHONEOS__)
bool XAGUI::_onScreenKeyboardShowed = false;
void (*XAGUI::_showOnScreenKeyboard)();
void (*XAGUI::_hideOnScreenKeyboard)();

void XAGUI::ShowOnScreenKeyboard()
{
	// We don't want to restart text input.
	if (IsOnScreenKeyboardShowed() || _showOnScreenKeyboard == 0) return;

	_showOnScreenKeyboard();
	_onScreenKeyboardShowed = true;
}

void XAGUI::HideOnScreenKeyboard()
{
	// We don't want to restop text input.
	if (!IsOnScreenKeyboardShowed() || _hideOnScreenKeyboard == 0) return;

	_hideOnScreenKeyboard();
	_onScreenKeyboardShowed = false;
}
#endif
};