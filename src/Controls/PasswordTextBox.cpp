#include <XAGUI.h>

namespace XAGUI
{

PasswordTextBox::PasswordTextBox() { }

void PasswordTextBox::InsertText(std::string text, int32_t position)
{
	uint32_t length = utf8::distance(text.begin(), text.end());
	if (GetLabel()->GetStaticText()->GetLength() + length > GetMaxCharacters()) return;
	
	uint8_t offset = 0;
	if (position > 0)
	{
		// BUG: Let ó be '{' and '}'. If you type 'e', 'ó' and 'e' you will get e{e} in unencrypted 
		// string instead of e{}e.
		std::string::iterator it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
			GetLabel()->GetPointerString()->begin() + position);

		while (it != GetLabel()->GetPointerString()->begin() + position + offset) 
		{
			offset++;
			it = utf8::find_invalid(GetLabel()->GetPointerString()->begin(), 
				GetLabel()->GetPointerString()->begin() + position + offset);
			if (it == GetLabel()->GetPointerString()->begin() + position + offset) break;
		}
	}

	_text.insert(position + offset, text);
	printf("%s\n", _text.c_str()); // To check if bug is fixed

	std::string buffer;
	for (uint32_t i = 0; i < length; i++)
		buffer += GetPasswordChar();

	GetLabel()->GetPointerString()->insert(position, buffer.c_str());
	GetLabel()->SetText(GetLabel()->GetText());
	SetCaretPosition(GetCaretPosition() + length);
}

void PasswordTextBox::RemoveCharacter(int32_t position)
{
	if (GetCaretPosition() < 1 || GetLabel()->GetStaticText()->GetLength() < 1) return;

	GetLabel()->GetPointerString()->erase(position, 1);
		
	_text.erase(position, 1);
    std::string::iterator it = utf8::find_invalid(_text.begin(), _text.end());

	uint8_t offset = 0;
	while (it != _text.end()) 
	{
		_text.erase(it);
		it = utf8::find_invalid(_text.begin(), _text.end());
		offset++;
    }

	GetLabel()->SetText(GetLabel()->GetText());
	SetCaretPosition(position);
}

void PasswordTextBox::SetText(std::string text) 
{ 
	if (GetLabel()->GetStaticText()->GetLength() + utf8::distance(text.begin(), text.end()) > 
		GetMaxCharacters()) return;
	
	_text = text;
	std::string buffer = "";
	for (int32_t i = 0; i < utf8::distance(_text.begin(), _text.end()); i++)
		buffer += GetPasswordChar();
	TextBox::SetText(buffer.c_str()); 
}

void PasswordTextBox::SetPasswordChar(cchar* passwordChar)
{ 
	_passwordChar = passwordChar; 
	SetText(GetText());
}

};