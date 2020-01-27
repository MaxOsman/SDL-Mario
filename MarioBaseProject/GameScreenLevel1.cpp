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
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{

}

void GameScreenLevel1::Render(int angle)
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE, angle);
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Test.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
}