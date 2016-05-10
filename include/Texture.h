#ifndef XAGUI_TEXTURE_H
#define XAGUI_TEXTURE_H

XAGUI_EXPORT class Texture
{
	public:

		Texture();

		virtual bool Load(cchar* name);

		virtual inline cchar* GetName() const { return _name.c_str(); }

	protected:

		std::string _name;
};

#endif
