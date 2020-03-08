#pragma once
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "PowBlock.h"
#include "Texture2D.h"
#include <vector>
#include <time.h>
#include <sstream>

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

	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	float spawnTime;
	int mScore;
public:
	GameScreenLevel1(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();

	void UpdatePowBlock();
	void SpawnEnemies(float deltaTime);
	void UpdateEnemies(float DeltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);

	int GetScore() { return mScore; }

	bool CollisionsBox(Rect2D rect1, Rect2D rect2)
	{
		if (rect1.y + rect1.h < rect2.y)
			return false;
		if (rect1.y > rect2.y + rect2.h)
			return false;
		if (rect1.x + rect1.w < rect2.x)
			return false;
		if (rect1.x > rect2.x + rect2.w)
			return false;

		return true;
	}

	LevelMap* mLevelMap;
};
