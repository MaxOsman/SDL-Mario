#include "GameScreenLevel1.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{
	mLevelMap = NULL;
	SetUpLevel();
	koopaSpawnTime = KOOPA_SPAWN_TIME;
	coinSpawnTime = COIN_SPAWN_TIME;
	mScore = 0;
	mCollisions = Collisions();
	mTime = 120;
	mSecondCountdown = 1.0f;

	mGusic = Mix_LoadMUS("Sounds/Mario_.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mGusic, -1);
	}
	mSounds->AddSound("Sounds/pow_.wav", SOUND_POW);
	mSounds->AddSound("Sounds/coin_.wav", SOUND_COIN);
	mSounds->AddSound("Sounds/death.wav", SOUND_DIE);
	mSounds->AddSound("Sounds/jump_.wav", SOUND_JUMP);
	mSounds->AddSound("Sounds/bump_.wav", SOUND_BUMP);
	mSounds->AddSound("Sounds/stomp_.wav", SOUND_STOMP);
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete marioCharacter;
	marioCharacter = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		delete mEnemies[i];
	}
	mEnemies.clear();
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		delete mCoins[i];
	}
	mCoins.clear();
	delete mLevelMap;
	mLevelMap = NULL;
	Mix_FreeMusic(mGusic);
	mGusic = nullptr;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if(mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	marioCharacter->Update(deltaTime, e);
	KillMarioCheck();
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
	SpawnEnemies(deltaTime);
	SpawnCoins(deltaTime);
	TimeCountdown(deltaTime);
}

void GameScreenLevel1::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0x45, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	if (!mEnemies.empty())
	{
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Render();
		}
	}
	if (!mCoins.empty())
	{
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Render();
		}
	}
	marioCharacter->Render();
	mPowBlock->Render();

	oss.str(string());
	oss << mScore;
	oss2.str(string());
	oss2 << mTime;
	ImportText((string("Score: ") + oss.str() + "    " + string("Time: ") + oss2.str()).c_str());
	DrawText(Vector2D(0, 0));

	SDL_RenderPresent(mRenderer);
}

void GameScreenLevel1::SetLevelMap()
{
	char map[MAP_HEIGHT][MAP_WIDTH];

	//Clear any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up new one.
	mLevelMap = new LevelMap(map);
	mLevelMap->LoadMapFromFile(1);
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//Pow Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//Player Characters
	marioCharacter = new CharacterMario(mRenderer, "Images/MarioAll.bmp", Vector2D(240, 352), mLevelMap, mSounds);

	//Background
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	Rect2D mPowRect = mPowBlock->GetCollisionBox();
	Rect2D mMarioRect = marioCharacter->GetCollisionBox();
	if (mCollisions.Box(mMarioRect, mPowRect))
	{
		if (mMarioRect.y > mPowRect.y+mPowRect.h/2 && marioCharacter->GetVelocity().y <= 0 && mPowBlock->IsAvailable() && !mScreenShake)
		{
			DoScreenShake();
			mPowBlock->TakeAHit();
			marioCharacter->CancelJump();
			mSounds->Play(SOUND_POW);
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); ++i)
		{
			mEnemies[i]->Update(deltaTime, e);

			Rect2D mEnemyRect = mEnemies[i]->GetCollisionBox();
			Rect2D mMarioRect = marioCharacter->GetCollisionBox();
			if (mEnemies[i]->GetInjuredState() == false)
			{
				if (mCollisions.Box(mMarioRect, mEnemyRect))
				{
					if (mMarioRect.y < mEnemyRect.y - MARIO_HEIGHT + mEnemyRect.h / 2 && marioCharacter->GetVelocity().y > 0)
					{
						mEnemies[i]->isAlive = false;
						marioCharacter->KoopaBounce(deltaTime);
						if (mEnemies[i]->GetType() == KOOPA_GREEN)
							mScore++;
						if (mEnemies[i]->GetType() == KOOPA_RED)
							mScore += 2;
						if (mEnemies[i]->GetType() == KOOPA_PURPLE)
							mScore += 3;
						mSounds->Play(SOUND_STOMP);
					}
					else
					{
						marioCharacter->isAlive = false;
						mSounds->Play(SOUND_DIE);
					}
				}
			}
			else
			{
				if (mCollisions.Box(mMarioRect, mEnemyRect))
				{
					mEnemies[i]->isAlive = false;
					if (mEnemies[i]->GetType() == KOOPA_GREEN)
						mScore++;
					if (mEnemies[i]->GetType() == KOOPA_RED)
						mScore += 2;
					if (mEnemies[i]->GetType() == KOOPA_PURPLE)
						mScore += 3;
					mSounds->Play(SOUND_STOMP);
				}
			}
			if (!mEnemies[i]->isAlive && enemyIndexToDelete == -1)
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); ++i)
		{
			mCoins[i]->Update(deltaTime, e);

			Vector2D mCoinPos = mCoins[i]->GetPosition();
			Vector2D mMarioPos = marioCharacter->GetPosition();
			if (mCollisions.Circle(mMarioPos, mCoinPos, COIN_RADIUS))
			{
				mCoins[i]->isAlive = false;
				mScore += 5;
				mSounds->Play(SOUND_COIN);
			}
			if (!mCoins[i]->isAlive && coinIndexToDelete == -1)
			{
				coinIndexToDelete = i;
			}
		}
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction)
{
	srand(time(0));
	int randNum = rand() % 10 + 1;
	COLOUR randType;
	string path;
	if (randNum <= 6)
	{
		randType = KOOPA_GREEN;
		path = "Images/KoopaGreenAll.bmp";
	}
	if (randNum > 6 && randNum <= 9)
	{
		randType = KOOPA_RED;
		path = "Images/KoopaRedAll.bmp";
	}	
	if (randNum > 9)
	{
		randType = KOOPA_PURPLE;
		path = "Images/KoopaPurpleAll.bmp";
	}
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, path, position, mLevelMap, direction, randType);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction)
{
	CharacterCoin* coinCharacter = new CharacterCoin(mRenderer, "Images/CoinAll.bmp", position, mLevelMap, direction);
	mCoins.push_back(coinCharacter);
}

void GameScreenLevel1::SpawnEnemies(float deltaTime)
{
	koopaSpawnTime -= deltaTime;
	if (koopaSpawnTime <= 0)
	{
		srand(time(0));
		int randNum = rand() % 2;
		if (randNum == 0)
		{
			//Top Left
			CreateKoopa(Vector2D(-12, 32), FACING_RIGHT);
		}
		else
		{
			//Top Right
			CreateKoopa(Vector2D(496, 32), FACING_LEFT);
		}
		koopaSpawnTime = KOOPA_SPAWN_TIME;
	}
}

void GameScreenLevel1::SpawnCoins(float deltaTime)
{
	coinSpawnTime -= deltaTime;
	if (coinSpawnTime <= 0)
	{
		srand(time(0));
		int randNum = rand() % 4;
		if (randNum == 0)
		{
			//Top Left
			CreateCoin(Vector2D(-12, 32), FACING_RIGHT);
		}
		if (randNum == 1)
		{
			//Top Right
			CreateCoin(Vector2D(496, 32), FACING_LEFT);
		}
		if (randNum == 2)
		{
			//Middle Right
			CreateCoin(Vector2D(-12, 128), FACING_RIGHT);
		}
		if (randNum == 3)
		{
			//Middle Left
			CreateCoin(Vector2D(496, 128), FACING_LEFT);
		}
		coinSpawnTime = COIN_SPAWN_TIME;
	}
}

void GameScreenLevel1::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

void GameScreenLevel1::KillMarioCheck()
{
	if (!marioCharacter->isAlive)
	{
		mNextScreen = SCREEN_GAMEOVER;
	}
}

void GameScreenLevel1::TimeCountdown(float deltaTime)
{
	mSecondCountdown -= deltaTime;
	if (mSecondCountdown <= 0.0)
	{
		mSecondCountdown = 1.0f;
		--mTime;
	}
	if(mTime <= 0)
		mNextScreen = SCREEN_BEAT1;
}