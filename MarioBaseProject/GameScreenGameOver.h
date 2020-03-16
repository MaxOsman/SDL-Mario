#pragma once
#include "GameScreen.h"
#include <string>
#include "Constants.h"
using namespace std;

class GameScreenGameOver : GameScreen
{
private:
	
public:
	GameScreenGameOver(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ImportText(const char* text);
};