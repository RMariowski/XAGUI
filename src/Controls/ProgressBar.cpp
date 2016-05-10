#include <XAGUI.h>

namespace XAGUI
{

ProgressBar::ProgressBar()
	: _progress(0)
{ }

void ProgressBar::Render()
{
	if (!IsVisible()) return;
		
	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), 
		static_cast<SizeType>(GetWidth() * GetProgress() / 100.0f), GetHeight(), GetSrcX(GetState()), 
		GetSrcY(GetState()), static_cast<SrcSizeType>(GetSrcWidth() * GetProgress() / 100.0f), 
		GetSrcHeight(), GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()),
		GetColorAlpha(GetState()), GetFlip());
	Control::Render();
}

void ProgressBar::SetProgress(int8_t progress)
{
	if (progress < 0 || progress > 100) return;

	_progress = progress; 
	if (onValueChanged != 0) 
	{
		onValueChanged(this);
	}
	else OnValueChangedEvent();

	XAGUI::SetRequestRedraw(true);
}

void ProgressBar::OnValueChanged() { }

};