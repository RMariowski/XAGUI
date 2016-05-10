#ifndef XAGUI_CONTROL_H
#define XAGUI_CONTROL_H

class Control;

typedef fastdelegate::FastDelegate1<Control*, void> ControlEvent;
typedef ControlEvent OnStateChangedEvent;
typedef fastdelegate::FastDelegate3<Control*, MousePosType, MousePosType, void> OnMouseMoveEvent;
typedef ControlEvent OnMouseEnterEvent;
typedef ControlEvent OnMouseLeaveEvent;
typedef fastdelegate::FastDelegate5<Control*, MousePosType, MousePosType, MouseButton, bool, void> 
	OnMouseButtonEvent;
typedef fastdelegate::FastDelegate3<Control*, Key, bool, void> OnKeyEvent;
typedef fastdelegate::FastDelegate2<Control*, std::string, void> OnTextInputEvent;
typedef fastdelegate::FastDelegate2<Control*, bool, void> OnFocusEvent;
typedef ControlEvent OnClickEvent;
typedef ControlEvent OnValueChangedEvent;

XAGUI_EXPORT class Control : public ControlBase
{
	public:

		Control();

		virtual ~Control();

		virtual void Render();

		virtual inline void Show() { SetVisible(true); }

		virtual inline void Hide() { SetVisible(false); }
		
		virtual inline void Normal() { SetState(CONTROL_STATE_NORMAL); }

		virtual inline void Hover() { SetState(CONTROL_STATE_HOVER); }

		virtual inline void Active() { SetState(CONTROL_STATE_ACTIVE); }

		virtual inline void Enable() { SetState(CONTROL_STATE_NORMAL); }

		virtual inline void Disable() { SetState(CONTROL_STATE_DISABLED); }

		virtual void AddChild(Control* control);

		virtual void MoveChildToFront(Control* control);
		
		virtual void MoveToFront();

		virtual void RemoveChild(uint32_t i);

		virtual void RemoveChild(Control* control);

		virtual void RemoveAllChildren();

		virtual void DeleteChild(uint32_t i);
		
		virtual void DeleteChild(Control* control);

		virtual void DeleteAllChildren();

		virtual inline bool IsActive() const
		{ return (GetState() == CONTROL_STATE_ACTIVE) ? true : false; }

		virtual inline bool IsDisabled() const
		{ return (GetState() == CONTROL_STATE_DISABLED) ? true : false; }
		
		virtual inline bool IsVisible() const { return _visible; }
		
		virtual inline bool IsConsumeMouseEvents() const { return _consumeMouseEvents; }

		virtual inline bool IsConsumeKeyboardEvents() const { return _consumeKeyboardEvents; }
		
		virtual inline bool IsDraggable() const { return _draggable; }

		virtual inline bool IsFocused() const { return (Control::GetFocusedControl() == this); }

		virtual inline PosType GetX() const { return _x; }

		virtual inline PosType GetY() const { return _y; }
		
		virtual inline Alignment GetAlignment() const { return _alignment; }

		virtual PosType GetAlignmentX() const;
		
		virtual PosType GetAlignmentY() const;
		
		virtual PosType GetAbsX() const;

		virtual PosType GetAbsY() const;

		virtual inline SizeType GetWidth() const { return _width; }

		virtual inline SizeType GetHeight() const { return _height; }
		
		virtual inline ControlState GetState() const { return _state; }
		
		virtual inline uint8_t GetColorRed(ControlState controlState) const 
		{ return _colorRed[controlState]; }

		virtual inline uint8_t GetColorGreen(ControlState controlState) const 
		{ return _colorGreen[controlState]; }

		virtual inline uint8_t GetColorBlue(ControlState controlState) const 
		{ return _colorBlue[controlState]; }

		virtual inline uint8_t GetColorAlpha(ControlState controlState) const 
		{ return _colorAlpha[controlState]; }

		virtual inline Control* GetParent() const { return _parent; }

		virtual Control* GetChild(cchar* id) const;

		virtual Control* GetChild(uint32_t i) const { return _children[i]; }

		virtual size_t GetChildrenCount() const { return _childrenCount; }
		
		virtual Control* GetControlAt(MousePosType x, MousePosType y);

		virtual inline MousePosType GetDragX() const { return _dragX; }

		virtual inline MousePosType GetDragY() const { return _dragY; }
		
		static inline Control* GetHoveredControl() { return _hoveredControl; }

		static inline Control* GetFocusedControl() { return _focusedControl; }
		
		virtual void SetPosition(PosType x, PosType y);

		virtual void SetX(PosType x);

		virtual void SetY(PosType y);

		virtual void SetSize(SizeType width, SizeType height);

		virtual void SetWidth(SizeType width);
		
		virtual void SetHeight(SizeType height);
		
		virtual void SetAlignment(Alignment alignment);
		
		virtual void SetState(ControlState state);

		virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

		virtual void SetColor(ControlState controlState, uint8_t red, uint8_t green, uint8_t blue, 
			uint8_t alpha);

		virtual void SetVisible(bool visible);

		virtual inline void SetConsumeMouseEvents(bool consumeMouseEvents) 
		{ _consumeMouseEvents = consumeMouseEvents; }

		virtual inline void SetConsumeKeyboardEvents(bool consumeKeyboardEvents) 
		{ _consumeKeyboardEvents = consumeKeyboardEvents; }
		
		virtual void SetParent(Control* parent);
		
		virtual inline void SetDragX(MousePosType dragX) { _dragX = dragX; }

		virtual inline void SetDragY(MousePosType dragY) { _dragY = dragY; }

		virtual inline void SetDraggable(bool draggable) { _draggable = draggable; }

		static void SetHoveredControl(Control* control) { _hoveredControl = control; }

		static void SetFocusedControl(Control* control);

	public:

		virtual void OnControlStateChanged();

		virtual void OnMouseMove(MousePosType x, MousePosType y);

		virtual void OnMouseEnter();

		virtual void OnMouseLeave();

		virtual void OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button);

		virtual void OnMouseButtonUp(MousePosType x, MousePosType y, MouseButton button);

		virtual void OnKeyDown(Key key);

		virtual void OnKeyUp(Key key);

		virtual void OnTextInput(std::string text);

		virtual void OnGotFocus();

		virtual void OnLostFocus();

		virtual void OnClick();

	public:

		OnStateChangedEvent onControlStateChanged;
		OnMouseMoveEvent onMouseMove;
		OnMouseEnterEvent onMouseEnter;
		OnMouseLeaveEvent onMouseLeave;
		OnMouseButtonEvent onMouseButton;
		OnKeyEvent onKey;
		OnTextInputEvent onTextInput;
		OnFocusEvent onFocus;
		OnClickEvent onClick;

	protected:

		bool _visible;
		bool _consumeMouseEvents;
		bool _consumeKeyboardEvents;
		bool _draggable;
		Alignment _alignment;
		ControlState _state;
		uint8_t _colorRed[CONTROL_STATE_COUNT];
		uint8_t _colorGreen[CONTROL_STATE_COUNT];
		uint8_t _colorBlue[CONTROL_STATE_COUNT];
		uint8_t _colorAlpha[CONTROL_STATE_COUNT];
		size_t _childrenCount;
		PosType _x;
		PosType _y;
		SizeType _width;
		SizeType _height;
		MousePosType _dragX;
		MousePosType _dragY;


		Control* _parent;
		std::vector<Control*> _children;

	private:

		static Control* _hoveredControl;
		static Control* _focusedControl;
};

#endif