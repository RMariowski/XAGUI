#include <XAGUI.h>

namespace XAGUI
{

Control* Control::_hoveredControl = 0;
Control* Control::_focusedControl = 0;

Control::Control() 
	: _visible(true),  _consumeMouseEvents(true), _consumeKeyboardEvents(false), _draggable(false),
	_alignment(ALIGNMENT_TOP_LEFT), _state(CONTROL_STATE_NORMAL), _childrenCount(0), _x(0), _y(0), 
	_width(0), _height(0), _dragX(0), _dragY(0), _parent(0)
{ SetColor(255, 255, 255, 255); }

Control::~Control() 
{ 
	DeleteAllChildren(); 

	if (this == Control::GetHoveredControl())
		Control::SetHoveredControl(0);

	if (this == Control::GetFocusedControl())
		Control::SetFocusedControl(0);
}

void Control::Render()
{
	if (!IsVisible()) return;

	for (uint32_t i = 0; i < GetChildrenCount(); i++)
		GetChild(i)->Render();
}

void Control::AddChild(Control* control)
{
	control->SetParent(this);
	_children.push_back(control);
	_childrenCount++;
}

void Control::MoveChildToFront(Control* control)
{
	for (uint32_t i = 0; i < GetChildrenCount(); i++)
	{
		if (GetChild(i) == control)
		{
			const size_t finalDst = GetChildrenCount() > i ? GetChildrenCount() - 1 : GetChildrenCount();
			std::vector<Control*> tmp(_children.begin() + i, _children.begin() + i + 1);
			_children.erase(_children.begin() + i, _children.begin() + i + 1);
			_children.insert(_children.begin() + finalDst, tmp.begin(), tmp.end());
			return;
		}
	}
}

void Control::MoveToFront()
{
	Control* child = this;
	Control* parent = GetParent();
	while (parent != 0)
	{
		parent->MoveChildToFront(child);
		child = parent;
		parent = parent->GetParent();
	}
}

void Control::RemoveChild(uint32_t i) 
{ 
	_children.erase(_children.begin() + i); 
	_childrenCount--;
}

void Control::RemoveChild(Control* control) 
{ 
	for (size_t i = 0; i < GetChildrenCount(); i++)
	{
		if (control == _children[i])
		{
			_children.erase(_children.begin() + i); 
			_childrenCount--;
			break;
		}
	}
}

void Control::RemoveAllChildren() 
{ 
	_children.clear(); 
	_childrenCount = 0;
}

void Control::DeleteChild(uint32_t i)
{
	SAFE_DELETE(_children[i]);
	RemoveChild(i);
}

void Control::DeleteChild(Control* control) 
{ 
	Control* temp = 0;
	for (size_t i = 0; i < GetChildrenCount(); i++)
	{
		temp = _children[i];
		if (control == temp)
		{
			_children.erase(_children.begin() + i); 
			SAFE_DELETE(temp);
			_childrenCount--;
			break;
		}
	}
}

void Control::DeleteAllChildren()
{
	for (size_t i = 0; i < GetChildrenCount(); i++)
	{
		SAFE_DELETE(_children[i]);
	}
	RemoveAllChildren();
}

PosType Control::GetAlignmentX() const
{
	if (GetAlignment() & ALIGNMENT_HCENTER)
	{
		if (GetParent() != 0) 
			return static_cast<PosType>((GetParent()->Control::GetWidth() - Control::GetWidth()) / 2.0f);
		return static_cast<PosType>((XAGUI::GetRenderer()->GetCanvasWidth() - Control::GetWidth()) / 2.0f);
	}
	else if (GetAlignment() & ALIGNMENT_RIGHT) 
	{
		if (GetParent() != 0) 
			return static_cast<PosType>(GetParent()->Control::GetWidth() - Control::GetWidth());
		return static_cast<PosType>(XAGUI::GetRenderer()->GetCanvasWidth() - Control::GetWidth());
	}

	// ALIGNMENT_LEFT
	return 0;
}

PosType Control::GetAlignmentY() const
{
	if (GetAlignment() & ALIGNMENT_VCENTER)
	{
		if (GetParent() != 0) 
			return static_cast<PosType>((GetParent()->Control::GetHeight() - Control::GetHeight()) / 2.0f);
		return static_cast<PosType>((XAGUI::GetRenderer()->GetCanvasHeight() - Control::GetHeight()) / 
			2.0f);
	}
	else if (GetAlignment() & ALIGNMENT_BOTTOM) 
	{
		if (GetParent() != 0) 
			return static_cast<PosType>(GetParent()->Control::GetHeight() - Control::GetHeight());
		return static_cast<PosType>(XAGUI::GetRenderer()->GetCanvasHeight() - Control::GetHeight());
	}

	// ALIGNMENT_TOP
	return 0;
}

PosType Control::GetAbsX() const
{
	if (GetParent() == 0) return GetAlignmentX() + GetX();
	return GetParent()->GetAbsX() + GetAlignmentX() + GetX();
}

PosType Control::GetAbsY() const
{
	if (GetParent() == 0)  return GetAlignmentY() + GetY();
	return GetParent()->GetAbsY() + GetAlignmentY() + GetY();
}

Control* Control::GetChild(cchar* id) const
{
	for (uint32_t i = 0; i < GetChildrenCount(); i++)
	{
		if (strcmp(GetChild(i)->GetID(), id) == 0) return GetChild(i);
		Form::tempControl = GetChild(i)->GetChild(id);
		if (Form::tempControl != 0) return Form::tempControl;
	}
	return 0;
}

Control* Control::GetControlAt(MousePosType x, MousePosType y)
{
	if (!IsVisible() || IsDisabled()) return 0;

	if (GetChildrenCount() > 0)
	{
		Control* control = 0;
		for (uint32_t i = GetChildrenCount(); i > 0; i--)
		{
			control = GetChild(i - 1);
			Form::tempControl = control->GetControlAt(static_cast<MousePosType>(x - control->GetX() - 
				control->GetAlignmentX()), static_cast<MousePosType>(y - control->GetY() - 
				control->GetAlignmentY()));

			if (Form::tempControl != 0 && Form::tempControl->IsConsumeMouseEvents()) 
				return Form::tempControl;
		}
	}

	if (x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight()) return 0;
	return this;
}

void Control::SetPosition(PosType x, PosType y)
{
	SetX(x);
	SetY(y);
}

void Control::SetX(PosType x) 
{ 
	if (GetX() == x) return;
	_x = x; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetY(PosType y) 
{ 
	if (GetY() == y) return;
	_y = y; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetSize(SizeType width, SizeType height)
{
	SetWidth(width);
	SetHeight(height);
}

void Control::SetWidth(SizeType width) 
{ 
	if (GetWidth() == width) return;
	_width = width; 
	XAGUI::SetRequestRedraw(true);
}
		
void Control::SetHeight(SizeType height) 
{ 
	if (GetHeight() == height) return;
	_height = height; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetAlignment(Alignment alignment) 
{ 
	if (GetAlignment() == alignment) return;
	_alignment = alignment; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetState(ControlState state)
{
	if (GetState() == state) return;
	
	_state = state;
	if (onControlStateChanged != 0)
	{
		onControlStateChanged(this);
	}
	else OnControlStateChanged();

	XAGUI::SetRequestRedraw(true);
}

void Control::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	for (uint8_t i = 0; i < CONTROL_STATE_COUNT; i++)
		SetColor(i, red, green, blue, alpha);
}

void Control::SetColor(ControlState controlState, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	// Q: This function should be conditioned as rest?
	_colorRed[controlState] = red;
	_colorGreen[controlState] = green;
	_colorBlue[controlState] = blue;
	_colorAlpha[controlState] = alpha;
	XAGUI::SetRequestRedraw(true);
}

void Control::SetVisible(bool visible) 
{ 
	if (IsVisible() == visible) return;
	
	_visible = visible; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetParent(Control* parent) 
{ 
	if (GetParent() == parent) return;
	
	_parent = parent; 
	XAGUI::SetRequestRedraw(true);
}

void Control::SetFocusedControl(Control* control)
{
	if (control == GetFocusedControl()) return;
	
	if (GetFocusedControl() != 0)
	{
		if (GetFocusedControl()->onFocus != 0)
		{
			GetFocusedControl()->onFocus(GetFocusedControl(), false);
		}
		else
		{
			GetFocusedControl()->OnLostFocus();
		}
	}

	_focusedControl = control;
	if (control != 0)
		(control->onFocus != 0) ? control->onFocus(control, true) : control->OnGotFocus();

	XAGUI::SetRequestRedraw(true);
}

void Control::OnControlStateChanged() { }

void Control::OnMouseMove(MousePosType x, MousePosType y) 
{ 
	if (!IsDraggable() || !IsActive()) return;
	
	SetX(static_cast<PosType>(x - GetDragX()));
	SetY(static_cast<PosType>(y - GetDragY()));
}

void Control::OnMouseEnter() { }

void Control::OnMouseLeave() { }

void Control::OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button) 
{ 
	if (!IsDraggable() || button != MOUSE_BUTTON_LEFT) return;
	
	SetDragX(static_cast<MousePosType>(x - GetAbsX() + GetAlignmentX()));
	SetDragY(static_cast<MousePosType>(y - GetAbsY() + GetAlignmentY()));	
}

void Control::OnMouseButtonUp(MousePosType x, MousePosType y, MouseButton button) { }

void Control::OnKeyDown(Key key) { }

void Control::OnKeyUp(Key key) { }

void Control::OnTextInput(std::string text) { }

void Control::OnGotFocus() { }

void Control::OnLostFocus() { }

void Control::OnClick() { }

};