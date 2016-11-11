//! @file SDLSetup.cpp
//! @author Patrick Nicoll 27218729
//! @brief Implementation of the class that takes care of setting up the base SDL objects

#include "stdafx.h"
#include "SDLSetup.h"
#include <iostream>

//! Constructor
//! @param quit	Boolean representing whether the user has quit the game or not
//! @param screenWidth	Width of the game window
//! @param screenHeight	Height of the game window
SDLSetup::SDLSetup(bool* quit,int screenWidth, int screenHeight)
{
	//Create the game window
	window = NULL;
	window = SDL_CreateWindow("Character Window", 300, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL){
		std::cout << "Error loading window" << std::endl;
		*quit = true;
	}

	//Create the renderer
	render = NULL;
	render = SDL_CreateRenderer(window, -1, 0);
	if (render == NULL){
		std::cout << "Error loading renderer" << std::endl;
		*quit = true;
	}

	//Create an event object
	mainEvent = new SDL_Event();
}

//! Destructor
SDLSetup::~SDLSetup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	delete mainEvent;
}

//! Getter for the renderer object
//! @return	renderer
SDL_Renderer* SDLSetup::GetRenderer()
{
	return render;
}

//! Getter for the event object
//! @return game event
SDL_Event* SDLSetup::GetEvent()
{
	return mainEvent;
}

//! Steps required at the beginning of each Draw loop
void SDLSetup::Begin() {
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(render);
}

//! Steps required at the end of each Draw loop
void SDLSetup::End() {
	SDL_RenderPresent(render);
}
