#ifndef XAGUI_FONT_H
#define XAGUI_FONT_H

XAGUI_EXPORT class Font
{
	public:

		Font();

		virtual bool Load(cchar* name, uint8_t size);

		virtual inline cchar* GetName() const { return _name.c_str(); }

		virtual inline uint8_t GetSize() const { return _size; }

		virtual SizeType GetTextWidth(cchar* text) const = 0;

		virtual SizeType GetTextHeight(cchar* text) const = 0;

	protected:

		uint8_t _size;
		std::string _name;
};

#endif
