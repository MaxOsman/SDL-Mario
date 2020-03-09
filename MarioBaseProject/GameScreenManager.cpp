#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen, TTF_Font* font)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	mFont = font;

	//Set up 1st screen
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
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
		tempScreen = new GameScreenLevel1(mRenderer, mFont, { 255, 64, 64 });
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		delete tempScreen;
		//mCurrentScreen->ImportText(mFont, (string("Score: ") + oss.str()).c_str(), { 255, 64, 64 });
		break;

	}
}