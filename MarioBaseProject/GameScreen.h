#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include "Commons.h"
#include <iostream>
#include "SoundEffect.h"
#include "Scores.h"

class GameScreen
{
protected:
	SDL_Renderer* mRenderer;
	SDL_Color mColor;
	SDL_Surface* mSurface;
	SDL_Texture* mTextTexture;
	TTF_Font* mFont;
	SCREENS mNextScreen;
	SoundEffect* mSounds;

	float mSecondCountdown;
	int mTime;

public:
	GameScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void DrawText(Vector2D position);
	virtual void ImportText(TTF_Font* font);
	virtual void TimeCountdown(float deltaTime);

	SCREENS GetNextScreen() { return mNextScreen; }
};