#ifndef XAGUI_TEST_RENDERER_H
#define XAGUI_TEST_RENDERER_H

class Renderer : public XAGUI::Renderer
{
	public:

		Renderer(XAGUI::SizeType screenWidth, XAGUI::SizeType screenHeight, XAGUI::SizeType canvasWidth, 
			XAGUI::SizeType canvasHeight);

		virtual ~Renderer();

		virtual bool Initialize(sf::RenderWindow* window);
		
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

		virtual void Present();

		virtual void Release();
		
		virtual Font* GetFont(cchar* name, uint8_t size) const;

		virtual StaticText* GetStaticText(cchar* name, uint8_t size, cchar* text) const;

		virtual Texture* GetTexture(cchar* name) const;

		inline void SetDefaultRenderTarget() { _renderTarget = _window; }
		
		inline void SetCanvasAsRenderTarget() { _renderTarget = &_renderTexture; }

	protected:

		sf::RenderWindow* _window;
		sf::RenderTexture _renderTexture;
		sf::RenderTarget* _renderTarget;
		sf::Text _staticText;
		sf::Sprite _sprite;

		static std::vector<Font*> _fonts;
};

#endif
