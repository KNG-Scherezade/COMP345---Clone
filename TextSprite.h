#pragma once

#include "stdafx.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextSprite
{
public:
	TextSprite(SDL_Renderer* renderer, bool* quit, std::string textContent, TTF_Font* textFont, SDL_Color textColor, int x, int y);
	~TextSprite();

	void SetText(std::string newText) { text = newText; }
	void SetColor(SDL_Color newColor) { color = newColor; }
	void SetFont(TTF_Font* newFont) { font = newFont; }

	void Draw();
private:
	SDL_Renderer* render;

	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Texture* texture;
	int textHeight;
	int textWidth;
	int x;
	int y;
	SDL_Rect rect;
	std::string text;
};

