#pragma once

#include "Commons.h"
#include "SDL.h"
#include <SDL_ttf.h>

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
	TTF_Font* mFont;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen, TTF_Font* font);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
};
