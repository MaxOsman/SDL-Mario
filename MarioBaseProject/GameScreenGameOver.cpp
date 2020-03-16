#include "GameScreenGameOver.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{

}

GameScreenGameOver::~GameScreenGameOver()
{

}

void GameScreenGameOver::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	ImportText((string("Game Over! Press Space to try again.")).c_str());
	DrawText(Vector2D(SCREEN_WIDTH/5, SCREEN_HEIGHT/2));

	SDL_RenderPresent(mRenderer);
}

void GameScreenGameOver::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			mNextScreen = SCREEN_LEVEL1;
			break;
		}
		break;
	}
}