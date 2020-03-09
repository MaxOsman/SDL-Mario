#include "GameScreenLevel1.h"

#define MARIO_POSITION_X = 64.0f
#define MARIO_POSITION_Y = 330.0f

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) : GameScreen(renderer, font, color)
{
	mLevelMap = NULL;
	SetUpLevel();
	spawnTime = SPAWN_TIME;
	mScore = 0;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	/*delete brickTexture;
	brickTexture = NULL;*/
	delete marioCharacter;
	marioCharacter = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		delete mEnemies[i];
	}
	mEnemies.clear();
	delete mLevelMap;
	mLevelMap = NULL;
}

void GameScreenLevel1::ImportText(const char* text)
{
	if (!(mSurface = TTF_RenderText_Shaded(mFont, text, mColor, { 0, 0, 0 })))
	{
		std::cout << "Text surface error." << std::endl;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
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
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
	SpawnEnemies(deltaTime);
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
	marioCharacter->Render();
	mPowBlock->Render();

	oss.str(string());
	oss << mScore;
	ImportText((string("Score: ") + oss.str()).c_str());
	DrawText(Vector2D(0, 0));
	/*for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			if(mLevelMap->GetTileAt(i, j) != 0)
				brickTexture->Render(Vector2D(j * 32, i * 32), SDL_FLIP_NONE);
		}
	}*/

	SDL_RenderPresent(mRenderer);
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
	//Clear any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set up new one.
	mLevelMap = new LevelMap(map);
}

bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	//Pow Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	//Player Characters
	marioCharacter = new CharacterMario(mRenderer, "Images/MarioAll.bmp", Vector2D(128, 200), mLevelMap, true);

	//Background
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.bmp"))
	{
		std::cout << "Failed to load background texture.";
		return false;
	}
	/*brickTexture = new Texture2D(mRenderer);
	if (!brickTexture->LoadFromFile("Images/brick.bmp"))
	{
		std::cout << "Failed to load brick texture.";
	}*/
}

void GameScreenLevel1::UpdatePowBlock()
{
	Rect2D mPowRect = mPowBlock->GetCollisionBox();
	Rect2D mMarioRect = marioCharacter->GetCollisionBox();
	if (CollisionsBox(mMarioRect, mPowRect))
	{
		if (mMarioRect.y > mPowRect.y+mPowRect.h/2 && marioCharacter->GetVelocity().y <= 0 && mPowBlock->IsAvailable() && !mScreenShake)
		{
			DoScreenShake();
			mPowBlock->TakeAHit();
			marioCharacter->CancelJump();
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
				if (CollisionsBox(mMarioRect, mEnemyRect))
				{
					if (mMarioRect.y < mEnemyRect.y - MARIO_HEIGHT + mEnemyRect.h / 2 && mMarioRect.x >= mEnemyRect.x - 14 && mMarioRect.x <= mEnemyRect.x + MARIO_WIDTH - 2 && marioCharacter->GetVelocity().y > 0)
					{
						mEnemies[i]->isAlive = false;
						marioCharacter->KoopaBounce(deltaTime);
						if (mEnemies[i]->GetType() == KOOPA_GREEN)
							mScore++;
						if (mEnemies[i]->GetType() == KOOPA_RED)
							mScore += 2;
						if (mEnemies[i]->GetType() == KOOPA_PURPLE)
							mScore += 3;
					}
					else
					{
						marioCharacter->isAlive = false;
					}
				}
			}
			else
			{
				if (CollisionsBox(mMarioRect, mEnemyRect))
				{
					mEnemies[i]->isAlive = false;
					if (mEnemies[i]->GetType() == KOOPA_GREEN)
						mScore++;
					if (mEnemies[i]->GetType() == KOOPA_RED)
						mScore += 2;
					if (mEnemies[i]->GetType() == KOOPA_PURPLE)
						mScore += 3;
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
	int randNum = rand() % 100 + 1;
	COLOUR randType;
	string path;
	if (randNum <= 60)
	{
		randType = KOOPA_GREEN;
		path = "Images/KoopaGreenAll.bmp";
	}
	if (randNum > 60 && randNum <= 90)
	{
		randType = KOOPA_RED;
		path = "Images/KoopaRedAll.bmp";
	}	
	if (randNum > 90)
	{
		randType = KOOPA_PURPLE;
		path = "Images/KoopaPurpleAll.bmp";
	}
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, path, position, mLevelMap, true, direction, randType);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::SpawnEnemies(float deltaTime)
{
	spawnTime -= deltaTime;
	if (spawnTime <= 0)
	{
		srand(time(0));
		int randNum = rand() % 2;
		if (randNum == 0)
		{
			CreateKoopa(Vector2D(-12, 32), FACING_RIGHT);
		}
		else
		{
			CreateKoopa(Vector2D(496, 32), FACING_LEFT);
		}
		spawnTime = SPAWN_TIME;
	}
}