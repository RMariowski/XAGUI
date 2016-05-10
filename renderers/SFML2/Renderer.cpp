#include "Main.h"

std::vector<Font*> Renderer::_fonts;

Renderer::Renderer(XAGUI::SizeType screenWidth, XAGUI::SizeType screenHeight, XAGUI::SizeType canvasWidth, 
				   XAGUI::SizeType canvasHeight)
	: XAGUI::Renderer(screenWidth, screenHeight, canvasWidth, canvasHeight), _window(0), _renderTarget(0)
{ XAGUI::XAGUI::SetRenderer(this); }

Renderer::~Renderer() { Release(); }

bool Renderer::Initialize(sf::RenderWindow* window)
{
	_window = window;

	_renderTexture.create(GetCanvasWidth(), GetCanvasHeight());
	
	SetDefaultRenderTarget();

	return true;
}

void Renderer::Clear() { _window->clear(sf::Color::Black); }

void Renderer::ClearCanvas() 
{ 
	_renderTexture.clear(sf::Color::Black);
	Clear();
}

void Renderer::RenderCanvas() 
{ 
	_sprite.setTexture(_renderTexture.getTexture());
	_sprite.setPosition(0.0f, 0.0f);
	_sprite.setTextureRect(sf::IntRect(0, 0, GetScreenWidth(), GetScreenHeight()));
	_sprite.setColor(sf::Color::White);
	
	_window->draw(_sprite);
}

void Renderer::Render(StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y)
{
	_staticText = *static_cast<StaticText*>(staticText)->Get();
	_staticText.setPosition(x, y);
	_staticText.setCharacterSize(staticText->GetFont()->GetSize());
	_renderTarget->draw(_staticText);
}

void Renderer::Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, XAGUI::Flip flip)
{
	_staticText = *static_cast<StaticText*>(staticText)->Get();
	_staticText.setPosition(x, y);
	_staticText.setCharacterSize(staticText->GetFont()->GetSize());
	
	_renderTarget->draw(_staticText);
}

void Renderer::Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, 
					  XAGUI::SizeType width, XAGUI::SizeType height, XAGUI::SrcPosType srcX, 
					  XAGUI::SrcPosType srcY, XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, 
					  XAGUI::Flip flip)
{
	_staticText = *static_cast<StaticText*>(staticText)->Get();
	_staticText.setPosition(x, y);
	_staticText.setCharacterSize(staticText->GetFont()->GetSize());
	
	_renderTarget->draw(_sprite);
}

void Renderer::Render(XAGUI::Texture* texture, XAGUI::PosType x, XAGUI::PosType y, XAGUI::SizeType width, 
					  XAGUI::SizeType height, XAGUI::SrcPosType srcX, XAGUI::SrcPosType srcY, 
					  XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, uint8_t red,
					  uint8_t green, uint8_t blue, uint8_t alpha, XAGUI::Flip flip)
{
	_sprite.setTexture(*static_cast<Texture*>(texture)->Get());
	_sprite.setPosition(x, y);
	_sprite.setTextureRect(sf::IntRect(srcX, srcY, srcWidth, srcHeight));
	_sprite.setColor(sf::Color(red, green, blue, alpha));
	
	_renderTarget->draw(_sprite);
}

void Renderer::Present() { _window->display(); }

void Renderer::Release()
{ 
	size_t fontsCount = _fonts.size();
	for (size_t i = 0; i < fontsCount; i++) delete _fonts[i]; 
}

Font* Renderer::GetFont(cchar* name, uint8_t size) const
{
	// Check if font already exists...
	Font* font = 0;
	size_t fontsCount = _fonts.size();
	for (size_t i = 0; i < fontsCount; i++)
	{
		font = _fonts[i];
		if (strcmp(name, font->GetName()) == 0 && font->GetSize() == size) return font;
	}

	// ...if not, we need to create new one...
	font = new Font();
	if (!font->Load(name, size)) 
	{
		SAFE_DELETE(font);
	}
	else
	{
		// ..and add to the font list.
		_fonts.push_back(font);
	}

	// ..and add to the font list.
	_fonts.push_back(font);
	return font;
}

StaticText* Renderer::GetStaticText(cchar* name, uint8_t size, cchar* text) const
{
	StaticText* staticText = new StaticText();
	staticText->SetFont(name, size); 
	staticText->SetText(text);
	return staticText;
}

Texture* Renderer::GetTexture(cchar* name) const
{
	Texture* texture = new Texture();
	if (!texture->Load(name))
	{
		SAFE_DELETE(texture);
	}
	return texture;
}
