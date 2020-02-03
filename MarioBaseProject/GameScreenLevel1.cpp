#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

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
	mBackgroundTexture->Render(Vector2D(), angle);
	myCharacter->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Player Character
	myCharacter = new Character(mRenderer, "Images/Mario.bmp", Vector2D());

	//Background
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
}