#ifndef XAGUI_TAB_CONTROL_H
#define XAGUI_TAB_CONTROL_H

XAGUI_EXPORT class TabControl : public Button
{
	public:

		class Tab
		{
			public:

				Tab()
				{
					button = new Button();
					page = new TabPage();
				}

				virtual inline Button* GetButton() const { return button; }

				virtual inline TabPage* GetPage() const { return page; }

			private:

				Button* button;
				TabPage* page;
		};

	public:

		TabControl();

		virtual ~TabControl();

		virtual void Render();

		virtual void AddTab(Tab* Tab);

		virtual SizeType GetHeight() const;

		virtual inline uint8_t GetTabsCount() const { return _tabs.size(); }
		
		virtual inline Tab* GetTab(uint8_t i) const { return _tabs[i]; }
		
		virtual Tab* GetTabByButton(Button* button) const;

		virtual inline Tab* GetCurrentTab() const { return _currentTab; }

		virtual void SetHeight(SizeType height);

		virtual inline void SetCurrentTab(Tab* tab);

	public:

		virtual void OnTabClick(Control* control);

	protected:

		virtual void Update();

	protected:

		std::vector<Tab*> _tabs;
		Tab* _currentTab;
};

#endif