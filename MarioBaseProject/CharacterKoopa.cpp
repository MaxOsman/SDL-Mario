#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map, bool isArcadeMario, FACING direction) : Character(renderer, imagePath, startPosition, map, isArcadeMario)
{
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
	mInjured = false;
	isAlive = true;
	mFacingDirection = direction;
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	mVelocity.y = -KOOPA_HIT_JUMP_V;
	mIsGrounded = false;
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;
	else
		mFacingDirection = FACING_LEFT;
	mInjured = false;
	mVelocity.y = -KOOPA_HIT_JUMP_V;
	mIsGrounded = false;
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (mInjured)
		left = mSingleSpriteWidth;

	SDL_Rect portionOfSpriteSheet = {left, 0, mSingleSpriteWidth, mSingleSpriteHeight};
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
			mVelocity.x = -KOOPA_SPEED;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingLeft = false;
			mMovingRight = true;
			mVelocity.x = KOOPA_SPEED;
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
	centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / mSingleSpriteWidth;
	leftXPosition = (int)mPosition.x / mSingleSpriteWidth;
	rightXPosition = (int)(mPosition.x + mTexture->GetWidth()) / mSingleSpriteWidth;
	footPosition = (int)(mPosition.y + mTexture->GetHeight()) / mSingleSpriteWidth;
	headPosition = (int)mPosition.y / mSingleSpriteWidth;
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1)
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

	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition) == 1)
	{
		mPosition.y = (headPosition + 1) * mSingleSpriteWidth;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, leftXPosition) == 1)
	{
		mPosition.x = (leftXPosition + 1) * mSingleSpriteWidth;
		mVelocity.x = 0;
	}
	else if (mCurrentLevelMap->GetTileAt(headPosition, rightXPosition) == 1)
	{
		mPosition.x = (rightXPosition - 1) * mSingleSpriteWidth;
		mVelocity.x = 0;
	}
}

void CharacterKoopa::ScreenSideCheck()
{
	if (mPosition.x < -MARIO_WIDTH / 2)
	{
		mPosition.x = 512 - MARIO_WIDTH / 2;
		if (GetPosition().y > 300.0f)
		{
			isAlive = false;
		}
	}
	if (mPosition.x > 512 - MARIO_WIDTH / 2)
	{
		mPosition.x = -MARIO_WIDTH / 2;
		if (GetPosition().y > 300.0f)
		{
			isAlive = false;
		}
	}
}