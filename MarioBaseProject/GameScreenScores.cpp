#include "GameScreenScores.h"

GameScreenScores::GameScreenScores(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, Scores* scores) : GameScreen(renderer, font, color)
{
	Mix_HaltMusic();
	Mix_HaltChannel(-1);
	mScores = scores;
}

GameScreenScores::~GameScreenScores()
{
	delete mScores;
}

void GameScreenScores::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	ImportText((string("-SCORES-")).c_str());
	DrawText(Vector2D(SCREEN_WIDTH/3, SCREEN_HEIGHT/3));

	SDL_RenderPresent(mRenderer);
}

void GameScreenScores::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
		cout << "Text surface error." << endl;
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);

	oss.str(string());
	oss << "Level 1:  " << mScores->GetScore(1) << "        " << "Level 2:  " << mScores->GetScore(2);
	if (!(mSurface2 = TTF_RenderText_Shaded(mFont, (oss.str()).c_str(), mColor, { 0, 0, 0 })))
		cout << "Text surface error." << endl;
	mTextTexture2 = SDL_CreateTextureFromSurface(mRenderer, mSurface2);

	oss.str(string());
	int totalScore = mScores->GetScore(1) + mScores->GetScore(2);
	if (totalScore == 0)
		oss << "Now this is just silly...";
	else if (totalScore > 0 && totalScore <= 20)
		oss << "You can do better than that!";
	else if (totalScore > 20 && totalScore <= 40)
		oss << "Getting better, but not ideal.";
	else if (totalScore > 40 && totalScore <= 60)
		oss << "A decent score, but a little average.";
	else if (totalScore > 60 && totalScore <= 80)
		oss << "Now that's more like it!";
	else if (totalScore > 80 && totalScore <= 100)
		oss << "Brilliant! You sure got the hang of this game quickly!";
	else if (totalScore > 100)
		oss << "Over 100? You must be cheating!";
	if (!(mSurface3 = TTF_RenderText_Shaded(mFont, (oss.str()).c_str(), mColor, { 0, 0, 0 })))
		cout << "Text surface error." << endl;
	mTextTexture3 = SDL_CreateTextureFromSurface(mRenderer, mSurface3);
}

void GameScreenScores::Update(float deltaTime, SDL_Event e)
{
	
}

void GameScreenScores::DrawText(Vector2D position)
{
	int texW = 0,
		texH = 0;
	SDL_QueryTexture(mTextTexture, NULL, NULL, &texW, &texH);
	SDL_Rect textRect = { position.x, position.y, texW, texH };
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &textRect);

	SDL_QueryTexture(mTextTexture2, NULL, NULL, &texW, &texH);
	SDL_Rect textRect2 = { position.x-75, position.y+100, texW, texH };
	SDL_RenderCopy(mRenderer, mTextTexture2, NULL, &textRect2);

	SDL_QueryTexture(mTextTexture3, NULL, NULL, &texW, &texH);
	SDL_Rect textRect3 = { position.x - 75, position.y + 200, texW, texH };
	SDL_RenderCopy(mRenderer, mTextTexture3, NULL, &textRect3);

	SDL_DestroyTexture(mTextTexture);
	SDL_FreeSurface(mSurface);
	SDL_DestroyTexture(mTextTexture2);
	SDL_FreeSurface(mSurface2);
	SDL_DestroyTexture(mTextTexture3);
	SDL_FreeSurface(mSurface3);
}