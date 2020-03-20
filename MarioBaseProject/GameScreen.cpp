#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color)
{
	mRenderer = renderer;
	mFont = font;
	mColor = color;
	mSurface = nullptr;
	mNextScreen = SCREEN_NULL;
	mSounds = new SoundEffect;
}

GameScreen::~GameScreen()
{
	mFont = NULL;
	mRenderer = NULL;
	delete mSounds;
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	
}

void GameScreen::Render()
{

}

void GameScreen::DrawText(Vector2D position)
{
	int texW = 0,
		texH = 0;
	SDL_QueryTexture(mTextTexture, NULL, NULL, &texW, &texH);
	SDL_Rect textRect = { position.x, position.y, texW, texH };
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &textRect);
	SDL_DestroyTexture(mTextTexture);
	SDL_FreeSurface(mSurface);
}

void GameScreen::ImportText(TTF_Font* font)
{
	
}

void GameScreen::TimeCountdown(float deltaTime)
{

}