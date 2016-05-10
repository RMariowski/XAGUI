#include <XAGUI.h>

namespace XAGUI
{

ScrollableControl::ScrollableControl() 
{ 
	_vScrollBar = new ScrollBar();
	GetVerticalScrollBar()->SetAlignment(ALIGNMENT_VCENTER_RIGHT);
	GetVerticalScrollBar()->SetOrientation(ORIENTATION_VERTICAL);
	GetVerticalScrollBar()->onValueChanged.bind(this, &ScrollableControl::OnVerticalValueChanged);
	GetVerticalScrollBar()->Hide();
	AddChild(GetVerticalScrollBar());

	_hScrollBar = new ScrollBar();
	GetHorizontalScrollBar()->SetAlignment(ALIGNMENT_BOTTOM_HCENTER);
	GetHorizontalScrollBar()->SetOrientation(ORIENTATION_HORIZONTAL);
	GetHorizontalScrollBar()->onValueChanged.bind(this, &ScrollableControl::OnHorizontalValueChanged);
	GetHorizontalScrollBar()->Hide();
	AddChild(GetHorizontalScrollBar());
}

void ScrollableControl::ShowVerticalScrollBar() { _vScrollBar->Show(); }

void ScrollableControl::HideVerticalScrollBar() { _vScrollBar->Hide(); }

void ScrollableControl::ShowHorizontalScrollBar() { _hScrollBar->Show(); }

void ScrollableControl::HideHorizontalScrollBar() { _hScrollBar->Hide(); }

void ScrollableControl::SetWidth(SizeType width) 
{ 
	if (GetWidth() == width) return;
	Button::SetWidth(width);
	GetHorizontalScrollBar()->SetWidth(width);
}
		
void ScrollableControl::SetHeight(SizeType height) 
{ 
	if (GetHeight() == height) return;
	Button::SetHeight(height);
	GetVerticalScrollBar()->SetHeight(height);
}

void ScrollableControl::OnVerticalValueChanged(Control* control) { }

void ScrollableControl::OnHorizontalValueChanged(Control* control) { }

}