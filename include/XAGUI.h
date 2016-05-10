#ifndef XANDEV_AWESOME_GUI_H
#define XANDEV_AWESOME_GUI_H

#include <vector>

#include <xaih/xaih.h>
#include <FastDelegate/FastDelegate.h>
#include <utf8cpp/utf8.h>
#include <stdint.h>

#if defined (XAGUI_COMPILE_DLL)
#ifdef _WIN32
#if defined (__GNUC__)
#define XAGUI_EXPORT __attribute__((dllexport))
#else
#define XAGUI_EXPORT __declspec(dllexport)
#endif
#endif
#elif defined (XAGUI_DLL)
#ifdef _WIN32
#ifdef __GNUC__
#define XAGUI_EXPORT __attribute__((dllimport))
#else
#define XAGUI_EXPORT __declspec(dllimport)
#endif
#endif
#else
#define XAGUI_EXPORT
#endif

namespace XAGUI
{

typedef int32_t MousePosType;
typedef int16_t PosType;
typedef uint16_t SizeType;
typedef uint16_t SrcPosType;
typedef uint16_t SrcSizeType;

#define CONTROL_STATE_NORMAL 0
#define CONTROL_STATE_HOVER 1
#define CONTROL_STATE_ACTIVE 2
#define CONTROL_STATE_PRESSED CONTROL_STATE_ACTIVE
#define CONTROL_STATE_DISABLED 3
#define CONTROL_STATE_COUNT 4
typedef uint8_t ControlState;

#define ALIGNMENT_LEFT 0x01
#define ALIGNMENT_HCENTER 0x02
#define ALIGNMENT_RIGHT 0x04
#define ALIGNMENT_TOP 0x10
#define ALIGNMENT_VCENTER 0x20
#define ALIGNMENT_BOTTOM 0x40
#define ALIGNMENT_TOP_LEFT (ALIGNMENT_TOP | ALIGNMENT_LEFT)
#define ALIGNMENT_VCENTER_LEFT (ALIGNMENT_VCENTER | ALIGNMENT_LEFT)
#define ALIGNMENT_BOTTOM_LEFT (ALIGNMENT_BOTTOM | ALIGNMENT_LEFT)
#define ALIGNMENT_TOP_HCENTER (ALIGNMENT_TOP | ALIGNMENT_HCENTER)
#define ALIGNMENT_VCENTER_HCENTER (ALIGNMENT_VCENTER | ALIGNMENT_HCENTER)
#define ALIGNMENT_CENTER ALIGNMENT_VCENTER_HCENTER
#define ALIGNMENT_BOTTOM_HCENTER (ALIGNMENT_BOTTOM | ALIGNMENT_HCENTER)
#define ALIGNMENT_TOP_RIGHT (ALIGNMENT_TOP | ALIGNMENT_RIGHT)
#define ALIGNMENT_VCENTER_RIGHT (ALIGNMENT_VCENTER | ALIGNMENT_RIGHT)
#define ALIGNMENT_BOTTOM_RIGHT (ALIGNMENT_BOTTOM | ALIGNMENT_RIGHT)
typedef uint8_t Alignment;

#define FLIP_NONE 0x00
#define FLIP_HORIZONTAL 0x01
#define FLIP_VERTICAL 0x02
#define FLIP_HORIZONTAL_VERTICAL (FLIP_HORIZONTAL | FLIP_VERTICAL)
typedef int32_t Flip;

#define ORIENTATION_HORIZONTAL 0
#define ORIENTATION_VERTICAL 1
typedef uint8_t Orientation;

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_MIDDLE 1
#define MOUSE_BUTTON_RIGHT 2
#define MOUSE_BUTTON_COUNT 3
typedef uint8_t MouseButton;

enum Key
{
	KEY_RETURN,
	KEY_TAB,
	KEY_BACKSPACE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_COUNT
};

#define TouchMoveEvent MouseMoveEvent
#define TouchDownEvent(x,y) MouseButtonDownEvent(x,y,XAGUI::MOUSE_BUTTON_LEFT)
#define TouchUpEvent(x,y) MouseButtonUpEvent(x,y,XAGUI::MOUSE_BUTTON_LEFT)

#include <Font.h>
#include <StaticText.h>
#include <Texture.h>
#include <Renderer.h>
#include <Layouts/Layout.h>
#include <Layouts/HorizontalLayout.h>
#include <Layouts/VerticalLayout.h>
#include <Controls/ControlBase.h>
#include <Controls/Control.h>
#include <Controls/Container.h>
#include <Controls/Label.h>
#include <Controls/Button.h>
#include <Controls/Slider.h>
#include <Controls/ScrollBar.h>
#include <Controls/ScrollableControl.h>
#include <Controls/TextBox.h>
#include <Controls/ComboBox.h>
#include <Controls/CheckBox.h>
#include <Controls/ListBox.h>
#include <Controls/TextButton.h>
#include <Controls/PictureBox.h>
#include <Controls/RadioButton.h>
#include <Controls/AnalogStick.h>
#include <Controls/ProgressBar.h>
#include <Controls/PasswordTextBox.h>
#include <Controls/MultilineTextBox.h>
#include <Controls/TabPage.h>
#include <Controls/TabControl.h>
#include <Controls/Window.h>
#include <Controls/Form.h>

XAGUI_EXPORT class XAGUI
{
	public:

		static inline bool IsRedrawNeeded() { return _redraw; }

		static inline Renderer* GetRenderer() { return _renderer; }

		static inline Texture* GetSkin() { return _skin; }

		static inline void SetRenderer(Renderer* renderer) { _renderer = renderer; }

		static inline void SetSkin(Texture* skin) { _skin = skin; }
		
		static inline void SetRequestRedraw(bool needRedraw) { _redraw = needRedraw; }

#if defined(__ANDROID__) || defined(__IPHONEOS__)
		static void ShowOnScreenKeyboard();

		static void HideOnScreenKeyboard();

		static inline bool IsOnScreenKeyboardShowed() { return _onScreenKeyboardShowed; }

		static inline void SetShowOnScreenKeyboard(void (*showOnScreenKeyboard)()) 
		{ _showOnScreenKeyboard = showOnScreenKeyboard; }

		static inline void SetHideOnScreenKeyboard(void (*hideOnScreenKeyboard)()) 
		{ _hideOnScreenKeyboard = hideOnScreenKeyboard; }

#endif

	private:

		static bool _redraw;
#if defined(__ANDROID__) || defined(__IPHONEOS__)
		static bool _onScreenKeyboardShowed; 
		static void (*_showOnScreenKeyboard)();
		static void (*_hideOnScreenKeyboard)();
#endif

		static Renderer* _renderer;
		static Texture* _skin;
};

};

#endif