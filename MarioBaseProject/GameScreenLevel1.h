#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"

class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	//Texture2D* brickTexture;
	bool SetUpLevel();
	Character* marioCharacter;
	Character* luigiCharacter;
	PowBlock* mPowBlock;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render(int angle);
	void Update(float deltaTime, SDL_Event e);
	void SetLevelMap();
	void UpdatePowBlock();
	bool CollisionDetection(Rect2D mario, Rect2D block);

	LevelMap* mLevelMap;
};
