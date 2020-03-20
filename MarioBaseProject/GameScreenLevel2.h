#pragma once
#include "GameScreen.h"
#include "CharacterMario.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <vector>
#include <time.h>
#include <sstream>

class Texture2D;

class GameScreenLevel2 : GameScreen
{
private:
	//Texture2D* brickTexture;
	void SetUpLevel();
	CharacterMario* marioCharacter;
	//Character* luigiCharacter;
	ostringstream oss;
	ostringstream oss2;
	Collisions mCollisions;
	Mix_Music* mGusic;
	LevelMap* mLevelMap;
	Scores* mScores;

	int mScore;
	bool canReset;
public:
	GameScreenLevel2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, Scores* scores);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetLevelMap();
	void ImportText(const char* text);
	void TimeCountdown(float deltaTime);
	void ResetBlocks();
	int GetScore() { return mScore; }
};
