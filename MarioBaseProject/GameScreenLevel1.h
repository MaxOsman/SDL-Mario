#pragma once
#include "GameScreen.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>

class Texture2D;
//class Character;
//class CharacterMario;
//class CharacterKoopa;
//class PowBlock;

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
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void UpdatePowBlock();

	void UpdateEnemies(float DeltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);

	/*bool CollisionsBox(Rect2D rect1, Rect2D rect2)
	{
		if (rect1.x + (rect1.w / 2) >= rect2.x&&
			rect1.x + (rect1.w / 2) <= rect2.x + rect2.w &&
			rect1.y + (rect1.h / 2) >= rect2.y&&
			rect1.y + (rect1.h / 2) <= rect2.y + rect2.h)
		{
			return true;
		}

		return false;
	}*/
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
