#ifndef XAGUI_STATIC_TEXT_H
#define XAGUI_STATIC_TEXT_H

XAGUI_EXPORT class StaticText
{
	public:

		StaticText();

		virtual inline Font* GetFont() const { return _font; }
		
		virtual inline cchar* GetText() const { return _text.c_str(); }

		virtual inline std::string GetString() { return _text; }
		
		virtual inline std::string* GetPointerString() { return &_text; }

		virtual inline uint32_t GetLength() const { return utf8::distance(_text.begin(), _text.end()); }
		
		virtual inline uint8_t GetRed() const { return _red; }

		virtual inline uint8_t GetGreen() const { return _green; }

		virtual inline uint8_t GetBlue() const { return _blue; }

		virtual inline uint8_t GetAlpha() const { return _alpha; }

		virtual void SetFont(cchar* name, uint8_t size) = 0;

		virtual inline void SetText(cchar* text) { _text = text; }

		virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

	protected:

		uint8_t _red;
		uint8_t _green;
		uint8_t _blue; 
		uint8_t _alpha;

		Font* _font;
		std::string _text;
};

#endif
