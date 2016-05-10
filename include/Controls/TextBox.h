#ifndef XAGUI_TEXT_BOX_H
#define XAGUI_TEXT_BOX_H

XAGUI_EXPORT class TextBox : public ScrollableControl
{
	public:

		TextBox();

		virtual ~TextBox();

		virtual void Render();
		
		virtual void InsertText(std::string text, int32_t position);

		virtual void RemoveCharacter(int32_t position);

		virtual inline Label* GetLabel() const { return _label; }

		virtual inline cchar* GetText() const { return GetLabel()->GetText(); }

		virtual inline uint16_t GetMaxCharacters() const { return _maxCharacters; }

		virtual inline uint32_t GetCaretPosition() const { return _caretPosition; }
		
		virtual inline PosType GetCaretPositionX() const { return _caretPositionX; }
	
		virtual inline PosType GetCaretPositionY() const { return _caretPositionY; }

		virtual inline SrcPosType GetCaretSrcX() const { return _caretSrcX; }
		
		virtual inline SrcPosType GetCaretSrcY() const { return _caretSrcY; }

		virtual inline SrcSizeType GetCaretSrcWidth() const { return _caretSrcWidth; }

		virtual inline SrcSizeType GetCaretSrcHeight() const { return _caretSrcHeight; }

		virtual void SetText(std::string text);

		virtual void SetMaxCharacters(uint16_t maxCharacters);

		virtual void SetCaretPosition(int32_t position);

		virtual void SetCaretPosition(PosType x, PosType y);

		virtual void SetCaretSrc(SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, 
			SrcSizeType srcHeight);

		virtual void SetCaretSrcX(SrcPosType srcX);

		virtual void SetCaretSrcY(SrcPosType srcY);

		virtual void SetCaretSrcWidth(SrcSizeType srcWidth);

		virtual void SetCaretSrcHeight(SrcSizeType srcHeight);

	public:

		virtual void OnMouseMove(MousePosType x, MousePosType y);

		virtual void OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button);
		
		virtual void OnKeyDown(Key key);

		virtual void OnTextInput(std::string text);

		virtual void OnGotFocus();

		virtual void OnLostFocus();

	public:

		OnTextInputEvent onTextInput;

	protected:

		PosType _caretPositionX;
		PosType _caretPositionY;
		uint16_t _maxCharacters;
		SrcPosType _caretSrcX;
		SrcPosType _caretSrcY;
		SrcSizeType _caretSrcWidth;
		SrcSizeType _caretSrcHeight;
		uint32_t _caretPosition;

		Label* _label;
};

#endif