#include <XAGUI.h>

namespace XAGUI
{

ScrollBar::ScrollBar() 
{ 
	_first = new Button(); 
	GetFirstButton()->onMouseButton.bind(this, &ScrollBar::OnMouseButton);
	AddChild(GetFirstButton());

	_second = new Button();
	GetSecondButton()->onMouseButton.bind(this, &ScrollBar::OnMouseButton);
	AddChild(GetSecondButton());
}

void ScrollBar::Render()
{
	if (!IsVisible()) return;

	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), Slider::GetWidth(), 
		Slider::GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
		GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
		GetColorAlpha(GetState()), GetFlip());
	Control::Render();
}

SizeType ScrollBar::GetWidth() const
{
	SizeType width = Slider::GetWidth();
	
	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		width += GetFirstButton()->GetWidth();
		width += GetSecondButton()->GetWidth();
	}

	return width;
}

SizeType ScrollBar::GetHeight() const
{
	SizeType height = Slider::GetHeight();

	if (GetOrientation() == ORIENTATION_VERTICAL) 
	{
		height += GetFirstButton()->GetHeight();
		height += GetSecondButton()->GetHeight();
	}

	return height;
}

void ScrollBar::SetWidth(SizeType width) 
{ 
	if (GetWidth() == width) return;

	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		width -= GetFirstButton()->GetWidth();
		width -= GetSecondButton()->GetWidth();
	}

	Slider::SetWidth(width);

	UpdateButtons();
}
		
void ScrollBar::SetHeight(SizeType height) 
{ 
	if (GetHeight() == height) return;
	
	if (GetOrientation() == ORIENTATION_VERTICAL) 
	{
		height -= GetFirstButton()->GetHeight();
		height -= GetSecondButton()->GetHeight();
	}

	Slider::SetHeight(height);

	UpdateButtons();
}

void ScrollBar::SetOrientation(Orientation orientation)
{
	Slider::SetOrientation(orientation);
	UpdateButtons();
}

void ScrollBar::SetValue(int32_t value) 
{ 
	if (value < GetMinValue())
	{
		value = GetMinValue();
	}
	else if (value > GetMaxValue())
	{
		value = GetMaxValue();
	}

	_value = value;

	(onValueChanged != 0) ? onValueChanged(this) : OnValueChanged();
	
	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		GetMarker()->SetX(static_cast<PosType>(GetMarkerOffsetX() + (Slider::GetWidth() - 
			GetMarker()->GetWidth()) / ((GetMaxValue() - GetMinValue()) / static_cast<float>(GetValue()))));
		GetMarker()->SetY(GetMarkerOffsetY());
	}
	else
	{
		GetMarker()->SetX(GetMarkerOffsetX());
		GetMarker()->SetY(static_cast<PosType>(GetMarkerOffsetY() + (Slider::GetHeight() - 
			GetMarker()->GetHeight()) / ((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetValue()))));
	}
}

void ScrollBar::OnMouseButton(Control* control, MousePosType x, MousePosType y, MouseButton button, 
							  bool down)
{
	if (!down) return;
	
	if (control == GetFirstButton())
	{
		SetValue(GetValue() - 1);
	}
	else if (control == GetSecondButton())
	{
		SetValue(GetValue() + 1);
	}
}

void ScrollBar::UpdateButtons()
{
	GetFirstButton()->SetAlignment(ALIGNMENT_TOP_LEFT);

	if (GetOrientation() == ORIENTATION_VERTICAL) 
	{
		GetSecondButton()->SetAlignment(ALIGNMENT_BOTTOM_LEFT);

		GetFirstButton()->SetY(-GetFirstButton()->GetHeight());
		GetSecondButton()->SetY(GetSecondButton()->GetHeight());
		
	}
	else
	{
		GetSecondButton()->SetAlignment(ALIGNMENT_TOP_RIGHT);

		GetFirstButton()->SetX(-GetFirstButton()->GetWidth());
		GetSecondButton()->SetX(GetSecondButton()->GetWidth());
	}
}

};