#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* levelMap)
{
	mRenderer = renderer;
	string imagePath = "Images/PowBlock.bmp";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed PowBlock texture load." << endl;
		return;
	}
	mLevelMap = levelMap;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 224);
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	mLevelMap = NULL;
	delete mTexture;
	mTexture = NULL;
}

Rect2D PowBlock::GetCollisionBox()
{
	Rect2D tempRect(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	return tempRect;
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(7, 7, 0);
		mLevelMap->ChangeTileAt(7, 8, 0);
	}
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		SDL_Rect destRect = {(int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight};

		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}