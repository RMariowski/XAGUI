#include <XAGUI.h>
namespace XAGUI
{

MultilineTextBox::MultilineTextBox()
	: _caretLinePosition(0)
{ }

MultilineTextBox::~MultilineTextBox() 
{ 
	uint32_t linesCount = GetLinesCount();
	for (uint32_t i = 0; i < linesCount; i++) delete _lines[i];
	_lines.clear(); 
}

void MultilineTextBox::Render()
{
	if (!IsVisible()) return;

	ScrollableControl::Render();

	uint32_t linesCount = GetLinesCount();
	for (uint32_t i = 0; i < linesCount; i++)
		GetLine(i)->Render();

	if (Control::GetFocusedControl() == this)
	{
		XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetCaretPositionX(), GetCaretPositionY(), 
			static_cast<SizeType>(GetCaretSrcWidth()), GetLabel()->GetHeight(), GetCaretSrcX(), 
			GetCaretSrcY(), GetCaretSrcWidth(), GetCaretSrcHeight(), 
			GetLabel()->GetColorRed(GetState()), GetLabel()->GetColorGreen(GetState()), 
			GetLabel()->GetColorBlue(GetState()), GetLabel()->GetColorAlpha(GetState()), GetFlip());
	}
}

void MultilineTextBox::InsertText(std::string text, int position)
{

}

void MultilineTextBox::AddLine(std::string text)
{
	uint32_t linesCount = GetLinesCount();
	if (linesCount == 1 && strcmp(_lines[0]->GetText(), "") == 0)
	{
		SetText(text);
	}
	else
	{
		Label* line = new Label();
		line->SetText(GetLabel()->GetStaticText()->GetFont()->GetName(), 
			GetLabel()->GetStaticText()->GetFont()->GetSize(), text.c_str());
		line->SetPosition(GetLabel()->GetX(), GetLabel()->GetY());

		line->SetParent(this);
		_lines.push_back(line);
		UpdateLine(linesCount); 
	}
	UpdateLines();
}

void MultilineTextBox::AddLine(uint32_t i, std::string text)
{
	Label* line = new Label();
	line->SetText(GetLabel()->GetStaticText()->GetFont()->GetName(), 
		GetLabel()->GetStaticText()->GetFont()->GetSize(), text.c_str());
	line->SetX(GetLabel()->GetX());
	
	line->SetParent(this);
	_lines.insert(_lines.begin() + i, line);
	UpdateLine(i); 
	UpdateLines();
}

void MultilineTextBox::RemoveCharacter(int position)
{
	
}

void MultilineTextBox::RemoveLine(uint32_t i)
{ 
	uint32_t linesCount = GetLinesCount();

	if (i > 0)
	{
		delete _lines[i];
		_lines.erase(_lines.begin() + i); 
	}
	else if (linesCount > 1 && i < 1)
	{
		GetLine(0)->SetText(GetLine(1)->GetText());
		
		delete _lines[1];
		_lines.erase(_lines.begin() + 1); 
	}
	else _lines[0]->SetText("");

	UpdateLines();
}

void MultilineTextBox::SetText(std::string text)
{
	uint32_t linesCount = GetLinesCount();

	if (linesCount > 0)
	{
		for (uint32_t i = linesCount - 1; i > 0; i--)
			RemoveLine(i);

		GetLine(0)->SetText(text.c_str());
	}
	else AddLine(text);

	UpdateLine(0);
	UpdateLines();
}

void MultilineTextBox::OnKeyDown(Key key)
{
	switch (key)
	{
		case KEY_RETURN:
			AddLine("");
			break;

		case KEY_LEFT:
			SetCaretPosition(GetCaretPosition() - 1);
			break;

		case KEY_RIGHT:
			SetCaretPosition(GetCaretPosition() + 1);
			break;

		case KEY_BACKSPACE:
			RemoveCharacter(GetCaretPosition() - 1);
			break;

	}
}

void MultilineTextBox::OnTextInput(std::string text) {  }

void MultilineTextBox::SetCaretPosition(int position)
{
	
}

void MultilineTextBox::SetCaretPosition(int position, int line)
{

}

void MultilineTextBox::SetCaretLinePosition(int line) 
{ 
	uint32_t linesCount = GetLinesCount();
	if (linesCount < 1) return;
	
	if (line < 0) 
	{
		_caretLinePosition = 0;
	}
	else if (static_cast<uint32_t>(line) >= linesCount)
	{
		_caretLinePosition = linesCount - 1;
	}
	else _caretLinePosition = line; 

	UpdateLines();
}

void MultilineTextBox::UpdateLine(uint32_t i)
{
	uint32_t position = std::string::npos;
	std::string lineText;
	lineText = GetLine(i)->GetText();
	position = lineText.find_first_of("\n");
	if (position != std::string::npos)
	{
		GetLine(i)->SetText(lineText.substr(0, position).c_str());
		AddLine(i + 1, lineText.substr(position + strlen("\n")).c_str());
		lineText = GetLine(i)->GetText();
	}

	SizeType width = GetLine(i)->GetStaticText()->GetFont()->GetTextWidth(lineText.c_str());
	if (width + GetLine(i)->GetX() > GetWidth())
	{
		std::string buffer = "";
		uint32_t len = lineText.length();
		for (position = 0; position < len; position++)
		{
			buffer += lineText[position];
			width = GetLine(i)->GetStaticText()->GetFont()->GetTextWidth(buffer.c_str());
			if (width + GetLine(i)->GetX() > GetWidth())
			{
				GetLine(i)->SetText(lineText.substr(0, position).c_str());
				AddLine(i + 1, lineText.substr(position).c_str());
				break;
			}
		}
	}
	
	UpdateLines();
}

void MultilineTextBox::UpdateLines()
{
	uint32_t linesCount = GetLinesCount();
	SizeType linesHeight = 0;

	// Handling all heights of lines can be very useful
	SizeType* linesHeights = new SizeType[linesCount];
	for (uint32_t i = 0; i < linesCount; i++)
	{
		if (i >= GetCaretLinePosition())
		{
			linesHeights[i] = GetLine(i)->GetStaticText()->GetFont()->GetTextHeight(GetLine(i)->GetText());
			linesHeight += linesHeights[i];
			if (static_cast<int>(linesHeight) > GetHeight() - GetLabel()->GetY())
			{
				GetLine(i)->Hide();
			}
			else
			{
				if (i == GetCaretLinePosition())
				{
					GetLine(i)->SetY(GetLabel()->GetY());
				}
				else GetLine(i)->SetY(static_cast<PosType>(GetLine(i - 1)->GetY() + linesHeights[i - 1]));
				
				GetLine(i)->Show();
			}
		}
		else GetLine(i)->Hide();
	}

	delete[] linesHeights;
}

};