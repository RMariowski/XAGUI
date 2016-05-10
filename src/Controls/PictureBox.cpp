#include <XAGUI.h>

namespace XAGUI
{

PictureBox::PictureBox()
	: _image(0)
{ }

void PictureBox::Render()
{
	if (!IsVisible() || GetImage() == 0) return;
	
	XAGUI::GetRenderer()->Render(GetImage(), GetAbsX(), GetAbsY(), GetWidth(), GetHeight(), 
		GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
		GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
		GetColorAlpha(GetState()), GetFlip());
	Control::Render();
}

void PictureBox::DeleteTexture() 
{ 
	SAFE_DELETE(_image); 
}

void PictureBox::SetImage(Texture* image) 
{ 
	_image = image; 
	XAGUI::SetRequestRedraw(true); 
}

};