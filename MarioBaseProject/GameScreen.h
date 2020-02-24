#pragma once

#include "SDL.h"

class GameScreen
{
protected:
	SDL_Renderer* mRenderer;

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render(int angle);
	virtual void Update(float deltaTime, SDL_Event e);
};