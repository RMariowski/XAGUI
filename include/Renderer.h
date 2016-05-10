#ifndef XAGUI_RENDERER_H
#define XAGUI_RENDERER_H

XAGUI_EXPORT class Renderer
{
	public:

		Renderer(SizeType screenWidth, SizeType screenHeight, SizeType canvasWidth, SizeType canvasHeight);

		virtual void ClearCanvas() = 0;

		virtual void RenderCanvas() = 0;

		virtual void Render(StaticText* staticText, PosType x, PosType y, XAGUI::Flip flip) = 0;
		
		virtual void Render(StaticText* staticText, PosType x, PosType y, SizeType width, SizeType height,
			SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, SrcSizeType srcHeight, 
			XAGUI::Flip flip) = 0;

		virtual void Render(Texture* texture, PosType x, PosType y, SizeType width, SizeType height, 
			SrcPosType srcX, SrcPosType srcY, SrcSizeType srcWidth, SrcSizeType srcHeight, uint8_t red, 
			uint8_t green, uint8_t blue, uint8_t alpha, Flip flip) = 0;

		virtual inline SizeType GetScreenWidth() const { return _screenWidth; }

		virtual inline SizeType GetScreenHeight() const { return _screenHeight; }

		virtual inline SizeType GetCanvasWidth() const { return _canvasWidth; }

		virtual inline SizeType GetCanvasHeight() const { return _canvasHeight; }

		virtual inline float GetWidthRatio() const { return _widthRatio; }
		
		virtual inline float GetHeightRatio() const { return _heightRatio; }

		virtual Font* GetFont(cchar* name, uint8_t size) const = 0;
		
		virtual StaticText* GetStaticText(cchar* name, uint8_t size, cchar* text) const = 0;

		virtual Texture* GetTexture(cchar* name) const = 0;
		
		virtual void SetScreenSize(SizeType width, SizeType height);

		virtual void SetCanvasSize(SizeType width, SizeType height);
		
		virtual void SetDefaultRenderTarget() = 0;
		
		virtual void SetCanvasAsRenderTarget() = 0;

	protected:

		virtual void UpdateRatio();

	protected:

		SizeType _screenWidth;
		SizeType _screenHeight;
		SizeType _canvasWidth;
		SizeType _canvasHeight;
		float _widthRatio;
		float _heightRatio;
};

#endif
