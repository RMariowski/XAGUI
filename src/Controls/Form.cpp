#include <XAGUI.h>

namespace XAGUI
{

Control* Form::tempControl = 0;

Form::Form() { }

Form::~Form() { PictureBox::DeleteTexture(); }

void Form::Render()
{
	XAGUI::SetSkin(GetSkin());
	if (XAGUI::IsRedrawNeeded())
	{
		XAGUI::GetRenderer()->SetCanvasAsRenderTarget();
		XAGUI::GetRenderer()->ClearCanvas();
		PictureBox::Render();
		XAGUI::GetRenderer()->SetDefaultRenderTarget();
		XAGUI::SetRequestRedraw(false);
	}
	XAGUI::GetRenderer()->RenderCanvas();
}

void Form::MouseMoveEvent(MousePosType x, MousePosType y)
{
	x = static_cast<MousePosType>(x / XAGUI::GetRenderer()->GetWidthRatio());
	y = static_cast<MousePosType>(y / XAGUI::GetRenderer()->GetHeightRatio());

	// If there's not hovered control or hovered control is not active and not disabled
	if (Control::GetHoveredControl() == 0 || (!Control::GetHoveredControl()->IsActive() &&
		!Control::GetHoveredControl()->IsDisabled()))
	{
		Form::tempControl = GetControlAt(x, y);
		if (Form::tempControl != 0 && !Form::tempControl->IsDisabled())
		{
			if (Control::GetHoveredControl() == 0)
			{
				Control::SetHoveredControl(Form::tempControl);
				Control::GetHoveredControl()->Hover();
			}
			else if (Control::GetHoveredControl() != Form::tempControl)
			{
				Control::GetHoveredControl()->Normal();
				Control::SetHoveredControl(Form::tempControl);
				Control::GetHoveredControl()->Hover();
			}
		}
	}

	if (Control::GetHoveredControl() != 0)
	{
		if (Control::GetHoveredControl()->onMouseMove != 0)
		{
			Control::GetHoveredControl()->onMouseMove(Control::GetHoveredControl(), x, y);
		}
		else Control::GetHoveredControl()->OnMouseMove(x, y);
	}
}

bool Form::MouseButtonDownEvent(MousePosType x, MousePosType y, MouseButton button)
{
	x = static_cast<MousePosType>(x / XAGUI::GetRenderer()->GetWidthRatio());
	y = static_cast<MousePosType>(y / XAGUI::GetRenderer()->GetHeightRatio());
	if (Control::GetHoveredControl() != 0)
	{
		bool consumeEvent = false;
		if (button == MOUSE_BUTTON_LEFT && !Control::GetHoveredControl()->IsDisabled())
		{
			Control::GetHoveredControl()->MoveToFront();
			Control::GetHoveredControl()->Active();
			Control::SetFocusedControl(Control::GetHoveredControl());
			consumeEvent = true;
		}

		if (Control::GetHoveredControl()->onMouseButton != 0) 
		{
			Control::GetHoveredControl()->onMouseButton(Control::GetHoveredControl(), x, y, button, true);
		}
		else Control::GetHoveredControl()->OnMouseButtonDown(x, y, button);

		return Control::GetHoveredControl()->IsConsumeMouseEvents() ? consumeEvent : false;
	}
	return false;
}
		
void Form::MouseButtonUpEvent(MousePosType x, MousePosType y, MouseButton button)
{
	x = static_cast<MousePosType>(x / XAGUI::GetRenderer()->GetWidthRatio());
	y = static_cast<MousePosType>(y / XAGUI::GetRenderer()->GetHeightRatio());

	if (Control::GetFocusedControl() == 0) return;

	if (button == MOUSE_BUTTON_LEFT)
	{
		Form::tempControl = GetControlAt(x, y);
		if (Form::tempControl == Control::GetFocusedControl())
		{
			if (Control::GetFocusedControl()->onClick != 0)
			{
				Control::GetFocusedControl()->onClick(Form::tempControl);
			}
			else Control::GetFocusedControl()->OnClick();
 
			if (Control::GetFocusedControl()->IsDisabled())
			{
				Control::SetHoveredControl(0);
				Control::SetFocusedControl(0);
			}
			else Control::GetFocusedControl()->Hover();
		}
		else
		{
			Control::SetHoveredControl(Form::tempControl);
			if (!Control::GetFocusedControl()->IsDisabled())
				Control::GetFocusedControl()->Normal();
			Control::GetHoveredControl()->Hover();
		}
	}

	if (Control::GetFocusedControl() != 0)
	{
		if (Control::GetFocusedControl()->onMouseButton != 0) 
		{
			Control::GetFocusedControl()->onMouseButton(Control::GetHoveredControl(), x, y, button, 
				false);
		}
		else Control::GetFocusedControl()->OnMouseButtonUp(x, y, button);
	}
}

bool Form::KeyDownEvent(Key key)
{
	if (GetFocusedControl() == 0 || GetFocusedControl() == this) return false;
	
	if (GetFocusedControl()->onKey != 0)
	{
		GetFocusedControl()->onKey(GetFocusedControl(), key, true);
	}
	else GetFocusedControl()->OnKeyDown(key);
	
	return Control::GetFocusedControl()->IsConsumeKeyboardEvents() ? true : false;
}

void Form::KeyUpEvent(Key key)
{
	if (GetFocusedControl() == 0 || GetFocusedControl() == this) return;
	
	if (GetFocusedControl()->onKey != 0)
	{
		GetFocusedControl()->onKey(GetFocusedControl(), key, false);
	}
	else GetFocusedControl()->OnKeyUp(key);
}

void Form::TextInputEvent(std::string text)
{
	if (GetFocusedControl() != 0 && GetFocusedControl() != this)
		GetFocusedControl()->OnTextInput(text);
}

};