#pragma once
#include "GameScreen.h"
#include <string>
#include "Constants.h"
using namespace std;

class GameScreenBeat1 : GameScreen
{
private:
	
public:
	GameScreenBeat1(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	~GameScreenBeat1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ImportText(const char* text);
};