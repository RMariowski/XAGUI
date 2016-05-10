#ifndef XAGUI_TEXT_BUTTON_H
#define XAGUI_TEXT_BUTTON_H

XAGUI_EXPORT class TextButton : public Button
{
	public:

		TextButton();

		virtual inline Label* GetLabel() const { return _label; }

		virtual void SetText(cchar* fontName, uint8_t fontSize, cchar* text);

	protected:

		Label* _label;
};

#endif
