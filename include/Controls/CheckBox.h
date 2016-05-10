#ifndef XAGUI_CHECK_BOX_H
#define XAGUI_CHECK_BOX_H

XAGUI_EXPORT class CheckBox : public Button
{
	public:

		CheckBox();

		virtual void Render();

		virtual inline bool IsChecked() const { return _checked; }

		virtual inline SrcPosType GetCheckedSrcX(ControlState controlState) const 
		{ return _checkedSrcX[controlState]; }

		virtual inline SrcPosType GetCheckedSrcY(ControlState controlState) const 
		{ return _checkedSrcY[controlState]; }

		virtual void SetCheckedSrc(SrcPosType srcX, SrcPosType srcY);
		
		virtual void SetCheckedSrc(ControlState controlState, SrcPosType srcX, SrcPosType srcY);

		virtual void SetCheckedSrcX(SrcPosType srcX);

		virtual void SetCheckedSrcY(SrcPosType srcY);

		virtual void SetCheckedSrcX(ControlState controlState, SrcPosType srcX);

		virtual void SetCheckedSrcY(ControlState controlState, SrcPosType srcY);

		virtual inline void SetChecked(bool checked) { _checked = checked; }

	public:

		virtual void OnClick();

	protected:

		SrcPosType _checkedSrcX[CONTROL_STATE_COUNT];
		SrcPosType _checkedSrcY[CONTROL_STATE_COUNT];

		bool _checked;
};

#endif