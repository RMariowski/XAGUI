#ifndef XAGUI_TEST_TEXTURE_H
#define XAGUI_TEST_TEXTURE_H

class Texture : public XAGUI::Texture
{
	public:

		Texture();

		virtual ~Texture();

		virtual bool Load(cchar* name);
		
		virtual void Release();
		 
		virtual inline sf::Texture* Get() const { return _texture; }

	public:

		sf::Texture* _texture;
};

#endif
