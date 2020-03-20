#include "GameScreenBeat2.h"

GameScreenBeat2::GameScreenBeat2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{
	Mix_HaltMusic();
	Mix_HaltChannel(-1);
}

GameScreenBeat2::~GameScreenBeat2()
{

}

void GameScreenBeat2::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	ImportText((string("Level 2 Complete! Press Space to see results!")).c_str());
	DrawText(Vector2D(SCREEN_WIDTH/6, SCREEN_HEIGHT/2));

	SDL_RenderPresent(mRenderer);
}

void GameScreenBeat2::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

void GameScreenBeat2::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mNextScreen = SCREEN_SCORES;
			break;
		}
		break;
	}
}