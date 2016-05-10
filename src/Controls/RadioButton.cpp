#include <XAGUI.h>

namespace XAGUI
{

RadioButton::RadioButton() { }

void RadioButton::OnClick()
{
	if (!IsChecked()) 
		SetChecked(true); 
}

};