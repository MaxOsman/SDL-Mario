#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"

class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	Character* marioCharacter;
	Character* luigiCharacter;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render(int angle);
	void Update(float deltaTime, SDL_Event e);
};
