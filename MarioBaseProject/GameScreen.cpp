#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

void GameScreen::Render(int angle)
{

}