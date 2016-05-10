#ifndef XAGUI_SCROLLABLE_CONTROL_H
#define XAGUI_SCROLLABLE_CONTROL_H

XAGUI_EXPORT class ScrollableControl : public Button
{
	public:

		ScrollableControl();

		void ShowVerticalScrollBar();
		
		void HideVerticalScrollBar();

		void HideHorizontalScrollBar();

		void ShowHorizontalScrollBar();

		virtual inline ScrollBar* GetVerticalScrollBar() const { return _vScrollBar; }

		virtual inline ScrollBar* GetHorizontalScrollBar() const { return _hScrollBar; }

		virtual void SetWidth(SizeType width);
		
		virtual void SetHeight(SizeType height);

		virtual inline void SetVerticalScrollBar(ScrollBar* scrollBar) { _vScrollBar = scrollBar; }

		virtual inline void SetHorizontalScrollBar(ScrollBar* scrollBar) { _hScrollBar = scrollBar; }

	public:

		virtual void OnVerticalValueChanged(Control* control);

		virtual void OnHorizontalValueChanged(Control* control);

	protected:

		ScrollBar* _vScrollBar;
		ScrollBar* _hScrollBar;
};

#endif