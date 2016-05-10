#ifndef XAGUI_TEST_TEXTURE_H
#define XAGUI_TEST_TEXTURE_H

class Texture : public XAGUI::Texture
{
	public:

		Texture();

		virtual ~Texture();

		virtual bool Load(cchar* name);

		virtual bool CreateTarget(XAGUI::SizeType width, XAGUI::SizeType height);

		virtual void Release();
		 
		virtual inline SDL_Texture* Get() const { return _texture; }

	protected:

		SDL_Texture* _texture;
};

#endif
