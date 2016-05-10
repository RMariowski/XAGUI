#ifndef XAGUI_ANALOG_STICK_H
#define XAGUI_ANALOG_STICK_H

XAGUI_EXPORT class AnalogStick : public Button
{
	public:

		AnalogStick();

		virtual void Render();

		void ResetStick();

		virtual inline PosType GetStickX() const { return _stickX; }

		virtual inline PosType GetStickY() const { return _stickY; }

		virtual inline SrcPosType GetStickSrcX(ControlState controlState) const 
		{ return _stickSrcX[controlState]; }
		
		virtual inline SrcPosType GetStickSrcY(ControlState controlState) const 
		{ return _stickSrcY[controlState]; }

		virtual inline float GetValueX() const { return _valueX; }
		
		virtual inline float GetValueY() const { return _valueY; }
		
		virtual void SetX(PosType x);

		virtual void SetY(PosType y);

		virtual void SetWidth(SizeType width);

		virtual void SetHeight(SizeType height);

		virtual void SetStickX(PosType stickX);
		
		virtual void SetStickY(PosType stickY);
		
		virtual void SetValueX(float valueX);

		virtual void SetValueY(float valueY);
		
		virtual void SetStickSrc(SrcPosType stickSrcX, SrcPosType stickSrcY);

		virtual void SetStickSrcX(SrcPosType stickSrcX);
		
		virtual void SetStickSrcY(SrcPosType stickSrcY);
		
		virtual void SetStickSrc(ControlState controlState, SrcPosType stickSrcX, SrcPosType stickSrcY);

		virtual void SetStickSrcX(ControlState controlState, SrcPosType stickSrcX);
		
		virtual void SetStickSrcY(ControlState controlState, SrcPosType stickSrcY);
	
	public:

		virtual void OnMouseMove(MousePosType x, MousePosType y);

		virtual void OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button);

		virtual void OnMouseButtonUp(MousePosType x, MousePosType y, MouseButton button);

		virtual void OnValueChanged();

	public:

		OnValueChangedEvent onValueChanged;

	protected:

		PosType _stickX;
		PosType _stickY;
		SrcPosType _stickSrcX[CONTROL_STATE_COUNT];
		SrcPosType _stickSrcY[CONTROL_STATE_COUNT];
		float _valueX;
		float _valueY;
};

#endif