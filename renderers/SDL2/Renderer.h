#ifndef XAGUI_TEST_RENDERER_H
#define XAGUI_TEST_RENDERER_H

class Renderer : public XAGUI::Renderer
{
	public:

		Renderer(XAGUI::SizeType screenWidth, XAGUI::SizeType screenHeight, XAGUI::SizeType canvasWidth, 
			XAGUI::SizeType canvasHeight);

		virtual ~Renderer();

		bool Initialize();
		
		void Clear();
		
		void ClearCanvas();

		void RenderCanvas();

		void Render(StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y);

		void Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, XAGUI::Flip flip);

		void Render(XAGUI::StaticText* staticText, XAGUI::PosType x, XAGUI::PosType y, XAGUI::SizeType width,
			XAGUI::SizeType height, XAGUI::SrcPosType srcX, XAGUI::SrcPosType srcY, 
			XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, XAGUI::Flip flip);

		void Render(XAGUI::Texture* texture, XAGUI::PosType x, XAGUI::PosType y, XAGUI::SizeType width, 
			XAGUI::SizeType height, XAGUI::SrcPosType srcX, XAGUI::SrcPosType srcY, 
			XAGUI::SrcSizeType srcWidth, XAGUI::SrcSizeType srcHeight, uint8_t red, uint8_t green,
			uint8_t blue, uint8_t alpha, XAGUI::Flip flip);

		void Present();

		void Release();
		
		inline SDL_Window* GetWindow() const { return _window; }

		inline SDL_Renderer* Get() const { return _renderer; }

		inline Texture* GetCanvas() const { return _canvas; }

		Font* GetFont(cchar* name, uint8_t size) const;

		StaticText* GetStaticText(cchar* name, uint8_t size, cchar* text) const;

		Texture* GetTexture(cchar* name) const;
		
		inline void SetDefaultRenderTarget() { SDL_SetRenderTarget(Get(), 0); }
		
		inline void SetCanvasAsRenderTarget() { SDL_SetRenderTarget(Get(), GetCanvas()->Get()); }

		inline void SetRenderTarget(Texture* target) { SDL_SetRenderTarget(Get(), target->Get()); }

	protected:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		Texture* _canvas;
		SDL_Surface* _surface;
		SDL_Texture* _texture;
		SDL_Rect _src;
		SDL_Rect _dst;
		SDL_Color _color;	
		static std::vector<Font*> _fonts;
};

#endif
