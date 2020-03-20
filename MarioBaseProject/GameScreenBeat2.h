#pragma once
#include "GameScreen.h"
#include <string>
#include "Constants.h"
using namespace std;

class GameScreenBeat2 : GameScreen
{
private:
	
public:
	GameScreenBeat2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	~GameScreenBeat2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ImportText(const char* text);
};