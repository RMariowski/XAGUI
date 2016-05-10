#include "Main.h"

TestForm* testForm = 0;

bool quit = false;
char buffer[MAX_BUFFER];

void Event(sf::Event* event)
{
	switch (event->type)
	{
		case sf::Event::MouseMoved:
			testForm->MouseMoveEvent(event->mouseMove.x, event->mouseMove.y);
			break;

		case sf::Event::MouseButtonPressed:
			{
				testForm->MouseButtonDownEvent(event->mouseButton.x, event->mouseButton.y, 
					MouseButtonToXAGUI(event->mouseButton.button));
			}
			break;

		case sf::Event::MouseButtonReleased:
			{
				testForm->MouseButtonUpEvent(event->mouseButton.x, event->mouseButton.y, 
					MouseButtonToXAGUI(event->mouseButton.button));
			}
			break;

		case sf::Event::KeyPressed:
			{
				if (event->key.code == sf::Keyboard::Escape)
				{
					quit = true;
				}
				else testForm->KeyDownEvent(KeyToXAGUI(event->key.code));
			}
			break;

		case sf::Event::KeyReleased:
			testForm->KeyDownEvent(KeyToXAGUI(event->key.code));
			break;
	}
}

void OnExitClick(XAGUI::Control* control) { quit = true; }

void OnIncreaseClick(XAGUI::Control* control)
{
	XAGUI::ProgressBar* progressBar = static_cast<XAGUI::ProgressBar*>(testForm->GetChild(
		"pgProgressBar"));
	progressBar->SetProgress(progressBar->GetProgress() + 2);
}

void OnDecreaseClick(XAGUI::Control* control)
{
	XAGUI::ProgressBar* progressBar = static_cast<XAGUI::ProgressBar*>(testForm->GetChild(
		"pgProgressBar"));
	progressBar->SetProgress(progressBar->GetProgress() - 2);
}

void OnAnalogStickValueChanged(XAGUI::Control* control)
{
	XAGUI::AnalogStick* analogStick = static_cast<XAGUI::AnalogStick*>(control);

	sprintf(buffer, "Analog Stick Value X: %.3f | Y: %.3f", analogStick->GetValueX(), 
		analogStick->GetValueY());
	static_cast<XAGUI::Label*>(testForm->GetChild("lblAnalogStickValue"))->SetText(buffer);
}

int main()
{
	sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::RenderWindow window(videoMode, TITLE);
	
	Renderer* renderer = new Renderer(videoMode.width, videoMode.height, CANVAS_WIDTH, CANVAS_HEIGHT);
	if (renderer->Initialize(&window))
	{
		testForm = new TestForm(CANVAS_WIDTH, CANVAS_HEIGHT);
		testForm->GetChild("btnExit")->onClick.bind(&OnExitClick);
		testForm->GetChild("btnIncrease")->onClick.bind(&OnIncreaseClick);
		testForm->GetChild("btnDecrease")->onClick.bind(&OnDecreaseClick);
		static_cast<XAGUI::AnalogStick*>(testForm->GetChild("asAnalogStick"))->onValueChanged.bind(
				&OnAnalogStickValueChanged);
	
		XAGUI::MultilineTextBox* tbMultiline = static_cast<XAGUI::MultilineTextBox*>(testForm->GetChild(
			"tbMultilineTextBox"));
		tbMultiline->AddLine("First");
		tbMultiline->AddLine("Second\nThis is pretty long line to be splited. Huh?\nDZIA");
		tbMultiline->AddLine("Third");
		tbMultiline->AddLine("Fourth");
		tbMultiline->AddLine("Fifth");
		tbMultiline->AddLine("Sixth");
		tbMultiline->AddLine("Seventh");
		tbMultiline->AddLine("Eighth\nNineth");
		tbMultiline->AddLine("Line");
		tbMultiline->AddLine("First");
		tbMultiline->AddLine("Second\nThis is pretty long line to be splited. Huh?\nDZIA");
		tbMultiline->AddLine("Third");
		tbMultiline->AddLine("Fourth");
		tbMultiline->AddLine("Fifth");
		tbMultiline->AddLine("Sixth");
		tbMultiline->AddLine("Seventh");
		tbMultiline->AddLine("Eighth\nNineth");
		tbMultiline->AddLine("Line");
		tbMultiline->ShowVerticalScrollBar();

		XAGUI::ListBox* lbListBox = static_cast<XAGUI::ListBox*>(testForm->GetChild("lbListBox"));
		XAGUI::Label* item = new XAGUI::Label();
		item->SetID("item1");
		item->SetAlignment(ALIGNMENT_HCENTER);
		item->SetColor(CONTROL_STATE_HOVER, 0, 0, 150, 255);
		item->SetText("res/arial.ttf", 16, "First item");
		lbListBox->AddItem(item);
		
		item = new XAGUI::Label();
		item->SetID("item2");
		item->SetAlignment(ALIGNMENT_RIGHT);
		item->SetColor(CONTROL_STATE_HOVER, 0, 0, 150, 255);
		item->SetText("res/arial.ttf", 16, "Second item");
		lbListBox->AddItem(item);

		StaticText* fpsText = renderer->GetStaticText("res/arial.ttf", 12, "");
		fpsText->SetColor(255, 255, 255, 230);
		
		sf::Time time;
		sf::Clock elapsedTime;
		int frames = 0;

		sf::Event event;
		while (!quit)
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						{
							window.close();
							quit = true;
						}
						break;

					default:
						Event(&event);
						break;
				}
			}

			renderer->Clear();

			testForm->Render();

			renderer->Render(fpsText, 3, 3);

			renderer->Present();

			frames++;
			time = elapsedTime.getElapsedTime();
			if(time.asMilliseconds() >= 1000)
			{
				sprintf(buffer, "FPS: %u\nThx to Castey for this awesome skin!\ngithub.com/Xandev/XAGUI", 
					frames);
				fpsText->SetText(buffer);

				frames = 0;
				elapsedTime.restart();
			}
		}

		SAFE_DELETE(testForm);
		SAFE_DELETE(fpsText);
	}

	SAFE_DELETE(renderer);

    return 0;
}