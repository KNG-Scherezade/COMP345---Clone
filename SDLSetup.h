#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
class SDLSetup
{
public:
	SDLSetup(bool* quit, int screenWidth, int screenHeight);
	~SDLSetup();

	SDL_Renderer* GetRenderer();
	SDL_Event* GetEvent();

	void Begin();
	void End();
private:
	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Event* mainEvent;
};

