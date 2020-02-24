#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"

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
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	marioCharacter->Update(deltaTime, e);
	UpdatePowBlock();
}

void GameScreenLevel1::Render(int angle)
{
	SDL_SetRenderDrawColor(mRenderer, 0x45, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(mRenderer);

	mBackgroundTexture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
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

	//Player Characters
	marioCharacter = new Character(mRenderer, "Images/Mario2.bmp", Vector2D(128, 200), mLevelMap, true);

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

bool GameScreenLevel1::CollisionDetection(Rect2D mario, Rect2D block)
{
	if (mario.y + mario.h < block.y)
		return false;
	if (mario.y > block.y + block.h)
		return false;
	if (mario.x + mario.w < block.x)
		return false;
	if (mario.x > block.x + block.w)
		return false;

	return true;
}

void GameScreenLevel1::UpdatePowBlock()
{
	Vector2D mVelocity = marioCharacter->GetVelocity();
	Texture2D* mTexture = marioCharacter->GetTexture();
	Rect2D mPowRect = mPowBlock->GetCollisionBox();
	Rect2D mMarioRect = marioCharacter->GetCollisionBox();

	if (CollisionDetection(mMarioRect, mPowRect))
	{
		if (mMarioRect.y > mPowRect.y+mPowRect.h/2 && mVelocity.y < 0 && mPowBlock->IsAvailable())
		{
			//DoScreenShake();
			mPowBlock->TakeAHit();
			marioCharacter->CancelJump();
		}

		if (mMarioRect.y < mPowRect.y + mPowRect.h/2 && mVelocity.y >= 0 && mPowBlock->IsAvailable())
		{
			cout << endl;
			marioCharacter->mIsOnPowBlock = true;
			marioCharacter->LandingProceedure(mPowRect.y);
		}
		else
			marioCharacter->mIsOnPowBlock = false;
	}
}