#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;

	//Set up 1st screen
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	delete mRenderer;
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render(int angle)
{
	mCurrentScreen->Render(angle);
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;

	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;

	}
}