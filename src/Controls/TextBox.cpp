#include <XAGUI.h>

namespace XAGUI
{

TextBox::TextBox()
	: _caretPositionX(0), _caretPositionY(0), _maxCharacters(0xffff), _caretSrcX(0), _caretSrcY(0),
	_caretSrcWidth(0), _caretSrcHeight(0), _caretPosition(0), _label(0)
{ 
	_label = new Label(); 
	GetLabel()->SetParent(this); 
	SetConsumeKeyboardEvents(true);
}

TextBox::~TextBox() { delete _label; }

void TextBox::Render()
{
	if (!IsVisible()) return;
	
	ScrollableControl::Render();
	GetLabel()->Render();
	
	if (Control::GetFocusedControl() != this) return;
	
	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetCaretPositionX(), GetCaretPositionY(), 
		static_cast<SizeType>(GetCaretSrcWidth()), GetLabel()->GetHeight(), GetCaretSrcX(), GetCaretSrcY(),
		GetCaretSrcWidth(), GetCaretSrcHeight(), GetLabel()->GetColorRed(GetState()), 
		GetLabel()->GetColorGreen(GetState()), GetLabel()->GetColorBlue(GetState()), 
		GetLabel()->GetColorAlpha(GetState()), GetFlip());
}

void TextBox::InsertText(std::string text, int32_t position)
{
	if (GetLabel()->GetStaticText()->GetLength() + utf8::distance(text.begin(), text.end()) > 
		GetMaxCharacters()) return;

	GetLabel()->GetPointerString()->insert(position, text);
	GetLabel()->SetText(GetLabel()->GetText());
	SetCaretPosition(GetCaretPosition() + text.length());
}

void TextBox::RemoveCharacter(int32_t position)
{
	if (GetCaretPosition() < 1 || GetLabel()->GetStaticText()->GetLength() < 1) return;
	
	GetLabel()->GetStaticText()->GetPointerString()->erase(position, 1);

    std::string::iterator it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
		GetLabel()->GetPointerString()->end());

	uint8_t offset = 0;
	while (it != GetLabel()->GetPointerString()->end()) 
	{
		offset++;
		GetLabel()->GetPointerString()->erase(it);
		it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
			GetLabel()->GetPointerString()->end());
    }

	SetText(GetLabel()->GetText());
	SetCaretPosition(position - offset);
}

void TextBox::SetText(std::string text) 
{ 
	if (utf8::distance(text.begin(), text.end()) > GetMaxCharacters()) return;
	
	GetLabel()->SetText(text.c_str()); 
	SetCaretPosition(GetLabel()->GetPointerString()->length());
}

void TextBox::SetMaxCharacters(uint16_t maxCharacters)
{
	if (GetLabel()->GetStaticText()->GetLength() > maxCharacters)
		GetLabel()->SetText(GetLabel()->GetPointerString()->substr(0, maxCharacters).c_str());
	_maxCharacters = maxCharacters;
}

void TextBox::SetCaretPosition(int position)
{
	if (position < 0 || static_cast<uint32_t>(position) > strlen(GetLabel()->GetStaticText()->GetText())) 
		return;

	std::string::iterator it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
		GetLabel()->GetPointerString()->begin() + position);
	
	char offset = 0;
	if (it != GetLabel()->GetPointerString()->begin() + position)
	{
		do 
		{
			(GetCaretPosition() > static_cast<uint32_t>(position)) ? offset-- : offset++;

			it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
				GetLabel()->GetPointerString()->begin() + position + offset);
		}
		while (it != GetLabel()->GetPointerString()->begin() + position + offset);
	}

	_caretPosition = position + offset;
	_caretPositionX = static_cast<PosType>(GetLabel()->GetAbsX() + 
		GetLabel()->GetStaticText()->GetFont()->GetTextWidth(GetLabel()->GetPointerString()->substr(0, 
		position + offset).c_str()));
	_caretPositionY = GetLabel()->GetAbsY();

	XAGUI::SetRequestRedraw(true);
}

void TextBox::SetCaretPosition(PosType x, PosType y)
{
	PosType characterX = GetLabel()->GetAbsX();
	SizeType characterWidth = 0;

	uint8_t offset = 1;
	uint32_t length = GetLabel()->GetPointerString()->length();
	for (uint32_t i = 0; i < length; i += offset)
	{
		offset = 1;

		std::string::iterator it = utf8::find_invalid(GetLabel()->GetPointerString()->begin() + i, 
			GetLabel()->GetPointerString()->begin() + i + offset);
		
		if (it != GetLabel()->GetPointerString()->begin() + i + offset)
		{
			do 
			{
				offset++;
				it = utf8::find_invalid(GetLabel()->GetPointerString()->begin() + i, 
					GetLabel()->GetPointerString()->begin() + i + offset);
			}
			while (it != GetLabel()->GetStaticText()->GetPointerString()->begin() + i + offset);
		}

		characterWidth = GetLabel()->GetStaticText()->GetFont()->GetTextWidth(
			GetLabel()->GetStaticText()->GetPointerString()->substr(i, offset).c_str());

		if(x >= characterX && x <= characterX + characterWidth)
		{
			SetCaretPosition(i);
			break;
		}

		characterX += static_cast<PosType>(characterWidth);
	}

	if (x > characterX + characterWidth)
		SetCaretPosition(length);
}

void TextBox::SetCaretSrc(SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, SrcSizeType srcHeight)
{
	SetCaretSrcX(srcX);
	SetCaretSrcY(srcY);
	SetCaretSrcWidth(srcWidth);
	SetCaretSrcHeight(srcHeight);
}

void TextBox::SetCaretSrcX(SrcPosType srcX) 
{ 
	_caretSrcX = srcX; 
	XAGUI::SetRequestRedraw(true);
}

void TextBox::SetCaretSrcY(SrcPosType srcY) 
{ 
	_caretSrcY = srcY; 
	XAGUI::SetRequestRedraw(true);
}

void TextBox::SetCaretSrcWidth(SrcSizeType srcWidth) 
{ 
	_caretSrcWidth = srcWidth; 
	XAGUI::SetRequestRedraw(true);
}

void TextBox::SetCaretSrcHeight(SrcSizeType srcHeight) 
{ 
	_caretSrcHeight = srcHeight; 
	XAGUI::SetRequestRedraw(true);
}

void TextBox::OnMouseMove(MousePosType x, MousePosType y)
{
	if (IsActive())
		SetCaretPosition(static_cast<PosType>(x), static_cast<PosType>(y));
}

void TextBox::OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button)
{
	if (button == MOUSE_BUTTON_LEFT)
		SetCaretPosition(static_cast<PosType>(x), static_cast<PosType>(y));
}

void TextBox::OnKeyDown(Key key)
{
	switch (key)
	{
		case KEY_LEFT:
			SetCaretPosition(GetCaretPosition() - 1);
			break;

		case KEY_RIGHT:
			SetCaretPosition(GetCaretPosition() + 1);
			break;

		case KEY_BACKSPACE:
			RemoveCharacter(GetCaretPosition() - 1);
			break;
	}
}

void TextBox::OnTextInput(std::string text) { InsertText(text.c_str(), GetCaretPosition()); }

void TextBox::OnGotFocus()
{
#if defined(__ANDROID__) || defined(__IPHONEOS__)
	XAGUI::ShowOnScreenKeyboard();
#endif
}

void TextBox::OnLostFocus()
{
#if defined(__ANDROID__) || defined(__IPHONEOS__)
	XAGUI::HideOnScreenKeyboard();
#endif
}

};