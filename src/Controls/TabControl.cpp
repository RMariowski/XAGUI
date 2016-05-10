#include <XAGUI.h>

namespace XAGUI
{

TabControl::TabControl() 
	: _currentTab(0)
{ AddTab(new Tab()); }

TabControl::~TabControl()
{
	uint8_t tabsCount = GetTabsCount();
	for (uint8_t i = 0; i < tabsCount; i++)
	{
		SAFE_DELETE(_tabs[i]);
	}
}

void TabControl::Render()
{
	if (!IsVisible()) return;

	XAGUI::GetRenderer()->Render(XAGUI::GetSkin(), GetAbsX(), GetAbsY(), Button::GetWidth(), 
		Button::GetHeight(), GetSrcX(GetState()), GetSrcY(GetState()), GetSrcWidth(), GetSrcHeight(), 
		GetColorRed(GetState()), GetColorGreen(GetState()), GetColorBlue(GetState()), 
		GetColorAlpha(GetState()), GetFlip());
	Control::Render();
}

void TabControl::AddTab(Tab* tab) 
{ 
	uint8_t tabsCount = GetTabsCount();
	if (tabsCount > 0)
	{
		Button* button = GetTab(tabsCount - 1)->GetButton();
		tab->GetButton()->SetX(button->GetX() + button->GetWidth()); 

		for (ControlState i = 0; i < CONTROL_STATE_COUNT; i++)
		{
			tab->GetButton()->SetSrcX(i, button->GetSrcX(i));
			tab->GetButton()->SetSrcY(i, button->GetSrcY(i));
		}

		tab->GetButton()->SetSrcWidth(button->GetSrcWidth());
		tab->GetButton()->SetSrcHeight(button->GetSrcHeight());
	}
	else SetCurrentTab(tab);

	tab->GetButton()->onClick.bind(this, &TabControl::OnTabClick);

	_tabs.push_back(tab);
	AddChild(tab->GetButton());
	AddChild(tab->GetPage());

	Update();
}

SizeType TabControl::GetHeight() const
{
	SizeType height = Button::GetHeight();
	height += GetTab(0)->GetButton()->GetHeight();
	return height;
}

TabControl::Tab* TabControl::GetTabByButton(Button* button) const
{
	Tab* tab = 0;
	uint8_t tabsCount = GetTabsCount();
	for (uint8_t i = 0; i < tabsCount; i++)
	{
		tab = GetTab(i);
		if (tab->GetButton() == button) return tab;
	}
	return 0;
}

void TabControl::SetHeight(SizeType height) 
{ 
	if (GetHeight() == height) return;
	height -= GetTab(0)->GetButton()->GetHeight();
	Button::SetHeight(height);

	Update();
}

void TabControl::SetCurrentTab(Tab* tab)
{
	_currentTab = tab;
	Update();
}

void TabControl::OnTabClick(Control* control)
{ SetCurrentTab(GetTabByButton(static_cast<Button*>(control))); }

void TabControl::Update()
{
	Tab* tab = 0;
	uint8_t tabsCount = GetTabsCount();
	for (uint8_t i = 0; i < tabsCount; i++)
	{
		tab = GetTab(i);
		tab->GetPage()->SetSize(Button::GetWidth(), Button::GetHeight());
		tab->GetButton()->SetY(-tab->GetButton()->GetHeight());

		if (tab == GetCurrentTab())
		{
			tab->GetButton()->Disable();
			tab->GetPage()->Show();
		}
		else 
		{
			tab->GetButton()->Enable();
			tab->GetPage()->Hide();
		}
	}
}

};