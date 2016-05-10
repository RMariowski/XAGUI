#ifndef XAGUI_FORM_H
#define XAGUI_FORM_H

XAGUI_EXPORT class Form : public PictureBox
{
	public:

		Form();

		virtual ~Form();

		virtual void Render();

		virtual void MouseMoveEvent(MousePosType x, MousePosType y);

		virtual bool MouseButtonDownEvent(MousePosType x, MousePosType y, MouseButton button);
		
		virtual void MouseButtonUpEvent(MousePosType x, MousePosType y, MouseButton button);

		virtual bool KeyDownEvent(Key key);

		virtual void KeyUpEvent(Key key);

		virtual void TextInputEvent(std::string text);

		virtual inline Texture* GetSkin() const { return PictureBox::GetImage(); }

	public:

		static Control* tempControl;
};

#endif