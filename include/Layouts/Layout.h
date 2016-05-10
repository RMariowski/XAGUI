#ifndef XAGUI_LAYOUT_H
#define XAGUI_LAYOUT_H

class Control;

XAGUI_EXPORT class Layout
{
	public:

		Layout();

		virtual void AddControl(Control* control);

		virtual void RemoveControl(size_t i);

		virtual void RemoveControl(Control* control);

		virtual void Update() = 0;

		virtual inline size_t GetControlsCount() const { return _controls.size(); }

		virtual inline Control* GetControl(size_t i) const { return _controls[i]; }

	protected:

		std::vector<Control*> _controls;
};

#endif