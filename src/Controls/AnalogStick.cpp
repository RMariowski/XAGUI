#include <XAGUI.h>

namespace XAGUI
{

AnalogStick::AnalogStick()
	: _stickX(0), _stickY(0), _valueX(0), _valueY(0)
{
	SetStickSrcX(0);
	SetStickSrcY(0);
}

void AnalogStick::Render()
{
	if (!IsVisible()) return;

	Button::Render();
	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetStickX(), GetStickY(), GetWidth(), GetHeight(), 
		GetStickSrcX(GetState()), GetStickSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
		GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()),
		GetColorAlpha(GetState()), GetFlip());
}

void AnalogStick::ResetStick()
{
	SetStickX(GetAbsX());
	SetStickY(GetAbsY());
}

void AnalogStick::SetX(PosType x)
{
	Control::SetX(x);
	ResetStick();
}

void AnalogStick::SetY(PosType y)
{
	Control::SetY(y);
	ResetStick();
}

void AnalogStick::SetWidth(SizeType width)
{
	Control::SetWidth(width);
	ResetStick();
}

void AnalogStick::SetHeight(SizeType height)
{
	Control::SetHeight(height);
	ResetStick();
}

void AnalogStick::SetStickX(PosType stickX)
{
	if (GetStickX() == stickX) return;
	
	PosType absX = GetAbsX();
	float quarterWidth = GetWidth() / 4.0f;
	if (stickX < absX - quarterWidth)
	{
		_stickX = absX - static_cast<PosType>(quarterWidth);
		SetValueX(-1.0f);
	}
	else if (stickX > absX + quarterWidth)
	{
		_stickX = absX + static_cast<PosType>(quarterWidth);
		SetValueX(1.0f);
	}
	else
	{
		_stickX = stickX;
		SetValueX((GetStickX() - absX) / quarterWidth);
	}
}

void AnalogStick::SetStickY(PosType stickY)
{
	if (GetStickY() == stickY) return;

	PosType absY = GetAbsY();
	float quarterHeight = GetHeight() / 4.0f;
	if (stickY < absY - quarterHeight)
	{
		_stickY = absY - static_cast<PosType>(quarterHeight);
		SetValueY(1.0f);
	}
	else if (stickY > absY + quarterHeight)
	{
		_stickY = absY + static_cast<PosType>(quarterHeight);
		SetValueY(-1.0f);
	}
	else
	{
		_stickY = stickY;
		SetValueY(-(GetStickY() - absY) / quarterHeight);
	}
}

void AnalogStick::SetValueX(float valueX)
{
	_valueX = valueX;
	if (onValueChanged != 0) 
	{
		onValueChanged(this);
	}
	else OnValueChangedEvent();

	XAGUI::SetRequestRedraw(true);
}

void AnalogStick::SetValueY(float valueY)
{
	_valueY = valueY;
	if (onValueChanged != 0) 
	{
		onValueChanged(this); 
	}
	else OnValueChangedEvent();
	
	XAGUI::SetRequestRedraw(true);
}

void AnalogStick::SetStickSrc(SrcPosType stickSrcX, SrcPosType stickSrcY)
{
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
	{
		SetStickSrcX(i, stickSrcX);
		SetStickSrcY(i, stickSrcY);
	}
}

void AnalogStick::SetStickSrcX(SrcPosType stickSrcX)
{
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetStickSrcX(i, stickSrcX);
}
		
void AnalogStick::SetStickSrcY(SrcPosType stickSrcY)
{
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetStickSrcY(i, stickSrcY);
}

void AnalogStick::SetStickSrc(ControlState controlState, SrcPosType stickSrcX, SrcPosType stickSrcY) 
{ 
	SetStickSrcX(controlState, stickSrcX); 
	SetStickSrcY(controlState, stickSrcY); 
}

void AnalogStick::SetStickSrcX(ControlState controlState, SrcPosType stickSrcX) 
{ 
	if (GetStickSrcX(controlState) == stickSrcX) return;
	
	_stickSrcX[controlState] = stickSrcX; 
	XAGUI::SetRequestRedraw(true);
}
		
void AnalogStick::SetStickSrcY(ControlState controlState, SrcPosType stickSrcY) 
{ 
	if (GetStickSrcY(controlState) == stickSrcY) return;
	
	_stickSrcY[controlState] = stickSrcY; 
	XAGUI::SetRequestRedraw(true);
}

void AnalogStick::OnMouseMove(MousePosType x, MousePosType y)
{
	Control::OnMouseMove(x, y);
	if (!IsActive()) return;
	
	SetStickX(static_cast<PosType>(x - GetWidth() / 2.0f));
	SetStickY(static_cast<PosType>(y - GetHeight() / 2.0f));
}

void AnalogStick::OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button)
{
	Control::OnMouseButtonDown(x, y, button);

	if (button != MOUSE_BUTTON_LEFT) return;

	SetStickX(static_cast<PosType>(x - GetWidth() / 2.0f));
	SetStickY(static_cast<PosType>(y - GetHeight() / 2.0f));
}

void AnalogStick::OnMouseButtonUp(MousePosType x, MousePosType y, MouseButton button)
{
	Control::OnMouseButtonUp(x, y, button);
	if (button == MOUSE_BUTTON_LEFT)
		ResetStick();
}

void AnalogStick::OnValueChanged() { }

};