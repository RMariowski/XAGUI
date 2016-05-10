#ifndef XAGUI_TEST_MAIN_H
#define XAGUI_TEST_MAIN_H

#include <XAGUI.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <SDL2/Font.h>
#include <SDL2/Texture.h>
#include <SDL2/StaticText.h>
#include <SDL2/Renderer.h>
#include <SDL2/InputHandler.h>

#define TITLE "XAGUI Test"
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define CANVAS_WIDTH 1024
#define CANVAS_HEIGHT 768

#include "TestForm.h"

extern void Message(uint32_t flags, cchar* title, cchar* message);

#endif