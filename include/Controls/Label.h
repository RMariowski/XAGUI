#ifndef XAGUI_LABEL_H
#define XAGUI_LABEL_H

XAGUI_EXPORT class Label : public Control
{
	public:

		Label();

		virtual ~Label();

		virtual void Render();

		virtual inline cchar* GetText() const { return GetStaticText()->GetText(); }
	
		virtual inline std::string GetString() const { return GetStaticText()->GetString(); }
		
		virtual inline std::string* GetPointerString() const 
		{ return GetStaticText()->GetPointerString(); }

		virtual inline StaticText* GetStaticText() const { return _staticText; }
		
		virtual inline Flip GetFlip() const { return _flip; }

		virtual void SetFont(cchar* name, uint8_t size);

		virtual void SetText(cchar* text);
		
		virtual void SetText(cchar* fontName, uint8_t fontSize, cchar* text);
		
		virtual void SetWidth(SizeType width);
		
		virtual void SetHeight(SizeType height);
		
		virtual void SetState(ControlState state);

		virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

		virtual void SetColor(ControlState controlState, uint8_t red, uint8_t green, uint8_t blue, 
			uint8_t alpha);
	
		virtual void SetFlip(Flip flip);

	protected:

		Flip _flip;

		StaticText* _staticText;
};

#endif
