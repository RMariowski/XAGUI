#ifndef XAGUI_LIST_BOX_H
#define XAGUI_LIST_BOX_H

XAGUI_EXPORT class ListBox : public ScrollableControl
{
	public:

		ListBox();

		virtual ~ListBox();

		virtual void Render();

		virtual void AddItem(Label* item);
	
		virtual void RemoveItem(uint32_t i);

		virtual void RemoveItem();
		
		virtual void DeleteItem(uint32_t i);

		virtual void DeleteItem();

		virtual inline size_t GetItemsCount() const { return _items.size(); }

	public:

		virtual void OnMouseMove(MousePosType x, MousePosType y);

		virtual void OnMouseButtonDown(MousePosType x, MousePosType y, MouseButton button);

	protected:

		std::vector<Label*> _items;
};

#endif