#ifndef XAGUI_TEST_FONT_H
#define XAGUI_TEST_FONT_H

class Font : public XAGUI::Font
{
	public:
		
		Font();

		virtual ~Font();

		virtual bool Load(cchar* name, uint8_t size);

		virtual void Release();

		virtual inline sf::Font* Get() const { return _font; }
		
		virtual XAGUI::SizeType GetTextWidth(cchar* text) const;

		virtual XAGUI::SizeType GetTextHeight(cchar* text) const;

	protected:

		 sf::Font* _font;
};

#endif
