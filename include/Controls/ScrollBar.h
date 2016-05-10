#ifndef XAGUI_SCROLL_BAR_H
#define XAGUI_SCROLL_BAR_H

XAGUI_EXPORT class ScrollBar : public Slider
{
	public:

		ScrollBar();

		virtual void Render();

		virtual SizeType GetWidth() const;

		virtual SizeType GetHeight() const;

		virtual inline Button* GetFirstButton() const { return _first; }

		virtual inline Button* GetSecondButton() const { return _second; }
		
		virtual void SetWidth(SizeType width);
		
		virtual void SetHeight(SizeType height);
		
		virtual void SetOrientation(Orientation orientation);

		virtual void SetFirstButton(Button* button) { _first = button; }

		virtual void SetSecondButton(Button* button) { _second = button; }

		virtual void SetValue(int32_t value);

	public:

		virtual void OnMouseButton(Control* control, MousePosType x, MousePosType y, MouseButton button, 
			bool down);

	protected:

		virtual void UpdateButtons();

	protected:

		Button* _first;
		Button* _second;
};

#endif