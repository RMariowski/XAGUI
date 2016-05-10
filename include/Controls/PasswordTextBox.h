#ifndef XAGUI_PASSWORD_TEXT_BOX_H
#define XAGUI_PASSWORD_TEXT_BOX_H

XAGUI_EXPORT class PasswordTextBox : public TextBox
{
	public:

		PasswordTextBox();

		virtual void InsertText(std::string text, int32_t position);

		virtual void RemoveCharacter(int32_t position);

		virtual inline cchar* GetText() const { return _text.c_str(); }
		
		virtual inline cchar* GetPasswordChar() const { return _passwordChar.c_str(); }

		virtual void SetText(std::string text);

		virtual void SetPasswordChar(cchar* passwordChar);

	protected:

		std::string _text;
		std::string _passwordChar;
};

#endif