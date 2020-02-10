#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#define MARIO_POSITION_X = 64.0f
#define MARIO_POSITION_Y = 330.0f

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete marioCharacter;
	marioCharacter = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	marioCharacter->Update(deltaTime, e);
}

void GameScreenLevel1::Render(int angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0x45, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	marioCharacter->Render();

	SDL_RenderPresent(mRenderer);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
	//Clear any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up new one.
	mLevelMap = new LevelMap(map);
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//Player Characters
	marioCharacter = new Character(mRenderer, "Images/Mario.bmp", Vector2D(128, 200), mLevelMap);

	//Background
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
}