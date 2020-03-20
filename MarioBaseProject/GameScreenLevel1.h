#pragma once
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "PowBlock.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <vector>
#include <time.h>
#include <sstream>
#include <fstream>

class Texture2D;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	//Texture2D* brickTexture;
	bool SetUpLevel();
	void DoScreenShake();
	CharacterMario* marioCharacter;
	//Character* luigiCharacter;
	PowBlock* mPowBlock;
	vector<CharacterKoopa*> mEnemies;
	vector<CharacterCoin*> mCoins;
	ostringstream oss;
	ostringstream oss2;
	Collisions mCollisions;
	Mix_Music* mGusic;

	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	float koopaSpawnTime;
	float coinSpawnTime;
	int mScore;
	Scores* mScores;
public:
	GameScreenLevel1(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, Scores* scores);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void ImportText(const char* text);

	void UpdatePowBlock();
	void SpawnEnemies(float deltaTime);
	void SpawnCoins(float deltaTime);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);
	void CreateCoin(Vector2D position, FACING direction);
	void KillMarioCheck();
	void TimeCountdown(float deltaTime);

	int GetScore() { return mScore; }

	LevelMap* mLevelMap;
};
