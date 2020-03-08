#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color)
{
	mColor = color;
	mRenderer = renderer;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
	delete mTextPosition;
	SDL_DestroyTexture(mTextTexture);
	SDL_FreeSurface(mSurface);
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	
}

void GameScreen::Render()
{

}

void GameScreen::DrawText(Vector2D position)
{
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(mTextTexture, NULL, NULL, &texW, &texH);
	SDL_Rect textRect = { position.x, position.y, texW, texH };
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &textRect);
	SDL_RenderPresent(mRenderer);
}