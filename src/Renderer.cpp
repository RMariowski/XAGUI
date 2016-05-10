#include <XAGUI.h>

namespace XAGUI
{

Renderer::Renderer(SizeType screenWidth, SizeType screenHeight, SizeType canvasWidth, 
				   SizeType canvasHeight) 
	: _screenWidth(screenWidth), _screenHeight(screenHeight), _canvasWidth(canvasWidth), 
	_canvasHeight(canvasHeight), _widthRatio(0.0f), _heightRatio(0.0f)
{ UpdateRatio(); }

void Renderer::SetScreenSize(SizeType width, SizeType height) 
{ 
	_screenWidth = width; 
	_screenHeight = height; 
	UpdateRatio();
	XAGUI::SetRequestRedraw(true);
}

void Renderer::SetCanvasSize(SizeType width, SizeType height) 
{ 
	_canvasWidth = width; 
	_canvasHeight = height;
	UpdateRatio();
	XAGUI::SetRequestRedraw(true);
}

void Renderer::UpdateRatio() 
{ 
	_widthRatio = (GetScreenWidth() / static_cast<float>(GetCanvasWidth())); 
	_heightRatio = (GetScreenHeight() / static_cast<float>(GetCanvasHeight())); 
}

};
