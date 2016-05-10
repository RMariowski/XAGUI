#include <XAGUI.h>

namespace XAGUI
{

ListBox::ListBox() { }

ListBox::~ListBox() { DeleteItem(); }

void ListBox::Render()
{
	if (!IsVisible()) return;
	
	ScrollableControl::Render();

	size_t itemsCount = GetItemsCount();
	for (size_t i = 0; i < itemsCount; i++)
		_items[i]->Render();
}

void ListBox::AddItem(Label* element) 
{ 
	size_t itemsCount = GetItemsCount();
	if (itemsCount > 0)
	{
		Label* lastItem = _items[itemsCount - 1];
		element->SetY(static_cast<PosType>(element->GetY() + lastItem->GetY() + lastItem->GetHeight()));
	}

	element->SetParent(this);
	_items.push_back(element); 
}

void ListBox::RemoveItem(uint32_t i) { _items.erase(_items.begin() + i); }

void ListBox::RemoveItem() { _items.clear(); }

void ListBox::DeleteItem(uint32_t i)
{
	SAFE_DELETE(_items[i]);
	RemoveChild(i);
}

void ListBox::DeleteItem() 
{
	uint32_t itemsCount = _items.size();
	for (uint32_t i = 0; i < itemsCount; i++)
	{
		SAFE_DELETE(_items[i]);
	}
	RemoveItem();
}

void ListBox::OnMouseMove(MousePosType x, MousePosType y)
{

}

void ListBox::OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button)
{
	if (button == MOUSE_BUTTON_LEFT)
	{
		
	}
}

};