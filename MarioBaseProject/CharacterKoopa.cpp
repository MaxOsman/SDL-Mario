#include "CharacterKoopa.h"
#include "CharacterKoopa.h"
#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, FACING direction, COLOUR type) : Character(renderer, imagePath, startPosition, map)
{
	mSingleSpriteWidth = mTexture->GetWidth() / 7;
	mSingleSpriteHeight = mTexture->GetHeight();
	mInjured = false;
	isAlive = true;
	mFacingDirection = direction;
	mType = type;
	mWalkAnimationTime = KOOPA_WALK_TIME;
	leftOfTilesheet = 0;
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	if(mType == KOOPA_GREEN)
		mInjuredTime = INJURED_TIME_GREEN;
	else if (mType == KOOPA_RED)
		mInjuredTime = INJURED_TIME_RED;
	else
		mInjuredTime = INJURED_TIME_PURPLE;
	mInjured = true;
	mIsGrounded = false;
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;
	else
		mFacingDirection = FACING_LEFT;
	mInjured = false;
	mIsGrounded = false;
}

void CharacterKoopa::Render()
{
	if (mInjured)
		leftOfTilesheet = mSingleSpriteWidth * 5;
	else
	{
		if (leftOfTilesheet == mSingleSpriteWidth * 5)
			leftOfTilesheet = 0;
	}

	SDL_Rect portionOfSpriteSheet = { leftOfTilesheet, 0, mSingleSpriteWidth, mSingleSpriteHeight};
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	else
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
			if (mType == KOOPA_GREEN)
				mVelocity.x = -KOOPA_GREEN_SPEED;
			else if (mType == KOOPA_RED)
				mVelocity.x = -KOOPA_RED_SPEED;
			else
				mVelocity.x = -KOOPA_PURPLE_SPEED;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
			if (mType == KOOPA_GREEN)
				mVelocity.x = KOOPA_GREEN_SPEED;
			else if (mType == KOOPA_RED)
				mVelocity.x = KOOPA_RED_SPEED;
			else
				mVelocity.x = KOOPA_PURPLE_SPEED;
		}

		mWalkAnimationTime -= deltaTime;
		if (mWalkAnimationTime <= 0 && leftOfTilesheet < 4 * mSingleSpriteWidth)
		{
			leftOfTilesheet += mSingleSpriteWidth;
			mWalkAnimationTime = KOOPA_WALK_TIME;
		}
		else if(mWalkAnimationTime <= 0 && leftOfTilesheet >= 4 * mSingleSpriteWidth)
		{
			leftOfTilesheet = 0;
			mWalkAnimationTime = KOOPA_WALK_TIME;
		}	
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;
		mVelocity.x = 0;
		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}
}

void CharacterKoopa::GroundCheck()
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

void CharacterKoopa::ScreenSideCheck()
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