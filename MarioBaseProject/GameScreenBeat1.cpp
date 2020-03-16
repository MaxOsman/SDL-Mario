#include "GameScreenBeat1.h"

GameScreenBeat1::GameScreenBeat1(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{

}

GameScreenBeat1::~GameScreenBeat1()
{

}

void GameScreenBeat1::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	ImportText((string("Level 1 Complete! Only one more to go!")).c_str());
	DrawText(Vector2D(SCREEN_WIDTH/5, SCREEN_HEIGHT/2));

	SDL_RenderPresent(mRenderer);
}

void GameScreenBeat1::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

void GameScreenBeat1::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mNextScreen = SCREEN_LEVEL2;
			break;
		}
		break;
	}
}