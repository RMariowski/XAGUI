#ifndef XAGUI_TAB_PAGE_H
#define XAGUI_TAB_PAGE_H

XAGUI_EXPORT class TabPage : public Control
{
	public:

		TabPage();

		virtual void AddControl(Control* control);

		virtual inline size_t GetControlsCount() const { return GetChildrenCount(); }

		virtual inline Control* GetControl(size_t i) const { return GetChild(i); }
};

#endif