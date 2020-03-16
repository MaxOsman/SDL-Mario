#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenGameOver.h"
#include "GameScreenBeat1.h"

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
	if (mCurrentScreen->GetNextScreen() != SCREEN_NULL)
		ChangeScreen(mCurrentScreen->GetNextScreen());
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear old screen
	if (mCurrentScreen != NULL)
		delete mCurrentScreen;

	switch (newScreen)
	{
	case SCREEN_LEVEL1:
		GameScreenLevel1* tempScreen1;
		tempScreen1 = new GameScreenLevel1(mRenderer, mFont, { 255, 255, 255 });
		mCurrentScreen = (GameScreen*)tempScreen1;
		tempScreen1 = NULL;
		delete tempScreen1;
		break;

	case SCREEN_GAMEOVER:
		GameScreenGameOver* tempScreenG;
		tempScreenG = new GameScreenGameOver(mRenderer, mFont, { 255, 64, 64 });
		mCurrentScreen = (GameScreen*)tempScreenG;
		tempScreenG = NULL;
		delete tempScreenG;
		break;

	case SCREEN_BEAT1:
		GameScreenBeat1* tempScreenB1;
		tempScreenB1 = new GameScreenBeat1(mRenderer, mFont, { 64, 255, 64 });
		mCurrentScreen = (GameScreen*)tempScreenB1;
		tempScreenB1 = NULL;
		delete tempScreenB1;
		break;
	}
}