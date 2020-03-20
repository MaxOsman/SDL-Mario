#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, Scores* scores) : GameScreen(renderer, font, color)
{
	mLevelMap = NULL;
	SetUpLevel();
	mScore = 0;
	mCollisions = Collisions();
	mTime = 60;
	mSecondCountdown = 1.0f;
	canReset = true;
	mScores = scores;

	Mix_HaltChannel(-1);
	mGusic = Mix_LoadMUS("Sounds/MarioUnderworld_.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mGusic, -1);
	}
	mSounds->AddSound("Sounds/coin_.wav", SOUND_COIN);
	mSounds->AddSound("Sounds/death.wav", SOUND_DIE);
	mSounds->AddSound("Sounds/jump_.wav", SOUND_JUMP);
	mSounds->AddSound("Sounds/bump_.wav", SOUND_BUMP);
	mSounds->AddSound("Sounds/stomp_.wav", SOUND_STOMP);
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete marioCharacter;
	marioCharacter = NULL;
	delete mLevelMap;
	mLevelMap = NULL;
	Mix_FreeMusic(mGusic);
	mGusic = nullptr;
	delete mScores;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	marioCharacter->Update(deltaTime, e);
	mLevelMap->Update(deltaTime);
	TimeCountdown(deltaTime);
	mScore = marioCharacter->GetScore();
	ResetBlocks();
}

void GameScreenLevel2::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(mRenderer);

	marioCharacter->Render();
	mLevelMap->Render();

	oss.str(string());
	oss << mScore;
	oss2.str(string());
	oss2 << mTime;
	ImportText((string("Score: ") + oss.str() + "    " + string("Time: ") + oss2.str()).c_str());
	DrawText(Vector2D(0, 0));
	
	SDL_RenderPresent(mRenderer);
}

void GameScreenLevel2::SetLevelMap()
{
	char map[MAP_HEIGHT][MAP_WIDTH];

	//Clear any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up new one.
	mLevelMap = new LevelMap(map, "Images/GroundBlock.bmp", "Images/CoinBlock.bmp", "Images/EmptyBlock.bmp", mRenderer);
	mLevelMap->LoadMapFromFile(2);
}

void GameScreenLevel2::SetUpLevel()
{
	SetLevelMap();

	//Player Characters
	marioCharacter = new CharacterMario(mRenderer, "Images/MarioAll.bmp", Vector2D(240, 352), mLevelMap, mSounds);
}

void GameScreenLevel2::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

void GameScreenLevel2::TimeCountdown(float deltaTime)
{
	mSecondCountdown -= deltaTime;
	if (mSecondCountdown <= 0.0)
	{
		mSecondCountdown = 1.0f;
		--mTime;
	}
	if (mTime <= 0)
	{
		//END OF LEVEL
		mScores->StoreTemp(2, mScore);
		mNextScreen = SCREEN_BEAT2;
	}
}

void GameScreenLevel2::ResetBlocks()
{
	if (mScore % 36 == 0 && mScore != 0)
	{
		if (canReset)
		{
			for (unsigned int i = 0; i < MAP_HEIGHT; ++i)
			{
				for (unsigned int j = 0; j < MAP_WIDTH; ++j)
				{
					if (mLevelMap->GetTileAt(i, j) == '4')
						mLevelMap->ChangeTileAt(i, j, '3');
				}
			}
			canReset = false;
			mSounds->Play(SOUND_STOMP);
		}
	}
	else
	{
		canReset = true;
	}
}