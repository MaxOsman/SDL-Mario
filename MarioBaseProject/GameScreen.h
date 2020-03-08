#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include "Commons.h"
#include <iostream>

class GameScreen
{
protected:
	SDL_Renderer* mRenderer;
	SDL_Color mColor;
	SDL_Surface* mSurface;
	SDL_Texture* mTextTexture;
	Vector2D* mTextPosition;

public:
	GameScreen(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void DrawText(Vector2D position);
};