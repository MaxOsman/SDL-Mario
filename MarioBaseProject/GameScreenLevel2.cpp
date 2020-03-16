#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{
	mLevelMap = NULL;
	SetUpLevel();
	mScore = 0;
	mCollisions = Collisions();
	mTime = 120;
	mSecondCountdown = 1.0f;

	mGusic = Mix_LoadMUS("Sounds/MarioUnderworld.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mGusic, -1);
	}
	mSounds->AddSound("Sounds/coin_.wav", SOUND_COIN);
	mSounds->AddSound("Sounds/death.wav", SOUND_DIE);
	mSounds->AddSound("Sounds/jump_.wav", SOUND_JUMP);
	mSounds->AddSound("Sounds/bump_.wav", SOUND_BUMP);
}

GameScreenLevel2::~GameScreenLevel2()
{
	/*delete brickTexture;
	brickTexture = NULL;*/
	delete marioCharacter;
	marioCharacter = NULL;
	delete mLevelMap;
	mLevelMap = NULL;
	Mix_FreeMusic(mGusic);
	mGusic = nullptr;
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	marioCharacter->Update(deltaTime, e);
	TimeCountdown(deltaTime);
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
	mLevelMap = new LevelMap(map, "Images/brick.bmp", "Images/brick.bmp", "Images/brick.bmp", mRenderer);
	mLevelMap->LoadMapFromFile(2);
}

void GameScreenLevel2::SetUpLevel()
{
	SetLevelMap();

	//Player Characters
	marioCharacter = new CharacterMario(mRenderer, "Images/MarioAll.bmp", Vector2D(240, 352), mLevelMap, mSounds);

	/*brickTexture = new Texture2D(mRenderer);
	if (!brickTexture->LoadFromFile("Images/brick.bmp"))
	{
		std::cout << "Failed to load brick texture.";
	}*/
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
	if(mTime <= 0)
		mNextScreen = SCREEN_BEAT2;
}