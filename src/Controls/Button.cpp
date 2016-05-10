#include <XAGUI.h>

namespace XAGUI
{

Button::Button()
	: _srcWidth(0), _srcHeight(0), _flip(FLIP_NONE)
{
	SetSrcX(0);
	SetSrcY(0);
}

void Button::Render()
{
	if (!IsVisible()) return;

	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
		GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
		GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
		GetColorAlpha(GetState()), GetFlip());
	Control::Render();
}

void Button::SetSrc(SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, SrcSizeType srcHeight)
{
	SetSrcX(srcX);
	SetSrcY(srcY);
	SetSrcWidth(srcWidth);
	SetSrcHeight(srcHeight);
}

void Button::SetSrc(ControlState controlState, SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, 
					SrcSizeType srcHeight)
{
	SetSrcX(controlState, srcX);
	SetSrcY(controlState, srcY);
	SetSrcWidth(srcWidth);
	SetSrcHeight(srcHeight);
}

void Button::SetSrcX(SrcPosType srcX) 
{ 
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetSrcX(i, srcX);
}

void Button::SetSrcY(SrcPosType srcY) 
{ 
	for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		SetSrcY(i, srcY);
}

void Button::SetSrcX(ControlState controlState, SrcPosType srcX) 
{ 
	if (GetSrcX(controlState) == srcX) return;
	
	_srcX[controlState] = srcX; 
	XAGUI::SetRequestRedraw(true);
}
		
void Button::SetSrcY(ControlState controlState, SrcPosType srcY) 
{ 
	if (GetSrcY(controlState) == srcY) return;

	_srcY[controlState] = srcY; 
	XAGUI::SetRequestRedraw(true);
}
		
void Button::SetSrcWidth(SrcSizeType srcWidth) 
{ 
	if (GetSrcWidth() == srcWidth) return;
	
	_srcWidth = srcWidth; 

	if (Control::GetWidth() == 0) 
		SetWidth(srcWidth);

	XAGUI::SetRequestRedraw(true);
}

void Button::SetSrcHeight(SrcSizeType srcHeight) 
{ 
	if (GetSrcHeight() == srcHeight) return;

	_srcHeight = srcHeight; 

	if (Control::GetHeight() == 0) 
		SetHeight(srcHeight);

	XAGUI::SetRequestRedraw(true);
}

void Button::SetFlip(Flip flip)
{
	if (GetFlip() == flip) return;

	_flip = flip; 
	XAGUI::SetRequestRedraw(true);
}

};