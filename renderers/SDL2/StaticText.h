#ifndef XAGUI_TEST_STATIC_TEXT_H
#define XAGUI_TEST_STATIC_TEXT_H

class StaticText : public XAGUI::StaticText
{
	public:

		StaticText();

		virtual ~StaticText();

		virtual void Release();

		virtual void SetFont(cchar* name, uint8_t size);

		virtual void SetText(cchar* text);

		virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

		virtual inline SDL_Texture* GetTexture() const { return _texture; }

	protected:
		
		SDL_Texture* _texture;
};

#endif