#ifndef XAGUI_MULTILINE_TEXT_BOX_H
#define XAGUI_MULTILINE_TEXT_BOX_H

XAGUI_EXPORT class MultilineTextBox : public TextBox
{
	public:

		MultilineTextBox();

		virtual ~MultilineTextBox();
		
		virtual void Render();

		virtual void InsertText(std::string text, int32_t position);

		virtual void AddLine(std::string text);
		
		virtual void AddLine(uint32_t i, std::string text);

		virtual void RemoveCharacter(int32_t position);

		virtual void RemoveLine(uint32_t i);

		virtual inline uint32_t GetLinesCount() const { return _lines.size(); }

		virtual inline Label* GetLine(uint32_t i) const { return _lines[i]; }

		virtual inline uint32_t GetCaretLinePosition() const { return _caretLinePosition; }

		virtual void SetText(std::string text);
		
		virtual void SetCaretPosition(int32_t position);
		
		virtual void SetCaretPosition(int32_t position, int32_t line);

		virtual void SetCaretLinePosition(int32_t line);

	public:

		virtual void OnKeyDown(Key key);

		virtual void OnTextInput(std::string text);

	protected:

		virtual void UpdateLine(uint32_t i); 

		virtual void UpdateLines();

	protected:

		uint32_t _caretLinePosition;
		std::vector<Label*> _lines;
};


#endif