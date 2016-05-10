#include <XAGUI.h>

namespace XAGUI
{

Slider::Slider()
	: _orientation(ORIENTATION_VERTICAL), _markerOffsetX(0), _markerOffsetY(0)
{ 
	_marker = new Button(); 
	SetValue(0);
	SetMinValue(0);
	SetMaxValue(1);
	GetMarker()->onMouseMove.bind(this, &Slider::MarkerOnMouseMove);
	GetMarker()->onMouseButton.bind(this, &Slider::MarkerOnMouseButton);
	AddChild(GetMarker());
}

void Slider::SetMarkerOffsetX(PosType markerOffsetX)
{
	if (GetMarkerOffsetX() == markerOffsetX) return;
	
	_markerOffsetX = markerOffsetX;
	SetValue(GetValue());
}

void Slider::SetMarkerOffsetY(PosType markerOffsetY)
{
	if (GetMarkerOffsetY() == markerOffsetY) return;

	_markerOffsetY = markerOffsetY;
	SetValue(GetValue());
}

void Slider::SetMinValue(int32_t minValue) 
{ 
	if (GetMinValue() == minValue) return;

	_minValue = minValue; 
	SetValue(GetValue());
}

void Slider::SetMaxValue(int32_t maxValue) 
{ 
	if (GetMaxValue() == maxValue) return;

	_maxValue = maxValue; 
	SetValue(GetValue());
}

void Slider::SetValue(int32_t value) 
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
		GetMarker()->SetX(static_cast<PosType>(GetMarkerOffsetX() + (GetWidth() - GetMarker()->GetWidth())
			/ ((GetMaxValue() - GetMinValue()) / static_cast<float>(GetValue()))));
		GetMarker()->SetY(GetMarkerOffsetY());
	}
	else
	{
		GetMarker()->SetX(GetMarkerOffsetX());
		GetMarker()->SetY(static_cast<PosType>(GetMarkerOffsetY() + (GetHeight() - 
			GetMarker()->GetHeight()) / ((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetValue()))));
	}
}

void Slider::OnMouseMove(MousePosType x, MousePosType y)
{
	if (!IsActive()) return;

	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetWidth() / static_cast<float>(x - GetAbsX()))));
	}
	else
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / static_cast<float>(GetHeight() / 
			static_cast<float>(y - GetAbsY()))));
	}
}

void Slider::OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button)
{
	if (button != MOUSE_BUTTON_LEFT) return;
	
	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetWidth() / static_cast<float>(x - GetAbsX()))));
	}
	else
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetHeight() / static_cast<float>(y - GetAbsY()))));
	}
}

void Slider::OnValueChanged() { }

void Slider::MarkerOnMouseMove(Control* control, MousePosType x, MousePosType y)
{
	if (!GetMarker()->IsActive()) return;

	if (GetOrientation() == ORIENTATION_HORIZONTAL) 
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetWidth() / static_cast<float>(x - GetAbsX()))));
	}
	else
	{
		SetValue(static_cast<int32_t>((GetMaxValue() - GetMinValue()) / 
			static_cast<float>(GetHeight() / static_cast<float>(y - GetAbsY()))));
	}
}

void Slider::MarkerOnMouseButton(Control* control, MousePosType x, MousePosType y, MouseButton button, 
								 bool down)
{
	if (down)
		OnMouseButtonDown(x, y, button);
}

};