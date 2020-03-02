#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

#define MARIO_POSITION_X = 64.0f
#define MARIO_POSITION_Y = 330.0f

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	SetUpLevel();
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
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
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
	marioCharacter = new CharacterMario(mRenderer, "Images/Mario2.bmp", Vector2D(128, 200), mLevelMap, true);

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

	CreateKoopa(Vector2D(150, 64), FACING_RIGHT);
	CreateKoopa(Vector2D(325, 64), FACING_LEFT);
}

void GameScreenLevel1::UpdatePowBlock()
{
	Rect2D mPowRect = mPowBlock->GetCollisionBox();
	Rect2D mMarioRect = marioCharacter->GetCollisionBox();

	if (CollisionsBox(mMarioRect, mPowRect))
	{
		if (mMarioRect.y > mPowRect.y+mPowRect.h/2 && marioCharacter->GetVelocity().y < 0 && mPowBlock->IsAvailable())
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
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Update(deltaTime, e);

			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().y < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH-96.0f))
			{
				//Nothing.
			}
			else
			{
				Rect2D mEnemyRect = mEnemies[i]->GetCollisionBox();
				Rect2D mMarioRect = marioCharacter->GetCollisionBox();
				if (CollisionsBox(mMarioRect, mEnemyRect))
				{
					if (mMarioRect.y < mEnemyRect.y - MARIO_HEIGHT + mEnemyRect.h / 2 && mMarioRect.x >= mEnemyRect.x - 12 && mMarioRect.x <= mEnemyRect.x + MARIO_WIDTH - 4 && marioCharacter->GetVelocity().y > 0)
					{
						mEnemies[i]->isAlive = false;
						marioCharacter->CancelJump();
					}
					else
					{
						marioCharacter->isAlive = false;
					}
				}
			}

			if (!mEnemies[i]->isAlive)
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
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.bmp", position, mLevelMap, true, direction);
	mEnemies.push_back(koopaCharacter);
}