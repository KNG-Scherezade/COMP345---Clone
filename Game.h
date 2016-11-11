#pragma once
#include "SDLSetup.h"
#include "TextSprite.h"
#include "Character.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight);
	~Game();
	void GameLoop();
	void DriverGameLoop(int amountHit);
private:
	bool quit;

	SDLSetup* setup;
	TextSprite* characterHpSprite;
	TextSprite* testInstructions1;
	TextSprite* testInstructions2;
	TTF_Font* font;
	SDL_Color color;
	std::string text;

	Character* myCharacter;
};

