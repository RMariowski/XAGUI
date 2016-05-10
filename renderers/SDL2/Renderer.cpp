#include "Main.h"

std::vector<Font*> Renderer::_fonts;

Renderer::Renderer(XAGUI::SizeType screenWidth, XAGUI::SizeType screenHeight, XAGUI::SizeType canvasWidth, 
				   XAGUI::SizeType canvasHeight)
	: XAGUI::Renderer(screenWidth, screenHeight, canvasWidth, canvasHeight), _window(0), _renderer(0), 
	_canvas(0), _surface(0), _texture(0)
{ XAGUI::XAGUI::SetRenderer(this); }

Renderer::~Renderer() { Release(); }

bool Renderer::Initialize()
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

	_window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		GetScreenWidth(), GetScreenHeight(), SDL_WINDOW_SHOWN);
	if (GetWindow() == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, SDL_GetError());
		return 0;
	}

	_renderer = SDL_CreateRenderer(GetWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (Get() == 0) 
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, SDL_GetError());
		return false;
	}
	else if (SDL_RenderTargetSupported(_renderer) == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, IMG_GetError());
		return false;
	}
	else if (TTF_Init() == -1)
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, TTF_GetError());
		return false;
	}

	_canvas = new Texture();
	if (!GetCanvas()->CreateTarget(GetCanvasWidth(), GetCanvasHeight())) 
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, SDL_GetError());
		return false;
	}

	return true;
}

void Renderer::Clear() { SDL_RenderClear(Get()); }

void Renderer::ClearCanvas()
{
	SDL_SetRenderDrawColor(Get(), 0, 0, 0, 0);
	Clear();
}

void Renderer::RenderCanvas() 
{ 
	_dst.x = 0;
	_dst.y = 0;
	_dst.w = GetScreenWidth();
	_dst.h = GetScreenHeight();
	SDL_RenderCopy(Get(), GetCanvas()->Get(), 0, &_dst); 
}

void Renderer::Render(StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y)
{
	_dst.x = x;
	_dst.y = y;

	_texture = staticText->GetTexture();
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_RenderCopy(Get(), _texture, 0, &_dst);
}

void Renderer::Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, XAGUI::Flip flip)
{
	_dst.x = x;
	_dst.y = y;

	_texture = static_cast<StaticText*>(staticText)->GetTexture();
	SDL_QueryTexture(_texture, 0, 0, &_dst.w, &_dst.h);
	SDL_RenderCopyEx(Get(), _texture, 0, &_dst, 0.0, 0, static_cast<SDL_RendererFlip>(flip));
}

void Renderer::Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, 
					  XAGUI::SizeType width, XAGUI::SizeType height, XAGUI::SrcPosType srcX, 
					  XAGUI::SrcPosType srcY, XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, 
					  XAGUI::Flip flip)
{
	_dst.x = x;
	_dst.y = y;
	_dst.w = width;
	_dst.h = height;

	_src.x = srcX;
	_src.y = srcY;
	_src.w = srcWidth;
	_src.h = srcHeight;

	_texture = static_cast<StaticText*>(staticText)->GetTexture();
	SDL_RenderCopyEx(Get(), _texture, &_src, &_dst, 0.0, 0, static_cast<SDL_RendererFlip>(flip));
}

void Renderer::Render(XAGUI::Texture* texture, XAGUI::PosType x, XAGUI::PosType y, XAGUI::SizeType width, 
					  XAGUI::SizeType height, XAGUI::SrcPosType srcX, XAGUI::SrcPosType srcY, 
					  XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, uint8_t red,
					  uint8_t green, uint8_t blue, uint8_t alpha, XAGUI::Flip flip)
{
	_dst.x = x;
	_dst.y = y;
	_dst.w = width;
	_dst.h = height;

	_src.x = srcX;
	_src.y = srcY;
	_src.w = srcWidth;
	_src.h = srcHeight;

	_texture = static_cast<Texture*>(texture)->Get();
	SDL_SetTextureColorMod(_texture, red, green, blue);
	SDL_SetTextureAlphaMod(_texture, alpha);
	SDL_RenderCopyEx(Get(), _texture, &_src, &_dst, 0.0, 0, static_cast<SDL_RendererFlip>(flip));
}

void Renderer::Present() { SDL_RenderPresent(Get()); }

void Renderer::Release()
{
	size_t fontsCount = _fonts.size();
	for (size_t i = 0; i < fontsCount; i++) delete _fonts[i];

	SAFE_DELETE(_canvas);
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
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
