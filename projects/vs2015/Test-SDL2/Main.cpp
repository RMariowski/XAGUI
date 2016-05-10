#include "Main.h"

TestForm* testForm = 0;

bool quit = false;
char buffer[MAX_BUFFER];

bool Event(SDL_Event* event)
{
	switch (event->type)
	{ 
		case SDL_MOUSEMOTION:
			testForm->MouseMoveEvent(event->motion.x, event->motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			return testForm->MouseButtonDownEvent(event->button.x, event->button.y, 
				MouseButtonToXAGUI(event->button.button));

		case SDL_MOUSEBUTTONUP:
			{
				testForm->MouseButtonUpEvent(event->button.x, event->button.y, 
					MouseButtonToXAGUI(event->button.button));
			}
			break;

		case SDL_KEYDOWN:
			{
				if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
				else testForm->KeyDownEvent(KeyToXAGUI(event->key.keysym.scancode));
			}
			break;

		case SDL_KEYUP:
			testForm->KeyUpEvent(KeyToXAGUI(event->key.keysym.scancode));
			break;

		case SDL_TEXTINPUT:
			testForm->TextInputEvent(event->text.text);
			break;
	}
	return false;
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

int main(int argc, char** argv)
{
	// Initializes SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Message(SDL_MESSAGEBOX_ERROR, TITLE, SDL_GetError());
		return 0;
	}

	// Gets current display
	SDL_DisplayMode display;
	SDL_GetDisplayMode(0, 0, &display);

	// For Android and iOS devices the size of window should be the same as screen resolution
#if !defined(__ANDROID__) && !defined(__IPHONEOS__)
	display.w = SCREEN_WIDTH;
	display.h = SCREEN_HEIGHT;
#endif
	
	Renderer* renderer = new Renderer(display.w, display.h, CANVAS_WIDTH, CANVAS_HEIGHT);
	if (renderer->Initialize())
	{
#if defined(__ANDROID__) || defined(__IPHONEOS__)
		XAGUI::XAGUI::SetShowOnScreenKeyboard(SDL_StartTextInput);
		XAGUI::XAGUI::SetHideOnScreenKeyboard(SDL_StopTextInput);
#endif
		testForm = new TestForm(CANVAS_WIDTH, CANVAS_HEIGHT);
		testForm->GetChild("btnExit")->onClick.bind(&OnExitClick);
		testForm->GetChild("btnIncrease")->onClick.bind(&OnIncreaseClick);
		testForm->GetChild("btnDecrease")->onClick.bind(&OnDecreaseClick);
		static_cast<XAGUI::AnalogStick*>(testForm->GetChild("asAnalogStick"))->onValueChanged.bind(
				&OnAnalogStickValueChanged);
	
		XAGUI::MultilineTextBox* tbMultiline = static_cast<XAGUI::MultilineTextBox*>(testForm->GetChild(
			"tbMultilineTextBox"));
		tbMultiline->AddLine("RIP is one of the oldest distance-vector routing protocols, which employs the hop count as a routing metric. RIP prevents routing loops by implementing a limit on the number of hops allowed in a path from the source to a destination. The maximum number of hops allowed for RIP is 15. This hop limit, however, also limits the size of networks that RIP can support. A hop count of 16 is considered an infinite distance, in other words the route is considered unreachable. RIP implements the split horizon, route poisoning and holddown mechanisms to prevent incorrect routing information from being propagated.");
		//tbMultiline->ShowVerticalScrollBar();

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

		uint32_t newTime;
		float deltaTime;
		float fpsTime = 0.0f;
		uint32_t frames = 0;
		uint32_t time = SDL_GetTicks();

		StaticText* fpsText = renderer->GetStaticText("res/arial.ttf", 12, "");
		fpsText->SetColor(255, 255, 255, 230);

		SDL_Event event;
		while (!quit)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						quit = true;
						break;

					default:
						Event(&event);
						break;
				}
			}
			newTime = SDL_GetTicks();
			deltaTime = (newTime - time) / 1000.0f;
			time = newTime;

			renderer->Clear();

			testForm->Render();

			renderer->Render(fpsText, 3, 3);
			
			renderer->Present();

			++frames;
			fpsTime += deltaTime;
			if (fpsTime >= 1.0f)
			{
				sprintf(buffer, "FPS: %u\nThx to Castey for this awesome skin!\ngithub.com/Xandev/XAGUI", 
					static_cast<uint32_t>(frames / fpsTime));
				fpsText->SetText(buffer);

				frames = 0;
				fpsTime = 0.0f;
			}
		}

		SAFE_DELETE(testForm);
		SAFE_DELETE(fpsText);
	}

	SAFE_DELETE(renderer);

	SDL_Quit();

	return 0;
}

void Message(uint32_t flags, cchar* title, cchar* message)
{
#if !defined(__ANDROID__) && !defined(__IPHONEOS__)
	switch (flags)
	{
		case SDL_MESSAGEBOX_ERROR:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, 0);
			break;

		case SDL_MESSAGEBOX_WARNING:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, message, 0);
			break;
		
		case SDL_MESSAGEBOX_INFORMATION:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, 0);
			break;
	}
#else
	switch (flags)
	{
		case SDL_MESSAGEBOX_ERROR:
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message);
			break;

		case SDL_MESSAGEBOX_WARNING:
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, message);
			break;
		
		case SDL_MESSAGEBOX_INFORMATION:
			SDL_Log(message);
			break;
	}
#endif
}