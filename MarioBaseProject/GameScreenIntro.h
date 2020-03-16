#pragma once
#include "GameScreen.h"
#include <string>
#include "Constants.h"
using namespace std;

class GameScreenIntro : GameScreen
{
private:
	
public:
	GameScreenIntro(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ImportText(const char* text);
};