#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING direction) : Character(renderer, imagePath, startPosition, map)
{
	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mFacingDirection = direction;
	isAlive = true;
	mWalkAnimationTime = COIN_ANIMATION_TIME;
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::GroundCheck()
{
	centralXPosition = (int)(mPosition.x + (mSingleSpriteWidth * 0.5f)) / mSingleSpriteWidth;
	leftXPosition = (int)mPosition.x / mSingleSpriteWidth;
	rightXPosition = (int)(mPosition.x + mSingleSpriteWidth) / mSingleSpriteWidth;
	footPosition = (int)(mPosition.y + mTexture->GetHeight()) / mSingleSpriteWidth;
	headPosition = (int)mPosition.y / mSingleSpriteWidth;
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == '1')
	{
		mPosition.y = (footPosition - 1) * mSingleSpriteWidth;
		mIsGrounded = true;
		mAccel.y = 0;
		mVelocity.y = 0;
	}
	else
	{
		mIsGrounded = false;
	}

	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) == '1' && mVelocity.y < 0)
	{
		mPosition.y = (headPosition + 1) * mSingleSpriteWidth;
		mVelocity.y = 0;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, leftXPosition) == '1' && mCurrentLevelMap->GetTileAt(footPosition - 1, leftXPosition) == 1)
	{
		mPosition.x = (leftXPosition + 1) * mSingleSpriteWidth - 31;
		mVelocity.x = 0;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, rightXPosition) == '1' && mCurrentLevelMap->GetTileAt(footPosition - 1, rightXPosition) == 1)
	{
		mPosition.x = (rightXPosition - 1) * mSingleSpriteWidth - 1;
		mVelocity.x = 0;
	}
}

void CharacterCoin::Render()
{
	SDL_Rect portionOfSpriteSheet = { leftOfTilesheet, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	else
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (mFacingDirection == FACING_LEFT)
	{
		mMovingLeft = true;
		mMovingRight = false;
		mVelocity.x = -COIN_MOVE_SPEED;
	}
	else if (mFacingDirection == FACING_RIGHT)
	{
		mMovingLeft = false;
		mMovingRight = true;
		mVelocity.x = COIN_MOVE_SPEED;
	}

	mWalkAnimationTime -= deltaTime;
	if (mWalkAnimationTime <= 0 && leftOfTilesheet < 2 * mSingleSpriteWidth)
	{
		leftOfTilesheet += mSingleSpriteWidth;
		mWalkAnimationTime = COIN_ANIMATION_TIME;
	}
	else if (mWalkAnimationTime <= 0 && leftOfTilesheet >= 2 * mSingleSpriteWidth)
	{
		leftOfTilesheet = 0;
		mWalkAnimationTime = COIN_ANIMATION_TIME;
	}
}

void CharacterCoin::ScreenSideCheck()
{
	if (mPosition.x < -mSingleSpriteWidth * 0.5)
	{
		mPosition.x = 512 - mSingleSpriteWidth * 0.5;
		if (GetPosition().y > 300.0f)
		{
			isAlive = false;
		}
	}
	if (mPosition.x > 512 - mSingleSpriteWidth * 0.5)
	{
		mPosition.x = -mSingleSpriteWidth * 0.5;
		if (GetPosition().y > 300.0f)
		{
			isAlive = false;
		}
	}
}