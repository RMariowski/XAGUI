#ifndef XAGUI_BUTTON_H
#define XAGUI_BUTTON_H

XAGUI_EXPORT class Button : public Control
{
	public:

		Button();

		virtual void Render();

		virtual inline bool IsPressed() const { return IsActive(); }

		virtual inline SrcPosType GetSrcX(ControlState controlState) const { return _srcX[controlState]; }

		virtual inline SrcPosType GetSrcY(ControlState controlState) const { return _srcY[controlState]; }

		virtual inline SrcSizeType GetSrcWidth() const { return _srcWidth; }
		
		virtual inline SrcSizeType GetSrcHeight() const { return _srcHeight; }
		
		virtual inline Flip GetFlip() const { return _flip; }

		virtual void SetSrc(SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, SrcSizeType srcHeight);
		
		virtual void SetSrc(ControlState controlState, SrcPosType srcX, SrcPosType srcY, 
			SrcSizeType srcWidth, SrcSizeType srcHeight);

		virtual void SetSrcX(SrcPosType srcX);
		
		virtual void SetSrcY(SrcPosType srcY);

		virtual void SetSrcX(ControlState controlState, SrcPosType srcX);
		
		virtual void SetSrcY(ControlState controlState, SrcPosType srcY);
		
		virtual void SetSrcWidth(SrcSizeType srcWidth);

		virtual void SetSrcHeight(SrcSizeType srcHeight);

		virtual void SetFlip(Flip flip);

	protected:

		SrcPosType _srcX[CONTROL_STATE_COUNT];
		SrcPosType _srcY[CONTROL_STATE_COUNT];
		SrcSizeType _srcWidth;
		SrcSizeType _srcHeight;
		Flip _flip;
};

#endif
