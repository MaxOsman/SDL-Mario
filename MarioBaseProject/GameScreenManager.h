#pragma once

#include "Commons.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include "Scores.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
	TTF_Font* mFont;
	Scores* mScores;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen, TTF_Font* font, Scores* scores);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
};
