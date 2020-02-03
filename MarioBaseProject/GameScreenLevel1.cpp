#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#define MARIO_POSITION_X = 64.0f
#define MARIO_POSITION_Y = 330.0f

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete myCharacter;
	myCharacter = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	myCharacter->Update(deltaTime, e);
}

void GameScreenLevel1::Render(int angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0x45, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	myCharacter->Render();

	SDL_RenderPresent(mRenderer);
}

bool GameScreenLevel1::SetUpLevel()
{
	//Player Character
	myCharacter = new Character(mRenderer, "Images/Mario.bmp", Vector2D(0, 0));

	//Background
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
}