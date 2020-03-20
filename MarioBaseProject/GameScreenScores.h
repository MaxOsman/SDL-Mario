#pragma once
#include "GameScreen.h"
#include <string>
#include "Constants.h"
#include <sstream>
using namespace std;

class GameScreenScores : GameScreen
{
private:
	ostringstream oss;
	Scores* mScores;
	SDL_Surface* mSurface2;
	SDL_Texture* mTextTexture2;
	SDL_Surface* mSurface3;
	SDL_Texture* mTextTexture3;
public:
	GameScreenScores(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, Scores* score);
	~GameScreenScores();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ImportText(const char* text);
	void DrawText(Vector2D position);
};