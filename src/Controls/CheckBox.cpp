#include <XAGUI.h>

namespace XAGUI
{

CheckBox::CheckBox()
	: _checked(false)
{ SetCheckedSrc(0, 0); }

void CheckBox::Render()
{
	if (!IsVisible()) return;
	
	if (IsChecked())
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(),
			GetCheckedSrcX(GetState()), GetCheckedSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
			GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
			GetColorAlpha(GetState()), GetFlip());
	}
	else
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(),
			GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
			GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
			GetColorAlpha(GetState()), GetFlip());
	}

	Control::Render();
}

void CheckBox::SetCheckedSrc(SrcPosType srcX, SrcPosType srcY)
{
	SetCheckedSrcX(srcX);
	SetCheckedSrcY(srcY);
}

void CheckBox::SetCheckedSrc(ControlState controlState, SrcPosType srcX, SrcPosType srcY)
{
	SetCheckedSrcX(controlState, srcX);
	SetCheckedSrcY(controlState, srcY);
}

void CheckBox::SetCheckedSrcX(SrcPosType srcX)
{ 
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetCheckedSrcX(i, srcX);
}

void CheckBox::SetCheckedSrcY(SrcPosType srcY)
{ 
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetCheckedSrcY(i, srcY);
}

void CheckBox::SetCheckedSrcX(ControlState controlState, SrcPosType srcX)
{ 
	if (GetCheckedSrcX(controlState) == srcX) return;
	
	_checkedSrcX[controlState] = srcX; 
	XAGUI::SetRequestRedraw(true);
}

void CheckBox::SetCheckedSrcY(ControlState controlState, SrcPosType srcY)
{ 
	if (GetCheckedSrcY(controlState) == srcY) return;
	
	_checkedSrcY[controlState] = srcY; 
	XAGUI::SetRequestRedraw(true);
}

void CheckBox::OnClick() 
{ 
	(IsChecked()) ? SetChecked(false) : SetChecked(true);
	XAGUI::SetRequestRedraw(true);
}

};