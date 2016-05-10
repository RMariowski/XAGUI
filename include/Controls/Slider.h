#ifndef XAGUI_SLIDER_H
#define XAGUI_SLIDER_H

XAGUI_EXPORT class Slider : public Button
{
	public:

		Slider();

		virtual inline Orientation GetOrientation() const { return _orientation; }

		virtual inline Button* GetMarker() const { return _marker; }
		
		virtual inline PosType GetMarkerOffsetX() const { return _markerOffsetX; }
		
		virtual inline PosType GetMarkerOffsetY() const { return _markerOffsetY; }
		
		virtual inline int32_t GetMinValue() const { return _minValue; }
		
		virtual inline int32_t GetMaxValue() const { return _maxValue; }

		virtual inline int32_t GetValue() const { return _value; }
	
		virtual void SetOrientation(Orientation orientation) { _orientation = orientation; }

		virtual void SetMarkerOffsetX(PosType markerOffsetX);
		
		virtual void SetMarkerOffsetY(PosType markerOffsetY);

		virtual void SetMinValue(int32_t minValue);

		virtual void SetMaxValue(int32_t maxValue);

		virtual void SetValue(int32_t value);

	public:

		virtual void OnMouseMove(MousePosType x, MousePosType y);

		virtual void OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button);

		virtual void OnValueChanged();

		virtual void MarkerOnMouseMove(Control* control, MousePosType x, MousePosType y);

		virtual void MarkerOnMouseButton(Control* control, MousePosType x, MousePosType y, 
			MouseButton button, bool down);

	public:

		OnValueChangedEvent onValueChanged;

	protected:

		Orientation _orientation;
		PosType _markerOffsetX;
		PosType _markerOffsetY;
		int32_t _value;
		int32_t _minValue;
		int32_t _maxValue;

		Button* _marker;
};

#endif